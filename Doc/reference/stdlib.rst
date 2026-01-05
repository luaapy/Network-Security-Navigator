Standard Library Reference
==========================

The NSN standard library is organized into modules.

Built-in Functions
------------------

- `print(args...)`: Output objects to the standard output.
- `len(obj)`: Return the length of a collection or bytes.
- `type(obj)`: Return the type name of an object.

The `net` Module
----------------

- `net.scan(target, ports)`: Perform a port scan.
- `net.ping(target)`: Check host reachability.
- `net.resolve(hostname)`: Perform DNS resolution.

The `security` Module
---------------------

- `security.hash.sha256(data)`: Compute SHA-256 hash.
- `security.crypto.encrypt(data, key)`: Encrypt data.
