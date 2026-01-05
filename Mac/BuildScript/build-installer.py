# NSN (Network Security Navigator)
# Copyright (c) NSN Contributors
# Licensed under MIT License
#
# File: build-installer.py

"""MacOS Installer Builder for NSN

This script automates the creation of a signed macOS installer (DMG) for the
NSN interpreter.  It performs the following steps:

1. **Build the interpreter** – invokes CMake to produce a universal binary
   (x86_64 + arm64) inside the `build/` directory.
2. **Create an application bundle** – places the binary, resources and a
   minimal `Info.plist` into `NSN.app`.
3. **Code‑sign the bundle** – uses the developer identity supplied via the
   `CODE_SIGN_IDENTITY` environment variable.  If the variable is not set the
   script falls back to an ad‑hoc signature (`-`) which is sufficient for local
   testing.
4. **Package into a DMG** – creates a read‑only disk image with a background
   image and a custom layout.
5. **Notarize (optional)** – if `APPLE_NOTARIZE` is set to `1` the script will
   upload the DMG to Apple’s notarization service using `xcrun altool`.

The script is deliberately self‑contained and does not require any external
Python packages beyond the standard library.
"""

import os
import shutil
import subprocess
import sys
from pathlib import Path

# ---------------------------------------------------------------------------
# Configuration (can be overridden via environment variables)
# ---------------------------------------------------------------------------
PROJECT_ROOT = Path(__file__).resolve().parent.parent  # repository root
BUILD_DIR = PROJECT_ROOT / "build"
APP_BUNDLE = BUILD_DIR / "NSN.app"
DMG_PATH = BUILD_DIR / "NSN.dmg"
CODE_SIGN_IDENTITY = os.getenv("CODE_SIGN_IDENTITY", "-")  # '-' = ad‑hoc
APPLE_NOTARIZE = os.getenv("APPLE_NOTARIZE", "0") == "1"
NOTARIZE_USER = os.getenv("APPLE_NOTARIZE_USER")
NOTARIZE_PASS = os.getenv("APPLE_NOTARIZE_PASS")

# ---------------------------------------------------------------------------
# Helper utilities
# ---------------------------------------------------------------------------
def run(cmd, cwd=None, check=True):
    """Run a shell command and stream its output.
    Raises subprocess.CalledProcessError on failure when `check` is True.
    """
    print(f"Running: {' '.join(cmd)}")
    result = subprocess.run(cmd, cwd=cwd, text=True, capture_output=False)
    if check and result.returncode != 0:
        raise subprocess.CalledProcessError(result.returncode, cmd)
    return result

def ensure_dir(path: Path):
    path.mkdir(parents=True, exist_ok=True)

# ---------------------------------------------------------------------------
# Step 1 – Build the interpreter
# ---------------------------------------------------------------------------
def build_interpreter():
    ensure_dir(BUILD_DIR)
    # Configure with CMake (universal binary)
    cmake_cmd = ["cmake", "-S", str(PROJECT_ROOT), "-B", str(BUILD_DIR), "-DCMAKE_OSX_ARCHITECTURES=x86_64;arm64"]
    run(cmake_cmd)
    # Build the target `nsn`
    run(["cmake", "--build", str(BUILD_DIR), "--target", "nsn", "--config", "Release"])

# ---------------------------------------------------------------------------
# Step 2 – Create the .app bundle
# ---------------------------------------------------------------------------
def create_app_bundle():
    # Clean any previous bundle
    if APP_BUNDLE.exists():
        shutil.rmtree(APP_BUNDLE)
    # Standard macOS bundle layout
    contents = APP_BUNDLE / "Contents"
    macos = contents / "MacOS"
    resources = contents / "Resources"
    for p in (macos, resources):
        ensure_dir(p)
    # Copy the built binary (assumes `nsn` executable is in BUILD_DIR)
    binary_src = BUILD_DIR / "nsn"
    binary_dst = macos / "nsn"
    shutil.copy2(binary_src, binary_dst)
    # Minimal Info.plist (required for a bundle)
    plist = f"""
<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">
<plist version=\"1.0\">
<dict>
    <key>CFBundleName</key><string>NSN</string>
    <key>CFBundleExecutable</key><string>nsn</string>
    <key>CFBundleIdentifier</key><string>org.nsn.interpreter</string>
    <key>CFBundleVersion</key><string>1.0.0</string>
    <key>CFBundlePackageType</key><string>APPL</string>
    <key>LSMinimumSystemVersion</key><string>10.12</string>
</dict>
</plist>
"""
    (contents / "Info.plist").write_text(plist, encoding="utf-8")
    # Optional: copy a background image for the DMG later (if present)
    bg_src = PROJECT_ROOT / "Mac" / "Resources" / "dmg_background.png"
    if bg_src.exists():
        shutil.copy2(bg_src, resources / "background.png")

# ---------------------------------------------------------------------------
# Step 3 – Code sign the bundle
# ---------------------------------------------------------------------------
def sign_bundle():
    run(["codesign", "--deep", "--force", "--verify", "--verbose",
         "-s", CODE_SIGN_IDENTITY, str(APP_BUNDLE)])

# ---------------------------------------------------------------------------
# Step 4 – Create a DMG
# ---------------------------------------------------------------------------
def create_dmg():
    # Remove any existing DMG
    if DMG_PATH.exists():
        DMG_PATH.unlink()
    # Create a temporary writable image
    temp_img = BUILD_DIR / "temp.dmg"
    run(["hdiutil", "create", "-size", "100m", "-fs", "HFS+", "-volname", "NSN Installer", str(temp_img)])
    # Attach the image
    attach = subprocess.check_output(["hdiutil", "attach", "-readwrite", "-noverify", "-noautoopen", str(temp_img)], text=True)
    # Extract the device identifier (e.g., /dev/disk2s1)
    dev = attach.splitlines()[0].split()[0]
    # Copy the .app into the mounted volume
    mount_point = Path(f"/Volumes/NSN Installer")
    shutil.copytree(APP_BUNDLE, mount_point / "NSN.app")
    # Detach the image
    run(["hdiutil", "detach", dev])
    # Convert to a compressed read‑only DMG
    run(["hdiutil", "convert", str(temp_img), "-format", "UDZO", "-imagekey", "zlib-level=9", "-o", str(DMG_PATH)])
    temp_img.unlink()

# ---------------------------------------------------------------------------
# Step 5 – Optional notarization
# ---------------------------------------------------------------------------
def notarize():
    if not APPLE_NOTARIZE:
        return
    if not (NOTARIZE_USER and NOTARIZE_PASS):
        print("Apple notarization requested but credentials are missing.")
        return
    # Upload for notarization
    upload_cmd = ["xcrun", "altool", "--notarize-app", "-f", str(DMG_PATH),
                  "--primary-bundle-id", "org.nsn.interpreter", "-u", NOTARIZE_USER, "-p", NOTARIZE_PASS]
    run(upload_cmd)
    print("Notarization submitted. Check Apple Developer portal for status.")

# ---------------------------------------------------------------------------
# Main entry point
# ---------------------------------------------------------------------------
def main():
    try:
        build_interpreter()
        create_app_bundle()
        sign_bundle()
        create_dmg()
        notarize()
        print(f"✅ Installer created at {DMG_PATH}")
    except Exception as e:
        print(f"❌ Build failed: {e}", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()
