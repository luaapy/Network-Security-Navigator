/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: intobject.c
 * Description: Integer object implementation.
 */

#include "nsn.h"

typedef struct {
    NSN_OBJECT_HEAD
    long lval;
} nsn_int_object;

static void int_dealloc(nsn_object *op) {
    NsnMem_Free(op);
}

nsn_type Nsn_IntType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "int",
    .tp_basicsize = sizeof(nsn_int_object),
    .tp_dealloc = int_dealloc
};

nsn_object *nsn_int_from_long(long value) {
    nsn_int_object *io = (nsn_int_object *)NsnMem_Malloc(sizeof(nsn_int_object));
    if (!io) return NULL;
    io->ob_refcnt = 1;
    io->ob_type = &Nsn_IntType;
    io->lval = value;
    return (nsn_object *)io;
}

long nsn_int_as_long(nsn_object *op) {
    if (op->ob_type != &Nsn_IntType) return -1;
    return ((nsn_int_object *)op)->lval;
}
