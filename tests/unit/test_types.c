/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: test_types.c
 * Description: Unit tests for the NSN object system and built-in types.
 */

#include "nsn.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_int_type() {
    nsn_object *v = nsn_int_from_long(12345);
    assert(v->ob_type == &Nsn_IntType);
    assert(nsn_int_as_long(v) == 12345);
    Nsn_DECREF(v);
}

void test_string_type() {
    nsn_object *s = nsn_string_from_cstring("NSN Test");
    assert(s->ob_type == &Nsn_StringType);
    assert(strcmp(nsn_string_as_cstring(s), "NSN Test") == 0);
    Nsn_DECREF(s);
}

void test_dict_type() {
    nsn_object *d = nsn_dict_new();
    nsn_object *k = nsn_string_from_cstring("key");
    nsn_object *v = nsn_int_from_long(100);
    
    nsn_dict_set_item(d, k, v);
    nsn_object *res = nsn_dict_get_item(d, k);
    assert(res == v);
    
    Nsn_DECREF(k);
    Nsn_DECREF(v);
    Nsn_DECREF(d);
}

int main() {
    printf("Running Type System Tests...\n");
    Nsn_Initialize(NULL);
    
    test_int_type();
    test_string_type();
    test_dict_type();
    
    Nsn_Finalize();
    printf("All type tests PASSED.\n");
    return 0;
}
