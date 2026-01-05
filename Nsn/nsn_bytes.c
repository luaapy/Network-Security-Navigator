/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: nsn_bytes.c
 * Description: Implementation of the 'bytes' object.
 */

#include "nsn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    NSN_OBJECT_HEAD
    unsigned char *data;
    size_t length;
} nsn_bytes_object;

static void bytes_dealloc(nsn_object *op) {
    nsn_bytes_object *bo = (nsn_bytes_object *)op;
    if (bo->data) free(bo->data);
    NsnMem_Free(bo);
}

nsn_type Nsn_BytesType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "bytes",
    .tp_basicsize = sizeof(nsn_bytes_object),
    .tp_dealloc = bytes_dealloc
};

nsn_object *nsn_bytes_from_data(const unsigned char *data, size_t len) {
    nsn_bytes_object *bo = (nsn_bytes_object *)NsnMem_Malloc(sizeof(nsn_bytes_object));
    if (!bo) return NULL;
    bo->ob_refcnt = 1;
    bo->ob_type = &Nsn_BytesType;
    bo->data = (unsigned char *)malloc(len);
    if (bo->data) memcpy(bo->data, data, len);
    bo->length = len;
    return (nsn_object *)bo;
}

size_t nsn_bytes_get_length(nsn_object *op) {
    if (op->ob_type != &Nsn_BytesType) return 0;
    return ((nsn_bytes_object *)op)->length;
}

const unsigned char *nsn_bytes_get_data(nsn_object *op) {
    if (op->ob_type != &Nsn_BytesType) return NULL;
    return ((nsn_bytes_object *)op)->data;
}
