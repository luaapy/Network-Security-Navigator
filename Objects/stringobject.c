/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: stringobject.c
 * Description: UTF-8 string object implementation.
 */

#include "nsn.h"
#include <string.h>

typedef struct {
    NSN_OBJECT_HEAD
    char *data;
    size_t length;
    long hash;
} nsn_string_object;

static void string_dealloc(nsn_object *op) {
    nsn_string_object *so = (nsn_string_object *)op;
    if (so->data) free(so->data);
    NsnMem_Free(so);
}

nsn_type Nsn_StringType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "string",
    .tp_basicsize = sizeof(nsn_string_object),
    .tp_dealloc = string_dealloc
};

nsn_object *nsn_string_from_cstring(const char *str) {
    nsn_string_object *so = (nsn_string_object *)NsnMem_Malloc(sizeof(nsn_string_object));
    if (!so) return NULL;
    
    so->ob_refcnt = 1;
    so->ob_type = &Nsn_StringType;
    so->length = strlen(str);
    so->data = strdup(str);
    so->hash = -1;
    
    return (nsn_object *)so;
}

const char *nsn_string_as_cstring(nsn_object *op) {
    if (op->ob_type != &Nsn_StringType) return NULL;
    return ((nsn_string_object *)op)->data;
}
