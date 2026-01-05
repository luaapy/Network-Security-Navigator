/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: token.c
 * Description: Token object implementation.
 */

#include "nsn.h"

typedef struct {
    NSN_OBJECT_HEAD
    int kind;
    nsn_object *value;
    int line;
    int col;
} nsn_token_object;

static void token_dealloc(nsn_object *op) {
    nsn_token_object *to = (nsn_token_object *)op;
    Nsn_XDECREF(to->value);
    NsnMem_Free(to);
}

nsn_type Nsn_TokenType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "token",
    .tp_basicsize = sizeof(nsn_token_object),
    .tp_dealloc = token_dealloc
};

nsn_object *NsnToken_New(int kind, nsn_object *value, int line, int col) {
    nsn_token_object *to = (nsn_token_object *)NsnMem_Malloc(sizeof(nsn_token_object));
    to->ob_refcnt = 1;
    to->ob_type = &Nsn_TokenType;
    to->kind = kind;
    to->value = value;
    Nsn_XINCREF(value);
    to->line = line;
    to->col = col;
    return (nsn_object *)to;
}
