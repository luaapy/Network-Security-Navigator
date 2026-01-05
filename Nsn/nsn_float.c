/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: nsn_float.c
 * Description: Implementation of the 'float' object.
 */

#include "nsn.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    NSN_OBJECT_HEAD
    double dval;
} nsn_float_object;

static void float_dealloc(nsn_object *op) {
    NsnMem_Free(op);
}

nsn_type Nsn_FloatType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "float",
    .tp_basicsize = sizeof(nsn_float_object),
    .tp_dealloc = float_dealloc
};

nsn_object *nsn_float_from_double(double value) {
    nsn_float_object *fo = (nsn_float_object *)NsnMem_Malloc(sizeof(nsn_float_object));
    if (!fo) return NULL;
    fo->ob_refcnt = 1;
    fo->ob_type = &Nsn_FloatType;
    fo->dval = value;
    return (nsn_object *)fo;
}

double nsn_float_as_double(nsn_object *op) {
    if (op->ob_type != &Nsn_FloatType) return 0.0;
    return ((nsn_float_object *)op)->dval;
}
