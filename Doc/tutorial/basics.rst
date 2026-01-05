NSN Basics
==========

The Basics of NSN syntax will feel very familiar if you have used Python, C, or JavaScript.

Comments
--------
Comments in NSN start with a hash `#`::

    # This is a comment
    print "Hello World" # Inline comment

Variables
---------
Variables are dynamically typed. You don't need to declare types::

    name = "NSN"
    version = 1.0
    is_active = true

Control Flow
------------

If Statements
~~~~~~~~~~~~~
NSN uses braces `{}` for blocks, similar to C::

    if version >= 1.0 {
        print "Stable release"
    } else {
        print "Alpha/Beta"
    }

Loops
~~~~~
The `while` loop runs as long as a condition is true::

    i = 0
    while i < 5 {
        print i
        i = i + 1
    }

The `for` loop is used to iterate over collections or ranges::

    for port in [80, 443, 22] {
        print "Checking port: " + port
    }

Functions
---------
Define functions using the `func` keyword::

    func scan_host(ip) {
        print "Scanning " + ip
        # perform scan logic
    }

    scan_host("127.0.0.1")

Error Handling
--------------
NSN uses `try`/`catch` blocks for exceptions::

    try {
        result = 10 / 0
    } catch {
        print "An error occurred!"
    }

In the next section, we will look at :doc:`network_ops` to see how NSN handles networking tasks.
