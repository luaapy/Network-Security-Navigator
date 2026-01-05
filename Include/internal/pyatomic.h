/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * Atomic operations
 */

#ifndef NSN_INTERNAL_ATOMIC_H
#define NSN_INTERNAL_ATOMIC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdatomic.h>
#include <stddef.h>

/* Simple wrapper types for atomic integers */
typedef _Atomic int nsn_atomic_int;
typedef _Atomic long nsn_atomic_long;
typedef _Atomic void* nsn_atomic_ptr;

/* Atomic load/store operations */
static inline int nsn_atomic_load_int(const nsn_atomic_int *obj) {
    return atomic_load_explicit(obj, memory_order_relaxed);
}
static inline void nsn_atomic_store_int(nsn_atomic_int *obj, int val) {
    atomic_store_explicit(obj, val, memory_order_relaxed);
}

static inline long nsn_atomic_load_long(const nsn_atomic_long *obj) {
    return atomic_load_explicit(obj, memory_order_relaxed);
}
static inline void nsn_atomic_store_long(nsn_atomic_long *obj, long val) {
    atomic_store_explicit(obj, val, memory_order_relaxed);
}

static inline void *nsn_atomic_load_ptr(const nsn_atomic_ptr *obj) {
    return atomic_load_explicit(obj, memory_order_relaxed);
}
static inline void nsn_atomic_store_ptr(nsn_atomic_ptr *obj, void *val) {
    atomic_store_explicit(obj, val, memory_order_relaxed);
}

/* Atomic increment/decrement */
static inline int nsn_atomic_fetch_add_int(nsn_atomic_int *obj, int delta) {
    return atomic_fetch_add_explicit(obj, delta, memory_order_relaxed);
}
static inline int nsn_atomic_fetch_sub_int(nsn_atomic_int *obj, int delta) {
    return atomic_fetch_sub_explicit(obj, delta, memory_order_relaxed);
}

static inline long nsn_atomic_fetch_add_long(nsn_atomic_long *obj, long delta) {
    return atomic_fetch_add_explicit(obj, delta, memory_order_relaxed);
}
static inline long nsn_atomic_fetch_sub_long(nsn_atomic_long *obj, long delta) {
    return atomic_fetch_sub_explicit(obj, delta, memory_order_relaxed);
}

#ifdef __cplusplus
}
#endif

#endif // NSN_INTERNAL_ATOMIC_H
