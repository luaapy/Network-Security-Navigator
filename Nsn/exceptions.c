/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: exceptions.c
 * Description: Definition of built-in exception types.
 */

#include "nsn.h"

nsn_object *NsnExc_BaseException = NULL;
nsn_object *NsnExc_Exception = NULL;
nsn_object *NsnExc_RuntimeError = NULL;
nsn_object *NsnExc_TypeError = NULL;
nsn_object *NsnExc_ValueError = NULL;
nsn_object *NsnExc_SecurityError = NULL;

static nsn_object *new_exception_type(const char *name, nsn_object *base) {
    // In a real system, this would create a new type object
    // For now, we use a placeholder module-like object or a dedicated type
    return nsn_module_new(name); 
}

void _NsnExc_Init(void) {
    NsnExc_BaseException = new_exception_type("BaseException", NULL);
    NsnExc_Exception = new_exception_type("Exception", NsnExc_BaseException);
    NsnExc_RuntimeError = new_exception_type("RuntimeError", NsnExc_Exception);
    NsnExc_TypeError = new_exception_type("TypeError", NsnExc_Exception);
    NsnExc_ValueError = new_exception_type("ValueError", NsnExc_Exception);
    NsnExc_SecurityError = new_exception_type("SecurityError", NsnExc_Exception);
}

void _NsnExc_Fini(void) {
    Nsn_XDECREF(NsnExc_BaseException);
    Nsn_XDECREF(NsnExc_Exception);
    Nsn_XDECREF(NsnExc_RuntimeError);
    Nsn_XDECREF(NsnExc_TypeError);
    Nsn_XDECREF(NsnExc_ValueError);
    Nsn_XDECREF(NsnExc_SecurityError);
}
