/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: pycore_atomic.h
 */

#ifndef NSN_PYCORE_ATOMIC_H
#define NSN_PYCORE_ATOMIC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pyatomic.h"

/* High‑level atomic helpers used by the interpreter core */

/* Increment a reference count atomically */
static inline void nsn_atomic_inc_ref(nsn_atomic_int *refcnt) {
    nsn_atomic_fetch_add_int(refcnt, 1);
}

/* Decrement a reference count atomically and return the new value */
static inline int nsn_atomic_dec_ref(nsn_atomic_int *refcnt) {
    return nsn_atomic_fetch_sub_int(refcnt, 1) - 1;
}

#ifdef __cplusplus
}
#endif

#endif // NSN_PYCORE_ATOMIC_H
