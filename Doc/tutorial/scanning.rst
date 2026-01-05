Advanced Port Scanning
======================

Port scanning is at the heart of NSN. This tutorial covers advanced scanning techniques.

Named Port Lists
----------------
You can define lists of ports for repeated use::

    web_ports = [80, 443, 8080, 8443]
    scan "10.0.0.1":web_ports

Protocol Specific Scans
-----------------------
NSN supports both TCP and UDP scanning. By default, `scan` uses TCP::

    # UDP Scan
    scan udp "192.168.1.1":53, 67, 68

Timing and Performance
----------------------
You can adjust the intensity of scans to avoid detection or speed up results::

    scan "10.0.0.5":1-65535 {
        threads: 50,
        timeout: 200ms,
        delay: 10ms
    }

Service Detection
-----------------
Combine scanning with service detection to identify what's running::

    results = scan "192.168.1.1":22, 80
    for r in results.open {
        service = detect_service(r)
        print "Port " + r + " is " + service
    }
