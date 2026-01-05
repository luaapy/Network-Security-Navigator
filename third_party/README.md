# Third-Party Libraries

The NSN project utilizes the following third-party libraries to provide advanced networking and security features:

## 1. OpenSSL
- **Purpose**: Provides robust cryptographic primitives (SHA256, RSA), SSL/TLS socket wrapping, and secure random number generation.
- **License**: Apache License 2.0 / OpenSSL License
- **URL**: [https://www.openssl.org](https://www.openssl.org)

## 2. libpcap / WinPcap
- **Purpose**: Essential for raw packet capturing, packet crafting, and link-layer network analysis.
- **License**: BSD 3-Clause
- **URL**: [https://www.tcpdump.org](https://www.tcpdump.org)

## 3. libssh
- **Purpose**: Enables secure remote service auditing and automation over SSH protocols.
- **License**: LGPL 2.1
- **URL**: [https://www.libssh.org](https://www.libssh.org)

## 4. libuv (Optional/Internal)
- **Purpose**: Asynchronous I/O support for high-concurrency scanning operations.
- **License**: MIT
- **URL**: [https://libuv.org](https://libuv.org)

---
All third-party source code is maintained in separate subdirectories (if vendored) or linked dynamically via the system package manager during the build process. See `LICENSE` for details on NSN's primary licensing terms.
