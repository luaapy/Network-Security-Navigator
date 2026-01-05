/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: nsn_unicode.c
 * Description: Implementation of the 'string' (UTF-8 unicode) object.
 */

#include "nsn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    NSN_OBJECT_HEAD
    char *data;
    size_t length;
    long hash;
} nsn_string_object;

static void string_dealloc(nsn_object *op) {
    nsn_string_object *so = (nsn_string_object *)op;
    if (so->data) Nsn_Free(so->data);
    NsnMem_Free(so);
}

static long string_hash(nsn_object *op) {
    nsn_string_object *so = (nsn_string_object *)op;
    if (so->hash != -1) return so->hash;
    
    so->hash = (long)Nsn_HashString(so->data);
    return so->hash;
}

nsn_type Nsn_StringType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "string",
    .tp_basicsize = sizeof(nsn_string_object),
    .tp_dealloc = string_dealloc,
    .tp_hash = string_hash
};

nsn_object *nsn_string_from_cstring(const char *str) {
    if (!str) return Nsn_None;
    
    nsn_string_object *so = (nsn_string_object *)NsnMem_Malloc(sizeof(nsn_string_object));
    if (!so) return NULL;
    
    so->ob_refcnt = 1;
    so->ob_type = &Nsn_StringType;
    so->length = strlen(str);
    so->data = Nsn_StrDup(str);
    so->hash = -1;
    
    return (nsn_object *)so;
}

const char *nsn_string_as_cstring(nsn_object *op) {
    if (op->ob_type != &Nsn_StringType) return NULL;
    return ((nsn_string_object *)op)->data;
}