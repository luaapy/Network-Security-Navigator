NSN Language Syntax
===================

Lexical Structure
-----------------

Keywords
~~~~~~~~
The following identifiers are reserved keywords in NSN:

* `async`, `await`, `break`, `class`, `continue`, `def`, `else`, `false`, `for`, `func`, `if`, `import`, `in`, `is`, `null`, `return`, `true`, `while`.

Literals
~~~~~~~~

**Strings**: Enclosed in double quotes.
::
    "Hello NSN"

**Numbers**: Integers and floating-point numbers.
::
    42
    3.14

**IP Addresses**: Native support for IPv4 and IPv6.
::
    192.168.1.1
    2001:db8::1

**Networks**: CIDR notation support.
::
    10.0.0.0/24

Control Flow
------------

If Statements
~~~~~~~~~~~~~
::
    if condition {
        # code
    } else {
        # code
    }

For Loops
~~~~~~~~~
::
    for item in collection {
        # code
    }

Function Definitions
~~~~~~~~~~~~~~~~~~~~
::
    func greet(name) {
        return "Hello " + name
    }
