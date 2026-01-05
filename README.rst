NSN (Network Security Navigator)
===============================

.. image:: https://github.com/luaapy/Network-Security-Navigator/actions/workflows/build.yml/badge.svg
   :target: https://github.com/luaapy/Network-Security-Navigator/actions/workflows/build.yml
   :alt: Build Status

A specialized lightweight language for network analysis, security auditing, and network automation.

Features
--------

* **First-Class Networking Types**: IP addresses, MAC addresses, and networks are native data types.
* **Low-Level Port Scanning**: Built-in optimized TCP/UDP port scanning.
* **Security Auditing**: Modules for service fingerprinting and vulnerability checking.
* **Lightweight**: Minimal runtime footprint and fast execution.

Quick Start
-----------

.. code-block:: bash

    mkdir build && cd build
    cmake ..
    make
    ./nsn examples/basic/01_hello_ping.nsn

Installation
------------

NSN can be installed on various platforms including Linux, macOS, and Android (via Termux).

.. code-block:: bash

    ./scripts/install.sh

License
-------

MIT License. See the `LICENSE` file for more details.
