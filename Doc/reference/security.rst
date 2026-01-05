Security Reference
==================

NSN includes specialized primitives for security auditing and vulnerability research.

Port Scanning
-------------
Keyword: `scan`

The `scan` primitive is a highly parallelized native operation.

.. code-block:: python

    # Basic scan
    results = scan "10.0.0.1":1-1024

    # Advanced configuration
    results = scan "10.0.0.1":80, 443 {
        timeout: 500ms,
        retries: 2,
        stealth: true
    }

Vulnerability Auditing
----------------------
The `audit` module provides service fingerprinting and CVE mapping.

.. code-block:: python

    import security.audit
    
    findings = security.audit.host("192.168.1.100")
    for issue in findings {
        print "Found " + issue.severity + ": " + issue.description
    }

Cryptography
------------
Native bindings to OpenSSL/LibreSSL for high-performance crypto.

Modules:
- `security.hash`: Fast MD5, SHA1, SHA256, SHA512.
- `security.crypto`: AES, RSA, ECC encryption and decryption.
