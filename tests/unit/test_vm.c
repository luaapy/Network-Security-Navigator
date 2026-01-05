/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: test_vm.c
 * Description: Unit tests for the bytecode evaluator (VM).
 */

#include "nsn.h"
#include <assert.h>
#include <stdio.h>

void test_simple_eval() {
    /* 
     * Manually construct a simple bytecode for: return 10 + 20
     */
    nsn_object *consts = nsn_list_new();
    nsn_list_append(consts, nsn_int_from_long(10));
    nsn_list_append(consts, nsn_int_from_long(20));
    
    unsigned char bc[] = {
        OP_LOAD_CONST, 0, // 10
        OP_LOAD_CONST, 1, // 20
        OP_BINARY_ADD,
        OP_RETURN_VALUE
    };
    
    nsn_object *code = NsnCode_New(bc, sizeof(bc), consts, nsn_list_new());
    nsn_object *result = NsnVM_EvalCode(code, nsn_dict_new(), nsn_dict_new());
    
    assert(result != NULL);
    assert(nsn_int_as_long(result) == 30);
    
    Nsn_DECREF(result);
    Nsn_DECREF(code);
    Nsn_DECREF(consts);
}

int main() {
    printf("Running VM Tests...\n");
    Nsn_Initialize(NULL);
    
    test_simple_eval();
    
    Nsn_Finalize();
    printf("All VM tests PASSED.\n");
    return 0;
}
