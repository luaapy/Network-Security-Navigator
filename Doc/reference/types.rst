Standard Type Hierarchy
=======================

Every value in NSN is an object and has a type.

Core types
----------

- **int**: Arbitrary precision integers.
- **float**: Double-precision floating point numbers.
- **string**: UTF-8 encoded sequences of characters.
- **bool**: True and False objects.
- **null**: The null object.

Collection Types
----------------

- **list**: Mutable sequences of objects.
- **dict**: Mapping of keys to values (hash table).
- **bytes**: Immutable sequence of raw bytes.

Networking Types
----------------

- **ipaddr**: Represents an IPv4 or IPv6 address.
- **network**: Represents a CIDR network block.
- **port**: Represents a network port and its state.
- **packet**: Represents a raw network packet for analysis.
