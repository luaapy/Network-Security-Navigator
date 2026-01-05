#!/bin/bash
# NSN (Network Security Navigator)
# Main Build Script

set -e

# Default build type
BUILD_TYPE=${1:-Release}

echo "Building NSN ($BUILD_TYPE)..."

# 1. Generate core headers/indices
echo "Generating internal headers..."
python3 Tools/scripts/generate_opcode_h.py
python3 Tools/scripts/generate_token.py
python3 Tools/scripts/generate_stdlib_module_names.py

# 2. Use CMake to build
mkdir -p build
cd build

# Check if we should use specialized flags
CMAKE_FLAGS=""
if [[ "$OSTYPE" == "darwin"* ]]; then
    # MacOS specific
    CMAKE_FLAGS="-DCMAKE_OSX_ARCHITECTURES=arm64;x86_64"
fi

cmake .. -DCMAKE_BUILD_TYPE=$BUILD_TYPE $CMAKE_FLAGS
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 1)

# 3. Copy binary back to root for convenience
cp nsn ../ 2>/dev/null || cp nsn.exe ../ 2>/dev/null || true

cd ..

echo "---------------------------------------"
if [ -f "nsn" ] || [ -f "nsn.exe" ]; then
    echo "NSN build successful!"
    ./nsn --version
else
    echo "NSN build failed: binary not found."
    exit 1
fi
