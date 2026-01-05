Advanced NSN Techniques
=======================

This section covers advanced features like custom protocols and asynchronous operations.

Asynchronous Network Tasks
--------------------------
Many network operations in NSN can be run asynchronously to improve performance::

    async func scan_all(targets) {
        for t in targets {
            results = await scan t:80
            print t + " status: " + results.status
        }
    }

    targets = ["10.0.0.1", "10.0.0.2", "10.0.0.3"]
    run scan_all(targets)

Custom Packet Construction
--------------------------
For low-level testing, you can construct and send custom packets::

    import protocol.raw
    
    pkt = raw.Packet()
    pkt.dst = "00:11:22:33:44:55"
    pkt.payload = "Custom Data"
    
    send_raw("eth0", pkt)

Integration with System Tools
-----------------------------
NSN can interface with external tools via C extensions or shell execution::

    output = exec "nmap -sV 192.168.1.1"
    parsed = parse_nmap(output)
    print parsed
