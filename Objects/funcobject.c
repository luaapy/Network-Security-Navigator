/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: funcobject.c
 * Description: Function object implementation.
 */

#include "nsn.h"

typedef struct {
    NSN_OBJECT_HEAD
    nsn_object *fn_code;
    nsn_object *fn_globals;
    nsn_object *fn_name;
} nsn_func_object;

static void func_dealloc(nsn_object *op) {
    nsn_func_object *fn = (nsn_func_object *)op;
    Nsn_XDECREF(fn->fn_code);
    Nsn_XDECREF(fn->fn_globals);
    Nsn_XDECREF(fn->fn_name);
    NsnMem_Free(fn);
}

nsn_type Nsn_FuncType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "function",
    .tp_basicsize = sizeof(nsn_func_object),
    .tp_dealloc = func_dealloc
};

nsn_object *nsn_func_new(nsn_object *code, nsn_object *globals, const char *name) {
    nsn_func_object *fn = (nsn_func_object *)NsnMem_Malloc(sizeof(nsn_func_object));
    if (!fn) return NULL;
    
    fn->ob_refcnt = 1;
    fn->ob_type = &Nsn_FuncType;
    Nsn_INCREF(code);
    fn->fn_code = code;
    Nsn_INCREF(globals);
    fn->fn_globals = globals;
    fn->fn_name = nsn_string_from_cstring(name);
    
    return (nsn_object *)fn;
}
