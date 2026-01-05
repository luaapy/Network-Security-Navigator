/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: test_memory.c
 * Description: Unit tests for the custom memory allocator and reference counting.
 */

#include "nsn.h"
#include <assert.h>
#include <stdio.h>

void test_allocation() {
    void *p = NsnMem_Malloc(1024);
    assert(p != NULL);
    p = NsnMem_Realloc(p, 2048);
    assert(p != NULL);
    NsnMem_Free(p);
    printf("test_allocation: PASSED\n");
}

void test_ref_counts() {
    nsn_object *obj = nsn_int_from_long(42);
    assert(obj->ob_refcnt == 1);
    
    Nsn_INCREF(obj);
    assert(obj->ob_refcnt == 2);
    
    Nsn_DECREF(obj);
    assert(obj->ob_refcnt == 1);
    
    Nsn_DECREF(obj); // Should trigger deallocation
    printf("test_ref_counts: PASSED\n");
}

int main() {
    printf("Running Memory System Tests...\n");
    Nsn_Initialize(NULL);
    
    test_allocation();
    test_ref_counts();
    
    Nsn_Finalize();
    printf("All memory tests PASSED.\n");
    return 0;
}
