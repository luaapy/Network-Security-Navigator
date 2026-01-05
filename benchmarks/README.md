# README.md

# NSN Benchmarks

This directory contains a collection of benchmark scripts written in the NSN language. The scripts are designed to measure the performance of core functionality provided by the NSN standard library.

## Available Benchmarks

- **`crypto_benchmark.nsn`** – Measures hash function throughput (SHA‑256, SHA‑1, MD5).
- **`network_benchmark.nsn`** – Measures latency and throughput for ping, TCP connections, and HTTP GET requests.
- **`scan_benchmark.nsn`** – Measures the speed of the built‑in port scanner across a range of ports.

## Running Benchmarks

```bash
nsn run benchmarks/crypto_benchmark.nsn
nsn run benchmarks/network_benchmark.nsn
nsn run benchmarks/scan_benchmark.nsn
```

Adjust the iteration counts inside each script to suit your hardware. The output will report operations per second for each tested operation.
