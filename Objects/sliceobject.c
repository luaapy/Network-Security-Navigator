/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: sliceobject.c
 * Description: Implementation of slice objects for sequence indexing.
 */

#include "nsn.h"

typedef struct {
    NSN_OBJECT_HEAD
    nsn_object *start;
    nsn_object *stop;
    nsn_object *step;
} nsn_slice_object;

static void slice_dealloc(nsn_object *op) {
    nsn_slice_object *sl = (nsn_slice_object *)op;
    Nsn_XDECREF(sl->start);
    Nsn_XDECREF(sl->stop);
    Nsn_XDECREF(sl->step);
    NsnMem_Free(sl);
}

nsn_type Nsn_SliceType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "slice",
    .tp_basicsize = sizeof(nsn_slice_object),
    .tp_dealloc = slice_dealloc
};

nsn_object *nsn_slice_new(nsn_object *start, nsn_object *stop, nsn_object *step) {
    nsn_slice_object *sl = (nsn_slice_object *)NsnMem_Malloc(sizeof(nsn_slice_object));
    if (!sl) return NULL;
    
    sl->ob_refcnt = 1;
    sl->ob_type = &Nsn_SliceType;
    Nsn_XINCREF(start);
    sl->start = start;
    Nsn_XINCREF(stop);
    sl->stop = stop;
    Nsn_XINCREF(step);
    sl->step = step;
    
    return (nsn_object *)sl;
}
