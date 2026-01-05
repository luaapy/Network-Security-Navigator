# Frequently Asked Questions (FAQ)

.. _faq:

.. contents:: Table of Contents
   :depth: 2
   :local:

What is NSN?
------------
NSN (Network Security Navigator) is a high‑performance, cross‑platform programming language designed for network security research, auditing, and automation.  It combines a Python‑like syntax with native C extensions for low‑level packet handling, cryptography, and parallel scanning.

How do I install NSN?
----------------------
The easiest way is to use the pre‑built binaries or install from source:

* **Linux/macOS** – ``curl -L https://nsn-lang.org/install.sh | bash``
* **Windows** – Download the ``nsn.exe`` from the latest GitHub Release and add it to your ``PATH``.
* **From source** – Clone the repository and run ``./scripts/build.sh`` which will invoke CMake and produce the ``nsn`` executable.

Can I use NSN on Android or iOS?
--------------------------------
Yes.  The project provides NDK/Gradle scripts for Android and Xcode projects for iOS.  See ``Android/README.md`` and ``Apple/README.md`` for detailed build instructions.

How do I run an NSN script?
----------------------------
``nsn run path/to/script.nsn``

You can also start an interactive REPL with ``nsn`` alone.

Where can I find the standard library?
--------------------------------------
All standard library modules are located under ``Lib/`` and are written in NSN itself.  They are automatically available when you import them, e.g. ``import network.tcp``.

How do I contribute?
--------------------
Please read ``CONTRIBUTING.md``.  In short:

1. Fork the repository.
2. Create a feature branch.
3. Write tests for your changes.
4. Submit a pull request.

What license is NSN released under?
-----------------------------------
NSN is licensed under the MIT License.  See ``LICENSE`` for the full text.

Where can I report bugs or request features?
-------------------------------------------
Use the GitHub issue templates located in ``.github/ISSUE_TEMPLATE`` – choose *Bug report* for bugs and *Feature request* for new ideas.

Is there a community or chat?
-----------------------------
Join the ``#nsn`` channel on the official Discord server (link in the README) or follow the mailing list at ``nsn@lists.example.org``.
