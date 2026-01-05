#!/bin/bash
# NSN Packaging Script
# Creates a distribution tarball

VERSION=$(grep "NSN_VERSION" nsnconfig.h.in | cut -d '"' -f 2)
NAME="nsn-$VERSION"

echo "Creating package $NAME.tar.gz..."

mkdir -p "dist/$NAME"

# Copy essential files
cp -r Include Lib Modules Nsn Objects Parser Programs scripts "dist/$NAME/"
cp Makefile.pre.in configure.ac nsnconfig.h.in README.md LICENSE "dist/$NAME/"

cd dist
tar -czf "$NAME.tar.gz" "$NAME"
rm -rf "$NAME"

echo "Package created in dist/$NAME.tar.gz"
