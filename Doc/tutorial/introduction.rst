Introduction to NSN
===================

What is NSN?
------------
NSN (Network Security Navigator) is a specialized, lightweight programming language designed specifically for network analysis, security auditing, and network automation.

In the world of network security, professionals often find themselves switching between different tools like Python (with Scapy), Bash (with Nmap/Netcat), and specialized scanners. NSN aims to consolidate these tasks into a single, high-performance, and intuitive language.

Design Philosophy
-----------------
* **Networking First**: IP addresses, networks, and packets aren't just strings; they are first-class data types.
* **Speed and Portability**: Written in clean-room C99 with a minimal executable size and low memory footprint.
* **Security Focused**: Built-in primitives for scanning, fingerprinting, and cryptographic operations.
* **Simplicity**: A syntax that feels familiar to Python and C users, but optimized for networking tasks.

Key Features
------------
1. **Native IP Types**: `192.168.1.1` and `10.0.0.0/24` are literal values.
2. **Integrated Scanning**: Perform port scans directly with the `scan` keyword.
3. **Deep Packet Inspection**: Capture and analyze raw packets with ease.
4. **Cross-Platform**: Runs natively on Linux, Windows, macOS, and Android (Termux).

Next Steps
----------
Ready to get started? Head over to the :doc:`basics` tutorial to learn the core syntax of NSN.
