Security Auditing
=================

NSN provides high-level constructs for security professionals.

Vulnerability Scanning
----------------------
You can trigger vulnerability checks against specific services::

    target = "192.168.1.10"
    audit target {
        checks: ["http", "ssh", "ssl"],
        intensity: "high"
    }

Cryptography
------------
Built-in support for common hashing and encryption algorithms::

    import security.hash
    
    data = "secret message"
    h = security.hash.sha256(data)
    print "Hash: " + h

Custom Exploit Logic
--------------------
While NSN targets analysis, it can be used to build custom testing scripts::

    # Example: Check for default credentials
    if ssh_login("10.0.0.1", "admin", "admin") {
        print "Warning: Default credentials found on router!"
    }
