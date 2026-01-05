#!/bin/bash
# NSN (Network Security Navigator)
# DevContainer Setup Script

set -e

echo "Starting NSN development environment setup..."

# 1. Update and install system dependencies
# These are usually in the Dockerfile, but keeping here for redundancy/local use
sudo apt-get update
sudo apt-get install -y \
    build-essential \
    autoconf \
    automake \
    libtool \
    libpcap-dev \
    libssl-dev \
    libssh-dev \
    cmake \
    git \
    python3 \
    python3-pip \
    clang-format \
    clang-tidy

# 2. Install Python dependencies for tools and docs
if [ -f "Doc/requirements.txt" ]; then
    pip3 install -r Doc/requirements.txt
fi

# 3. Initialize git hooks if in a git repo
if [ -d ".git" ]; then
    git config core.hooksPath .githooks || true
fi

# 4. Make all scripts executable
chmod +x scripts/*.sh

echo "Setup complete. You are ready to build NSN!"
./scripts/build.sh --version
