/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: iobase.c
 * Description: Base classes for the IO hierarchy.
 */

#include "nsn.h"

/* 
 * IOBase is the abstract base class for all I/O classes.
 * It provides default implementations for methods like seekable(), 
 * readable(), writable(), and closed.
 */

typedef struct {
    NSN_OBJECT_HEAD
} nsn_iobase_object;

static void iobase_dealloc(nsn_object *op) {
    NsnMem_Free(op);
}

nsn_type Nsn_IOBaseType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "_io._IOBase",
    .tp_basicsize = sizeof(nsn_iobase_object),
    .tp_dealloc = iobase_dealloc
};

void _nsn_init_iobase(void) {
    /* Base IO types registration */
}
