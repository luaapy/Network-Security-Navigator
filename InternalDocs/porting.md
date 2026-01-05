# Porting NSN to New Platforms

NSN is designed for high portability.

## Core Dependencies
- Standard C99 compiler and library.
- POSIX threads (optional but recommended).
- BSD sockets or equivalent.

## Porting Steps
1. Define platform-specific macros in `nsnconfig.h`.
2. Implement low-level networking in `Modules/_network/`.
3. Configure the build system (CMake or Autotools).
4. Verify core functionality with `tests/unit/`.

## Target Environments
- **POSIX**: Linux, macOS, BSD.
- **Windows**: Requires Winsock2.
- **Android**: Supported via NDK and Termux.
- **Embedded**: Minimal builds can be achieved by disabling optional modules (SSL, PCAP).
