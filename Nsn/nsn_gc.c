/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: nsn_gc.c
 * Description: Garbage collection and reference management.
 */

#include "nsn.h"

/* 
 * Standard reference counting is the primary mechanism.
 * This file handles cyclic garbage collection if implemented.
 */

void NsnGC_Track(nsn_object *obj) {
    /* Add to the generation 0 tracking list */
}

void NsnGC_Untrack(nsn_object *obj) {
    /* Remove from tracking list */
}

void NsnGC_Collect(void) {
    /* 
     * 1. Mark and sweep for cycles
     * 2. Finalize unreachable objects
     */
}

/* Internal Incref/Decref implementations if not inlined */

void Nsn_IncRef(nsn_object *obj) {
    if (obj) obj->ob_refcnt++;
}

void Nsn_DecRef(nsn_object *obj) {
    if (!obj) return;
    if (--obj->ob_refcnt == 0) {
        if (obj->ob_type && obj->ob_type->tp_dealloc) {
            obj->ob_type->tp_dealloc(obj);
        } else {
            Nsn_Free(obj);
        }
    }
}
