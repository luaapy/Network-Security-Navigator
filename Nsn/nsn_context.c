/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: nsn_context.c
 * Description: Implementation of context management objects.
 */

#include "nsn.h"

typedef struct {
    NSN_OBJECT_HEAD
    nsn_object *enter;
    nsn_object *exit;
} nsn_context_object;

static void context_dealloc(nsn_object *op) {
    nsn_context_object *co = (nsn_context_object *)op;
    Nsn_XDECREF(co->enter);
    Nsn_XDECREF(co->exit);
    NsnMem_Free(co);
}

nsn_type Nsn_ContextType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "context",
    .tp_basicsize = sizeof(nsn_context_object),
    .tp_dealloc = context_dealloc
};

nsn_object *nsn_context_new(nsn_object *enter, nsn_object *exit) {
    nsn_context_object *co = (nsn_context_object *)NsnMem_Malloc(sizeof(nsn_context_object));
    if (!co) return NULL;
    co->ob_refcnt = 1;
    co->ob_type = &Nsn_ContextType;
    Nsn_XINCREF(enter);
    co->enter = enter;
    Nsn_XINCREF(exit);
    co->exit = exit;
    return (nsn_object *)co;
}
