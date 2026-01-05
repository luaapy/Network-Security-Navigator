Networking API Reference
========================

The :mod:`protocol` package provides high-level interfaces for network communication.

TCP Module
----------

.. module:: protocol.tcp

.. class:: Connection(host, port, timeout=5.0)

   Represents a TCP connection to a remote host.

   .. method:: connect()
      Establish the connection.

   .. method:: send(data)
      Send bytes or string data through the socket.

   .. method:: recv(bufsize=4096)
      Receive up to *bufsize* bytes.

UDP Module
----------

.. module:: protocol.udp

.. class:: Client(host, port)

   Represents a UDP client.

   .. method:: send(data)
      Send data to the target host:port.

ICMP Module
-----------

.. module:: protocol.icmp

.. function:: ping(host, count=4, timeout=1.0)

   Send ICMP echo requests to the target host.

DNS Module
----------

.. module:: protocol.dns

.. function:: resolve(hostname)

   Resolve a hostname to an IP address.
