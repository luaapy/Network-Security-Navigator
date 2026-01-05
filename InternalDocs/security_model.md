# NSN Security Model Documentation

The NSN interpreter is designed to run untrusted scripts that interact with networks, filesystems, and system resources.  To protect the host environment, NSN implements a **defense‑in‑depth security model** that combines **sandboxing**, **capability‑based permissions**, **exception handling**, and **runtime configuration**.

---

## 1. Threat Model
| Threat | Description |
|--------|-------------|
| **Malicious script** | A script supplied by a user that attempts to read/write arbitrary files, open network connections to prohibited hosts, or exhaust system resources. |
| **Privilege escalation** | The script may try to invoke native extensions that call OS APIs directly. |
| **Denial‑of‑service** | Excessive CPU, memory, or network usage that could degrade the host. |
| **Data leakage** | Access to sensitive data (e.g., credentials) stored on the host. |

The security model aims to mitigate these threats while still allowing powerful network‑automation capabilities.

---

## 2. Sandbox Flag (`sandbox_enabled`)
The primary runtime switch is `sandbox_enabled` in `nsnconfig.h`.  When enabled:
1. **Filesystem access** is restricted to a whitelist of directories defined by `allowed_dirs` (comma‑separated absolute paths).  Any attempt to open a file outside this set raises `NsnExc_PermissionError`.
2. **Network access** is limited to hosts/ports listed in `allowed_hosts` (also a comma‑separated list of `host:port` patterns).  DNS resolution for non‑whitelisted hosts fails with `NsnExc_NetworkError`.
3. **Process creation** (`os.exec*`‑like functions) is disabled entirely.
4. **Environment variables** are hidden; the script sees an empty environment unless explicitly injected via `Nsn_Config_SetEnv`.

The sandbox can be toggled at runtime via `Nsn_Config_Apply()` after modifying the global `NsnConfig` object.

---

## 3. Capability‑Based Permissions
Beyond the binary sandbox flag, NSN supports fine‑grained capabilities that modules can request during initialization:
```c
int Nsn_Capability_Request(const char *cap_name);
```
Supported capabilities include:
* `CAP_NETWORK_RAW` – Allows raw socket creation (required for ICMP, packet capture).  Only granted on platforms where the interpreter runs with elevated privileges.
* `CAP_FILE_WRITE` – Enables writing to files outside the sandbox whitelist (useful for logging).  Must be explicitly approved by the embedding application.
* `CAP_SYSTEM_INFO` – Access to system information (e.g., `os.uname`).

If a capability is denied, the corresponding API call raises `NsnExc_CapabilityError`.

---

## 4. Exception Hierarchy for Security
All security‑related errors inherit from a common base exception `NsnExc_SecurityError` defined in `errors.c`.  The hierarchy is:
```
SecurityError (base)
├─ PermissionError
├─ NetworkError
├─ CapabilityError
└─ SandboxViolationError
```
Scripts can catch these exceptions using `try … catch` blocks, allowing graceful degradation or user‑friendly error messages.

---

## 5. Resource Limits
The interpreter enforces hard limits to prevent DoS attacks:
```c
#ifndef NSN_MAX_MEMORY
#define NSN_MAX_MEMORY (256 * 1024 * 1024)   // 256 MiB per interpreter instance
#endif

#ifndef NSN_MAX_RECURSION_DEPTH
#define NSN_MAX_RECURSION_DEPTH 1024
#endif
```
* **Memory** – The arena allocator checks against `max_memory` in the global config; exceeding it triggers `NsnExc_MemoryError`.
* **Recursion** – The VM tracks call‑stack depth; exceeding `max_recursion_depth` raises `NsnExc_RecursionError`.
* **CPU time** – An optional watchdog (enabled via `NSN_ENABLE_WATCHDOG`) can interrupt scripts that run longer than a configurable threshold.

---

## 6. Auditing & Logging
When `log_level` ≥ 3 (info) the interpreter emits security‑relevant events via `NSN_LOG_INFO`:
* File open attempts (including success/failure and resolved path).
* Network connection attempts (host, port, protocol).
* Capability requests and their outcomes.

Logs can be directed to a file (`log_file` in `NsnConfig`) or to stdout.  The `NSN_LOG_DEBUG` macro provides even more granular details for developers.

---

## 7. Embedding API for Host Applications
An embedding application can:
1. **Create a sandboxed interpreter**:
   ```c
   NsnConfig *cfg = Nsn_GetConfig();
   cfg->sandbox_enabled = 1;
   cfg->allowed_dirs = "C:/nsn/scripts,/tmp";
   cfg->allowed_hosts = "192.168.1.0/24,10.0.0.0/8";
   Nsn_Config_Apply();
   ```
2. **Grant selective capabilities** before running untrusted code:
   ```c
   Nsn_Capability_Request("CAP_NETWORK_RAW"); // may return 0 (granted) or -1 (denied)
   ```
3. **Capture security events** via a custom log handler:
   ```c
   void my_log_handler(int level, const char *msg) { /* forward to host logger */ }
   Nsn_SetLogHandler(my_log_handler);
   ```

---

## 8. Testing the Security Model
* **Unit tests** (`tests/security/`) verify that forbidden operations raise the correct exceptions.
* **Fuzz tests** (`Modules/_network/fuzz.c`) attempt to trigger sandbox bypasses by feeding malformed inputs.
* **CI pipeline** runs the test suite on Linux, macOS, and Windows with the sandbox both enabled and disabled to ensure consistent behaviour.

---

## 9. Future Enhancements
* **Capability negotiation** with external policy engines (e.g., SELinux, AppArmor). 
* **Fine‑grained network policies** using CIDR ranges and protocol filters.
* **Dynamic sandbox reconfiguration** without interpreter restart (currently requires `Nsn_Config_Apply`).

---

*Keep this document up‑to‑date with any changes to `nsnconfig.h`, the exception hierarchy, or the sandbox implementation.*
