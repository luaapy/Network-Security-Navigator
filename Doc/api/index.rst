NSN C API Reference
===================

The NSN C API allows C/C++ developers to extend the NSN language with new modules or embed the NSN interpreter into existing applications.

.. toctree::
   :maxdepth: 2
   :caption: C API:

   core
   network
   security

Overview
--------
The API follows a reference-counting model similar to CPython. Every `nsn_object` must be managed using the `nsn_incref` and `nsn_decref` macros.

Core API
--------
- Object creation and manipulation
- Memory management (Arena allocator)
- Virtual Machine control

Extending NSN
-------------
- Defining new types
- Implementing module functions
- Argument parsing with `nsn_get_args`
