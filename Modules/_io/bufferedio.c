/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: bufferedio.c
 * Description: Buffered I/O implementation.
 */

#include "nsn.h"

/*
 * BufferedIO provides a buffer for raw I/O streams.
 */

typedef struct {
    NSN_OBJECT_HEAD
    nsn_object *raw;
    char *buffer;
    size_t size;
    size_t pos;
} nsn_buffered_object;

static void buffered_dealloc(nsn_object *op) {
    nsn_buffered_object *bo = (nsn_buffered_object *)op;
    Nsn_XDECREF(bo->raw);
    free(bo->buffer);
    NsnMem_Free(bo);
}

nsn_type Nsn_BufferedIOType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "_io.BufferedIO",
    .tp_basicsize = sizeof(nsn_buffered_object),
    .tp_dealloc = buffered_dealloc
};

void _nsn_init_bufferedio(void) {
    /* Buffered IO types registration */
}
