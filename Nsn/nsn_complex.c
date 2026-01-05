/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: nsn_complex.c
 * Description: Implementation of the 'complex' number object.
 */

#include "nsn.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    NSN_OBJECT_HEAD
    double real;
    double imag;
} nsn_complex_object;

static void complex_dealloc(nsn_object *op) {
    NsnMem_Free(op);
}

nsn_type Nsn_ComplexType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "complex",
    .tp_basicsize = sizeof(nsn_complex_object),
    .tp_dealloc = complex_dealloc
};

nsn_object *nsn_complex_from_doubles(double real, double imag) {
    nsn_complex_object *co = (nsn_complex_object *)NsnMem_Malloc(sizeof(nsn_complex_object));
    if (!co) return NULL;
    co->ob_refcnt = 1;
    co->ob_type = &Nsn_ComplexType;
    co->real = real;
    co->imag = imag;
    return (nsn_object *)co;
}
