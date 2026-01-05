NSN NEWS.d Directory
====================

This directory contains news entry files which are used to generate the
changelog for NSN releases. Each file represents a single change and is
categorized into subdirectories based on its impact.

Subdirectories
--------------

* `Core and Builtins`: Changes to the core interpreter or built-in types.
* `Library`: Changes to the NSN standard library modules.
* `Networking`: Improvements or fixes to the networking subsystem.
* `Security`: Security-related fixes and improvements.
* `Documentation`: Updates to the documentation.
* `Tests`: New tests or improvements to the test suite.
* `Build`: Changes to the build system (CMake, etc.).

Adding a News Entry
-------------------

To add a news entry, create a file in the appropriate subdirectory with a
unique name (e.g., `IssueID.category.nonce.rst`). The file should contain
a brief description of the change in RST format.

Example: `123.Security.aB12.rst`

.. code-block:: rst

   Fixed a buffer overflow in the ICMP packet parser when handling malformed
   echo reply packets.

Generation
----------

The final `NEWS` file is generated during the release process by collecting
all files from these subdirectories and sorting them. Once a release is tagged,
the entries are typically moved or archived.
