#!/bin/bash
# NSN Installation Script
set -e

PREFIX=${1:-/usr/local}

echo "Installing NSN to $PREFIX..."

# Create directories
mkdir -p "$PREFIX/bin"
mkdir -p "$PREFIX/lib/nsn"
mkdir -p "$PREFIX/include/nsn"

# Copy binary
if [ -f "nsn" ]; then
    cp nsn "$PREFIX/bin/"
    chmod +x "$PREFIX/bin/nsn"
else
    echo "Error: nsn binary not found. Run ./scripts/build.sh first."
    exit 1
fi

# Copy standard library
cp -r Lib/* "$PREFIX/lib/nsn/"

# Copy headers
cp Include/nsn.h "$PREFIX/include/nsn/"
cp -r Include/core "$PREFIX/include/nsn/"

echo "NSN successfully installed!"
