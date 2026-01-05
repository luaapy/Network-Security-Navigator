# NSN RPM Package

This directory contains the RPM spec file for building NSN on Red Hat, Fedora, and CentOS systems.

## Building the RPM

1. Create the source tarball:
   ```bash
   ./scripts/package.sh
   ```

2. Copy the tarball to your RPM sources directory:
   ```bash
   cp dist/nsn-1.0.0.tar.gz ~/rpmbuild/SOURCES/
   ```

3. Build the package:
   ```bash
   rpmbuild -ba pkg/rpm/nsn.spec
   ```
