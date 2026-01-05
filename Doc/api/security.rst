# Security API Documentation

.. _security-api:

Security Module Overview
=======================

The **security** package provides native primitives for security‑related operations in NSN.  It is implemented in C for high performance and exposed to the language as a standard library module.

Modules
-------

- ``security.scanner`` – High‑performance port scanner.  Implements the ``scan`` keyword and provides a ``Scanner`` object with methods to configure timeouts, retries, and stealth mode.
- ``security.hash`` – Cryptographic hash functions.  Functions ``sha256``, ``sha1`` and ``md5`` return a hexadecimal string representing the digest of the supplied data.
- ``security.ssl`` – TLS/SSL wrapper for sockets.  ``wrap_socket`` upgrades a raw ``socket`` object to an encrypted channel.
- ``security.crypto`` – Thin bindings to OpenSSL for symmetric and asymmetric encryption.  Functions include ``aes_encrypt``, ``aes_decrypt``, ``rsa_encrypt`` and ``rsa_decrypt``.

Key Functions
-------------

``security.scanner.scan(host: str, ports: str) -> dict``
    Perform a TCP connect scan on ``host`` for the port range expressed in ``ports`` (e.g. ``"1-1024"``).  Returns a dictionary mapping each open port to a ``{"status": "open"}`` entry.

``security.hash.sha256(data: str) -> str``
    Compute the SHA‑256 digest of ``data`` and return the hexadecimal representation.

``security.hash.sha1(data: str) -> str``
    Compute the SHA‑1 digest of ``data``.

``security.hash.md5(data: str) -> str``
    Compute the MD5 digest of ``data``.

``security.ssl.wrap_socket(sock: socket) -> socket``
    Upgrade a plain ``socket`` object to an SSL/TLS encrypted socket.  The returned object supports the same ``send``/``recv`` methods as a regular socket.

``security.crypto.aes_encrypt(key: bytes, plaintext: bytes) -> bytes``
    Encrypt ``plaintext`` using AES‑256‑CBC with ``key``.  Returns the ciphertext.

``security.crypto.aes_decrypt(key: bytes, ciphertext: bytes) -> bytes``
    Decrypt ``ciphertext`` using AES‑256‑CBC with ``key``.

Examples
--------

Port scanning::

    import security.scanner as scanner
    result = scanner.scan("192.168.1.1", "1-1024")
    print(result)

Hashing::

    import security.hash as hash
    print(hash.sha256("hello world"))

TLS socket::

    import network.tcp as tcp
    import security.ssl as ssl
    s = tcp.connect("example.com", 443)
    secure = ssl.wrap_socket(s)
    secure.send("GET / HTTP/1.1\r\nHost: example.com\r\n\r\n")
    print(secure.recv(1024))

Encryption::

    import security.crypto as crypto
    key = crypto.random_bytes(32)
    ct = crypto.aes_encrypt(key, b"secret data")
    pt = crypto.aes_decrypt(key, ct)
    print(pt)

See also
--------

- :doc:`../reference/types` – NSN object model.
- :doc:`../reference/syntax` – Language syntax reference.
- :doc:`../tutorial/advanced` – Advanced usage examples.
