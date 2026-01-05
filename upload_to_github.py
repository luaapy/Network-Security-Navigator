import os
import subprocess
import sys

def run_command(command, cwd=None):
    """Run a shell command and print status."""
    try:
        # Hide sensitive token in command printing
        display_cmd = command
        if "@github.com" in command:
            parts = command.split("@")
            display_cmd = "git remote add origin https://***@github.com" + parts[1].split("github.com")[1]
            
        subprocess.run(
            command,
            cwd=cwd,
            shell=True,
            check=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        print(f"✅ Success: {display_cmd}")
        return True
    except subprocess.CalledProcessError as e:
        # Ignore errors for things like 'remote remove' if it doesn't exist
        if "No such remote" in e.stderr:
            return True
        if "nothing to commit" in e.stdout:
            print("ℹ️  Nothing to commit (already clean).")
            return True
            
        print(f"❌ Error: {e.stderr.strip()}")
        return False

def main():
    print("========================================")
    print("   🚀 NSN GitHub Uploader")
    print("========================================")
    
    # 1. CONFIGURATION
    username = "luaapy"
    repo_name = "Network-Security-Navigator"
    
    # Get Token
    print("\nTo upload, we need your GitHub Personal Access Token.")
    
    token = input("\n🔑 Paste your GitHub Token here: ").strip()
    
    if not token:
        print("Error: Token cannot be empty.")
        return

    # Construct Authenticated URL
    # Format: https://TOKEN@github.com/user/repo.git
    remote_url = f"https://{token}@github.com/{username}/{repo_name}.git"
    current_dir = os.getcwd()

    print(f"\n📂 Uploading from: {current_dir}")
    print(f"🔗 Target Repo:    https://github.com/{username}/{repo_name}")
    
    # 2. GIT OPERATIONS
    print("\n--- Starting Upload ---")

    # Configure Git Identity (Fixes "Author identity unknown")
    print("Configuring Git Identity to default...")
    run_command('git config --global user.email "bot@nsn.org"')
    run_command('git config --global user.name "NSN Uploader"')

    # Initialize if needed
    if not os.path.exists(os.path.join(current_dir, ".git")):
        print("Initializing Git...")
        run_command("git init")

    # Add all files
    print("Prepping files...")
    run_command("git add .")
    
    # Commit with User Explanation
    explanation = input("\n📝 Enter commit explanation (e.g. 'Initial Release'): ").strip()
    if not explanation:
        explanation = "Update NSN project files"
        
    print("Committing changes...")
    run_command(f'git commit -m "{explanation}"')
    
    # Rename branch to main
    run_command("git branch -M main")
    
    # Setup Remote
    print("Configuring remote server...")
    run_command("git remote remove origin") # Clean slate
    if not run_command(f"git remote add origin {remote_url}"):
        print("Failed to configure remote.")
        return

    # Push
    print("\n⬆️  Pushing to GitHub (this might take a few seconds)...")
    if run_command("git push -u origin main --force"):
        print("\n========================================")
        print("🎉 SUCCESS! Your project is online.")
        print(f"👉 View it here: https://github.com/{username}/{repo_name}")
        print("========================================")
    else:
        print("\n❌ Push failed. Check your token permissions or internet connection.")

if __name__ == "__main__":
    main()
