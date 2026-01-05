# NSN (Network Security Navigator)
# Copyright (c) NSN Contributors
# Licensed under MIT License
#
# File: libnsn.py
# Description: GDB pretty printers for NSN core objects.

import gdb

class NsnObjectPrinter:
    """Pretty-print an nsn_object."""
    def __init__(self, val):
        self.val = val

    def to_string(self):
        refcnt = self.val['ob_refcnt']
        obj_type = self.val['ob_type']['tp_name'].string()
        
        # Try to extract actual value based on type
        if obj_type == "int":
            ptr = self.val.cast(gdb.lookup_type("nsn_int_object").pointer())
            return f"NSN Int({ptr['lval']}) [refs={refcnt}]"
        elif obj_type == "string":
            ptr = self.val.cast(gdb.lookup_type("nsn_string_object").pointer())
            return f"NSN String(\"{ptr['data'].string()}\") [refs={refcnt}]"
        
        return f"NSN {obj_type} Object @ {self.val.address} [refs={refcnt}]"

def build_pretty_printer():
    pp = gdb.printing.RegexpCollectionPrettyPrinter("nsn")
    pp.add_printer('nsn_object', '^nsn_object$', NsnObjectPrinter)
    return pp

# Register the printers
gdb.printing.register_pretty_printer(gdb.current_objfile(), build_pretty_printer())
print("NSN GDB extensions loaded.")
