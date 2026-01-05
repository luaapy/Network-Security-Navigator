Networking Reference
====================

The networking capabilities are core to NSN, providing native types and optimized operations.

IP Address Handling
-------------------
IP addresses are created using literals or the `ip()` constructor.

.. code-block:: python

    a = 192.168.1.1
    b = ip("10.0.0.1")

Methods:
- `addr.version()`: Returns 4 or 6.
- `addr.is_private()`: Returns true if the address is in a private range.
- `addr.is_multicast()`: Returns true if it's a multicast address.

Network/CIDR Handling
---------------------
Networks are defined using the `/` slash notation.

.. code-block:: python

    net = 192.168.1.0/24

Methods:
- `net.contains(ip)`: Check if an IP is within the subnet.
- `net.hosts()`: Return an iterator over usable hosts in the network.
- `net.broadcast()`: Return the broadcast address.

Socket Operations
-----------------
NSN provides high-level wrappers around BSD sockets.

.. code-block:: python

    import protocol.tcp
    s = tcp.connect("google.com", 80)
    s.send("GET / HTTP/1.1\r\n\r\n")
    data = s.recv(1024)
