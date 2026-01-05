/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: nsn_hash.c
 * Description: Internal object hashing logic.
 */

#include "nsn.h"

long nsn_object_hash(nsn_object *v) {
    if (v->ob_type->tp_hash) {
        return v->ob_type->tp_hash(v);
    }
    
    // Default pointer-based hash for non-hashable types
    return (long)((uintptr_t)v >> 4);
}
