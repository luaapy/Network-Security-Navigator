/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: nsn_weakref.c
 * Description: Weak reference implementation.
 */

#include "nsn.h"

typedef struct {
    NSN_OBJECT_HEAD
    nsn_object *referenced;
    nsn_object *callback;
} nsn_weakref_object;

static void weakref_dealloc(nsn_object *op) {
    nsn_weakref_object *wr = (nsn_weakref_object *)op;
    // Notify referenced object that this weakref is going away?
    NsnMem_Free(wr);
}

nsn_type Nsn_WeakrefType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "weakref",
    .tp_basicsize = sizeof(nsn_weakref_object),
    .tp_dealloc = weakref_dealloc
};

nsn_object *NsnWeakref_New(nsn_object *obj, nsn_object *callback) {
    nsn_weakref_object *wr = (nsn_weakref_object *)NsnMem_Malloc(sizeof(nsn_weakref_object));
    wr->ob_refcnt = 1;
    wr->ob_type = &Nsn_WeakrefType;
    wr->referenced = obj;
    wr->callback = callback;
    Nsn_XINCREF(callback);
    return (nsn_object *)wr;
}
