/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: nsn_bytecode.c
 * Description: Bytecode object implementation.
 */

#include "nsn.h"
#include <stdlib.h>
#include <string.h>

/* Code Object Structure */
typedef struct {
    NSN_OBJECT_HEAD
    unsigned char *code;   /* Serialized bytecode */
    size_t length;         /* Length of bytecode */
    nsn_object *consts;    /* Constant pool (NSN List) */
    nsn_object *names;     /* Variable names (NSN List) */
    nsn_object *filename;  /* Script source path */
    int arg_count;         /* Number of function arguments */
} nsn_code_object;

static void code_dealloc(nsn_object *op) {
    nsn_code_object *co = (nsn_code_object *)op;
    if (co->code) free(co->code);
    Nsn_XDECREF(co->consts);
    Nsn_XDECREF(co->names);
    Nsn_XDECREF(co->filename);
    NsnMem_Free(co);
}

nsn_type Nsn_CodeType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "code",
    .tp_basicsize = sizeof(nsn_code_object),
    .tp_dealloc = code_dealloc
};

nsn_object *NsnCode_New(unsigned char *code, size_t len, nsn_object *consts, nsn_object *names) {
    nsn_code_object *co = (nsn_code_object *)NsnMem_Malloc(sizeof(nsn_code_object));
    if (!co) return NULL;

    co->ob_refcnt = 1;
    co->ob_type = &Nsn_CodeType;
    
    co->code = (unsigned char *)malloc(len);
    if (co->code) memcpy(co->code, code, len);
    co->length = len;

    co->consts = consts;
    Nsn_XINCREF(consts);
    
    co->names = names;
    Nsn_XINCREF(names);
    
    co->filename = NULL;
    co->arg_count = 0;

    return (nsn_object *)co;
}
