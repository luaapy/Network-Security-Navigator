/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: exceptions.c
 * Description: Exception object implementation.
 */

#include "nsn.h"

typedef struct {
    NSN_OBJECT_HEAD
    nsn_object *msg;
} nsn_exception_object;

static void exception_dealloc(nsn_object *op) {
    nsn_exception_object *eo = (nsn_exception_object *)op;
    Nsn_XDECREF(eo->msg);
    NsnMem_Free(eo);
}

nsn_type Nsn_ExceptionType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "BaseException",
    .tp_basicsize = sizeof(nsn_exception_object),
    .tp_dealloc = exception_dealloc
};

nsn_object *nsn_exception_new(nsn_type *type, const char *msg) {
    nsn_exception_object *eo = (nsn_exception_object *)NsnMem_Malloc(sizeof(nsn_exception_object));
    if (!eo) return NULL;
    
    eo->ob_refcnt = 1;
    eo->ob_type = type;
    eo->msg = nsn_string_from_cstring(msg);
    
    return (nsn_object *)eo;
}
