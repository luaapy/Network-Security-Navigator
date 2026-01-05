/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: typeobject.c
 * Description: The core 'type' object for the NSN type system.
 */

#include "nsn.h"

static void type_dealloc(nsn_object *op) {
    /* Most basic types are static and never deallocated */
}

nsn_type Nsn_TypeType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "type",
    .tp_basicsize = sizeof(nsn_type),
    .tp_dealloc = type_dealloc
};
