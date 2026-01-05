# NSN Network Internals Documentation

This document describes the **internal architecture** of the networking subsystem in NSN.  All network‑related functionality lives in the `Modules/_network/` directory and is exposed to scripts through the public headers in `Include/network/`.  The design balances **cross‑platform portability**, **high performance**, and **extensibility** for future protocols.

---

## 1. High‑Level Overview

| Layer | Description |
|-------|-------------|
| **Public API** (`Include/network/*.h`) | Header files that script writers import (`import socket`, `import http`, etc.).  They expose opaque `nsn_object *` constructors and a small set of operations. |
| **C Extension Modules** (`Modules/_network/`) | Implementations written in C for speed.  Each module registers its functions with the interpreter during `nsn_module_init`. |
| **Platform Abstraction** (`Modules/_network/platform/`) | Thin wrappers that map POSIX socket calls to Winsock on Windows, and provide a unified API (`nsn_socket_*`). |
| **Core Utilities** (`core/memory.h`, `core/object.h`) | Allocate and manage the `nsn_object` structures that represent sockets, packets, etc. |

---

## 2. Core Types

| Type | Header | Purpose |
|------|--------|---------|
| `nsn_socket_object` | `socketmodule.c` | Represents a generic socket (TCP/UDP). Holds the native file descriptor (`int fd` on POSIX, `SOCKET` on Windows) and the address family. |
| `nsn_tcp_object` | `tcpmodule.c` | Sub‑class of `nsn_socket_object` that provides `connect`, `send`, `recv`, and `close` semantics for stream‑oriented communication. |
| `nsn_udp_object` | `udpmodule.c` | Sub‑class of `nsn_socket_object` for datagram communication. |
| `nsn_icmp_object` | `icmpmodule.c` | Minimal socket used for raw ICMP packets (ping, traceroute). |
| `nsn_http_object` | `httpmodule.c` | Simple HTTP client that internally creates a TCP socket, performs request formatting, and parses the response into a dictionary‑like object. |
| `nsn_dns_object` | `dnsmodule.c` | Wrapper around `getaddrinfo`/`getnameinfo` for forward and reverse DNS lookups. |
| `nsn_packet_object` | `packetmodule.c` | Holds raw packet bytes and provides helper functions for field extraction (e.g., Ethernet, IP, TCP headers). |

All these types inherit from the base `nsn_object` defined in `core/object.h`, which provides reference counting and a pointer to a `nsn_type` describing the object's behaviour.

---

## 3. Platform Abstraction Layer

The file `Modules/_network/platform.h` defines a unified interface:
```c
int nsn_platform_socket(int domain, int type, int protocol);
int nsn_platform_connect(int fd, const struct sockaddr *addr, socklen_t addrlen);
ssize_t nsn_platform_send(int fd, const void *buf, size_t len, int flags);
ssize_t nsn_platform_recv(int fd, void *buf, size_t len, int flags);
int nsn_platform_close(int fd);
```
* On **POSIX** systems these map directly to the standard BSD socket API.
* On **Windows** they translate to Winsock calls (`socket`, `connect`, `send`, `recv`, `closesocket`) and perform the required `WSAStartup`/`WSACleanup` handling in `platform_win.c`.
* The abstraction also normalises error codes, converting platform‑specific `errno`/`WSAGetLastError` values into NSN exceptions (`NsnExc_NetworkError`).

---

## 4. Initialization & Registration

Each network module implements an `nsn_module_init` function that is called by the interpreter during start‑up (see `nsn_module_new` in `core/module.c`).  Example for the socket module:
```c
int nsn_socket_module_init(void) {
    nsn_object *mod = nsn_module_new("socket");
    nsn_module_add_function(mod, "new", nsn_socket_new);
    nsn_module_add_function(mod, "bind", nsn_socket_bind);
    nsn_module_add_function(mod, "listen", nsn_socket_listen);
    nsn_module_add_function(mod, "accept", nsn_socket_accept);
    nsn_module_add_function(mod, "connect", nsn_socket_connect);
    nsn_module_add_function(mod, "close", nsn_socket_close);
    return Nsn_ImportModuleObject(mod);
}
```
The module object is then inserted into the interpreter’s built‑in module table, making it available to scripts via `import socket`.

---

## 5. Error Handling & Exceptions

All platform calls are wrapped with `Nsn_Err_SetFromErrno` (POSIX) or `Nsn_Err_SetFromWinError` (Windows).  The wrapper translates the native error into one of the following exception types (declared in `errors.c`):
* `NsnExc_NetworkError`
* `NsnExc_TimeoutError`
* `NsnExc_PermissionError`
These exceptions propagate through the VM just like Python exceptions, allowing user scripts to `try … catch` network failures.

---

## 6. Performance Optimisations
1. **Zero‑Copy I/O** – When receiving data into an `nsn_packet_object`, the module allocates the buffer directly from the arena allocator (`NsnArena_Alloc`) to avoid an extra `memcpy`.  The packet object then takes ownership of the buffer.
2. **Fast‑Path Functions** – Critical paths (e.g., `nsn_socket_send` for small buffers) bypass the generic `nsn_object` wrapper and call the platform function directly after a quick type check.
3. **Thread‑Local Sockets** – When POSIX threads are enabled, each thread gets its own socket cache to reduce contention on global state.
4. **DNS Caching** – The DNS module maintains an LRU cache (size configurable via `nsnconfig.h`) to avoid repeated `getaddrinfo` calls for the same hostname.

---

## 7. Extending the Network Stack
To add a new protocol (e.g., QUIC or a custom binary protocol):
1. **Create a new C module** under `Modules/_network/` (e.g., `quicmodule.c`).
2. Define a new `nsn_quic_object` that embeds `nsn_socket_object` or uses raw sockets.
3. Implement the required operations (`connect`, `send`, `recv`, `close`).
4. Register the module in `nsn_module_init` and expose the functions to the interpreter.
5. Update `Include/network/quic.h` with the public API and add it to the top‑level `nsn.h` includes if you want it globally available.

---

## 8. Testing & Validation
* **Unit tests** live in `tests/network/` and cover each public function with both POSIX and Windows builds (CI runs on all three platforms).  Tests use the `nsn_socketpair` helper on POSIX and a loopback Winsock socket on Windows.
* **Fuzzing** – The `Modules/_network/fuzz.c` target feeds random byte streams into the packet parser to ensure robust handling of malformed packets.
* **Benchmarking** – `benchmarks/network_benchmark.nsn` measures latency for TCP connect, UDP send/receive, and HTTP GET across platforms.

---

## 9. Documentation Generation
The public headers contain Doxygen‑style comments.  Running `make docs` (Sphinx) extracts these comments into the `Doc/reference/network.rst` page, which is linked from the main API reference.

---

*Keep this document in sync with any changes to the network modules, platform abstraction, or configuration flags.*
