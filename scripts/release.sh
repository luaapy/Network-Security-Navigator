#!/bin/bash
# NSN (Network Security Navigator)
# Automated Release Script

set -e

VERSION=$(grep "NSN_VERSION" Include/nsn.h | awk '{print $3}' | tr -d '"')

echo "Preparing release v$VERSION..."

# 1. Run tests
./scripts/test.sh

# 2. Package artifacts
./scripts/package.sh

# 3. Tagging (optional, requires git)
if [ -d ".git" ]; then
    echo "Tagging release..."
    git tag -a "v$VERSION" -m "NSN Release $VERSION"
fi

echo "Release v$VERSION prepared successfully."
