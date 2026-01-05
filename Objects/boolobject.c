/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: boolobject.c
 * Description: Implementation of Boolean (True/False) objects.
 */

#include "nsn.h"

typedef struct {
    NSN_OBJECT_HEAD
    int bval;
} nsn_bool_object;

static void bool_dealloc(nsn_object *op) {
    /* Boolean objects are singleton and should not be deallocated */
}

nsn_type Nsn_BoolType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "bool",
    .tp_basicsize = sizeof(nsn_bool_object),
    .tp_dealloc = bool_dealloc
};

static nsn_bool_object _nsn_true_val = { { 1, &Nsn_BoolType }, 1 };
static nsn_bool_object _nsn_false_val = { { 1, &Nsn_BoolType }, 0 };

nsn_object *Nsn_True = (nsn_object *)&_nsn_true_val;
nsn_object *Nsn_False = (nsn_object *)&_nsn_false_val;

nsn_object *nsn_bool_from_int(int b) {
    return b ? Nsn_True : Nsn_False;
}
