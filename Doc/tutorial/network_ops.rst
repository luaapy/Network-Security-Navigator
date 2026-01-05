Network Operations
==================

NSN is built for networking. This section covers basic network tasks.

Host Connectivity
-----------------
The most basic operation is checking if a host is reachable using `ping`::

    target = "8.8.8.8"
    if ping(target) {
        print target + " is alive"
    }

DNS Resolution
--------------
You can resolve hostnames directly using the `resolve` keyword::

    ip = resolve "google.com"
    print "Google is at " + ip

Port Scanning
-------------
Scanning ports is integrated into the language syntax::

    # Scan a single port
    if port 80 open on "127.0.0.1" {
        print "Web server is running"
    }

    # Scan a range
    results = scan "192.168.1.1":1-100
    for r in results.open {
        print "Found open port: " + r
    }
