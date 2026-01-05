#!/bin/bash
# NSN (Network Security Navigator)
# Build Cleanup Script

echo "Cleaning up NSN build artifacts..."

# Remove build directory
rm -rf build/
rm -rf dist/

# Remove generated files in core
rm -f Nsn/stdlib_modules.h
rm -f Nsn/frozen.s
rm -f nsn
rm -f nsn.exe

# Remove Python cache
find . -type d -name "__pycache__" -exec rm -rf {} +
find . -type f -name "*.pyc" -delete

# Remove documentation build
rm -rf Doc/_build/

# Remove autotools artifacts if they exist
rm -rf autom4te.cache/
rm -f config.log config.status
rm -f Makefile

echo "Cleanup complete."
