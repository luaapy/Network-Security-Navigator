# NSN (Network Security Navigator)

<div align="center">

![NSN Logo](https://img.shields.io/badge/NSN-Network_Security_Navigator-blue?style=for-the-badge)

**A lightweight, high-performance programming language for network analysis, security auditing, and automation**

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/luaapy/Network-Security-Navigator/actions)
[![Termux](https://img.shields.io/badge/Termux-Ready-orange)](pkg/termux/)
[![Version](https://img.shields.io/badge/version-1.0.0-blue)](https://github.com/luaapy/Network-Security-Navigator/releases)

[Features](#-features) • [Installation](#-installation) • [Quick Start](#-quick-start) • [Documentation](#-documentation) • [Examples](#-examples) • [Contributing](#-contributing)

</div>

---

## Features
- **Lightweight** - Binary size < 5 MB
- **Fast** - Startup time < 50ms, low memory footprint
- **Built-in Network Tools** - ping, scan, DNS, HTTP, SSH
- **Security Focused** - Crypto, hashing, vulnerability scanning
- **Cross-Platform** - Linux, macOS, Windows, Android/Termux
- **Simple Syntax** - Easy to learn, powerful to use
- **Extensible** - C API for custom modules

---

## Installation
### Termux (Android) - Recommended
```bash
# Install from GitHub
pkg install git clang make autoconf automake libtool pkg-config -y
git clone https://github.com/luaapy/Network-Security-Navigator.git
cd Network-Security-Navigator
chmod +x pkg/termux/install-local.sh
./pkg/termux/install-local.sh
```

### Linux
```bash
# Ubuntu/Debian
sudo apt update
sudo apt install -y build-essential autoconf automake libtool pkg-config libpcap-dev libssl-dev libssh-dev
git clone https://github.com/luaapy/Network-Security-Navigator.git
cd Network-Security-Navigator/nsn
./configure --enable-optimizations && make -j$(nproc) && sudo make install
```

### macOS
```bash
# Using Homebrew
brew install autoconf automake libtool pkg-config libpcap openssl libssh
git clone https://github.com/luaapy/Network-Security-Navigator.git
cd Network-Security-Navigator/nsn
./configure --enable-optimizations && make -j$(sysctl -n hw.ncpu) && sudo make install
```

### Windows
```powershell
# Using PowerShell (Native)
git clone https://github.com/luaapy/Network-Security-Navigator.git
cd Network-Security-Navigator
.\BUILD_NATIVE.bat
```

---

## Quick Start

### Hello, Network!

```nsn
# hello.nsn
print "Hello, Network!"
ping 8.8.8.8
```

Run it:
```bash
nsn hello.nsn
```

### Simple Port Scan

```nsn
# scan.nsn
target = 192.168.1.1
result = scan target:80,443,22,8080

for port in result.open {
    print "Port", port, "is open"
}
```

---

## Documentation

- [Language Reference](Doc/reference/syntax.rst)
- [Standard Library API](Doc/api/network.rst)
- [Tutorials](Doc/tutorial/)
- [Examples](examples/)
- [Contributing Guide](CONTRIBUTING.md)

---

## Building from Source

### Requirements

- **C Compiler** - GCC 7+ or Clang 6+
- **Build Tools** - autoconf, automake, libtool, pkg-config
- **Optional Libraries** - libpcap, openssl, libssh

### Build Steps

```bash
# 1. Clone repository
git clone https://github.com/luaapy/Network-Security-Navigator.git
cd Network-Security-Navigator/nsn

# 2. Generate configure script
autoreconf -i

# 3. Configure build
./configure --enable-optimizations --enable-static

# 4. Compile
make -j$(nproc)

# 5. Run tests
make test

# 6. Install
sudo make install
```

---

## Contributing

We welcome contributions! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

---

## License

NSN is licensed under the **MIT License** - see [LICENSE](LICENSE) for details.

---

<div align="center">

**Made by Nosan**

Star this repo if you find it useful!

</div>
