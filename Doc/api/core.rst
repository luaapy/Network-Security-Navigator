Core C API
==========

Object Management
-----------------

Every object in NSN is a pointer to an `nsn_object` structure.

Reference Counting
~~~~~~~~~~~~~~~~~~
NSN uses manual reference counting for memory management.

- `nsn_incref(nsn_object *obj)`: Increase reference count.
- `nsn_decref(nsn_object *obj)`: Decrease reference count. If zero, deallocate.

Common Object Creation
~~~~~~~~~~~~~~~~~~~~~~
- `nsn_int_from_long(long val)`
- `nsn_string_from_cstring(const char *s)`
- `nsn_list_new()`

Virtual Machine
---------------

Executing Code
~~~~~~~~~~~~~~
- `nsn_eval_code(nsn_object *code, nsn_object *globals)`
- `nsn_run_file(const char *path)`
