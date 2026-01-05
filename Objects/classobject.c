/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: classobject.c
 * Description: Class and instance object implementation.
 */

#include "nsn.h"

typedef struct {
    NSN_OBJECT_HEAD
    nsn_object *cl_name;
    nsn_object *cl_dict;
} nsn_class_object;

static void class_dealloc(nsn_object *op) {
    nsn_class_object *cl = (nsn_class_object *)op;
    Nsn_XDECREF(cl->cl_name);
    Nsn_XDECREF(cl->cl_dict);
    NsnMem_Free(cl);
}

nsn_type Nsn_ClassType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "class",
    .tp_basicsize = sizeof(nsn_class_object),
    .tp_dealloc = class_dealloc
};

nsn_object *nsn_class_new(const char *name) {
    nsn_class_object *cl = (nsn_class_object *)NsnMem_Malloc(sizeof(nsn_class_object));
    if (!cl) return NULL;
    
    cl->ob_refcnt = 1;
    cl->ob_type = &Nsn_ClassType;
    cl->cl_name = nsn_string_from_cstring(name);
    cl->cl_dict = nsn_dict_new();
    
    return (nsn_object *)cl;
}
