NSN Windows Build Guide
=======================

This directory contains Windows-specific source files and build
configurations for the MSVC compiler.

Building with MSVC
------------------

1. Open the solution in `PCbuild/nsn.sln`.
2. Ensure you have the Windows SDK and OpenSSL installed.
3. Build the 'nsn' project.

Windows Specific Modules
------------------------

* `msvcrtmodule.c`: Interface to the Microsoft Visual C Runtime.
* `winreg.c`: Interface to the Windows Registry.
* `winsound.c`: Interface to the Windows Sound API.
