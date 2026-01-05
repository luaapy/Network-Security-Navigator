/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: nsn_generators.c
 * Description: Implementation of generator objects.
 */

#include "nsn.h"

typedef struct {
    NSN_OBJECT_HEAD
    nsn_frame *frame;
    int running;
} nsn_gen_object;

static void gen_dealloc(nsn_object *op) {
    nsn_gen_object *go = (nsn_gen_object *)op;
    // NsnFrame_Delete(go->frame);
    NsnMem_Free(go);
}

nsn_type Nsn_GenType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "generator",
    .tp_basicsize = sizeof(nsn_gen_object),
    .tp_dealloc = gen_dealloc
};

nsn_object *nsn_generator_new(nsn_frame *frame) {
    nsn_gen_object *go = (nsn_gen_object *)NsnMem_Malloc(sizeof(nsn_gen_object));
    if (!go) return NULL;
    go->ob_refcnt = 1;
    go->ob_type = &Nsn_GenType;
    go->frame = frame;
    go->running = 0;
    return (nsn_object *)go;
}
