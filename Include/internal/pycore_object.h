/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: pycore_object.h
 */

#ifndef NSN_PYCORE_OBJECT_H
#define NSN_PYCORE_OBJECT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "object.h"
#include "pycore_atomic.h"

/* Object allocation and deallocation helpers */

static inline nsn_object *nsn_object_new(nsn_type *type, size_t size) {
    nsn_object *obj = (nsn_object *)NsnMem_Malloc(size);
    if (!obj) {
        // Set memory error
        NsnErr_SetString(NsnExc_MemoryError, "Unable to allocate object");
        return NULL;
    }
    obj->ob_refcnt = 1;
    obj->ob_type = type;
    return obj;
}

static inline void nsn_object_dealloc(nsn_object *obj) {
    if (obj && obj->ob_type && obj->ob_type->tp_dealloc) {
        obj->ob_type->tp_dealloc(obj);
    }
    NsnMem_Free(obj);
}

/* Reference count manipulation using atomic helpers */
static inline void nsn_object_inc_ref(nsn_object *obj) {
    nsn_atomic_inc_ref((nsn_atomic_int *)&obj->ob_refcnt);
}

static inline void nsn_object_dec_ref(nsn_object *obj) {
    if (nsn_atomic_dec_ref((nsn_atomic_int *)&obj->ob_refcnt) == 0) {
        nsn_object_dealloc(obj);
    }
}

#ifdef __cplusplus
}
#endif

#endif // NSN_PYCORE_OBJECT_H
