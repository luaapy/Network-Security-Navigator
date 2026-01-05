# NSN (Network Security Navigator)
# Copyright (c) NSN Contributors
# Licensed under MIT License
#
# File: nsn.py
# Description: LLDB data formatters for NSN core objects.

import lldb

def nsn_object_SummaryProvider(valobj, dict):
    refcnt = valobj.GetChildMemberWithName('ob_refcnt').GetValueAsSigned()
    type_ptr = valobj.GetChildMemberWithName('ob_type')
    type_name = type_ptr.GetChildMemberWithName('tp_name').GetSummary()
    
    return f"NSN {type_name} (refs={refcnt})"

def __lldb_init_module(debugger, dict):
    debugger.HandleCommand('type summary add nsn_object --python-function nsn.nsn_object_SummaryProvider')
    print("NSN LLDB extensions loaded.")
