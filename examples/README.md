# NSN Example Scripts

This directory contains a collection of example NSN scripts that demonstrate various features of the language.  The examples are organized by difficulty and use‑case:

## Basic
- **hello_world.nsn** – The classic "Hello, World!" program.
- **variables.nsn** – Demonstrates variable assignment and basic types.
- **control_flow.nsn** – Shows `if`, `while`, and `for` constructs.
- **functions.nsn** – Defines and calls user functions.
- **modules.nsn** – Imports and uses standard library modules.

## Advanced
- **network_scan.nsn** – Uses the `security.scanner` module to perform a port scan.
- **http_fetch.nsn** – Retrieves a web page using the `network.http` module.
- **crypto_demo.nsn** – Shows hashing and encryption primitives.
- **concurrency.nsn** – Demonstrates threading with the `thread` module.
- **custom_module.nsn** – Shows how to write and import a custom NSN module.

## Intermediate
- **13_vulnerability_scan.nsn** – Performs a simple vulnerability scan against a target host.
- **12_packet_analysis.nsn** – Parses raw packets using the `network.packet` module.
- **11_dns_lookup.nsn** – Demonstrates DNS resolution and reverse lookup.
- **10_tcp_handshake.nsn** – Shows a full TCP three‑way handshake.
- **09_icmp_ping.nsn** – Sends ICMP echo requests and measures latency.

## Real‑World
- **web_crawler.nsn** – Crawls a website and extracts links.
- **ssh_bruteforce.nsn** – Demonstrates an SSH login brute‑force (educational only).
- **malware_analysis.nsn** – Uses the `security.audit` module to fingerprint a binary.
- **network_monitor.nsn** – Captures live traffic with `libpcap` bindings.

Each script can be run with:

```bash
nsn run examples/<category>/<script_name>.nsn
```

Feel free to explore, modify, and extend these examples.  Contributions are welcome – add new scripts to the appropriate subdirectory and update this README.
