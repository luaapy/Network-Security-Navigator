/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: _testinternalcapi.c
 * Description: Testing internal C APIs.
 */

#include "nsn.h"
#include "internal/nsn_internal.h"
#include <stdio.h>
#include <assert.h>

int main(int argc, char **argv) {
    printf("--- NSN Internal C-API Test ---\n");

    Nsn_Initialize(NULL);

    // Test internal memory pool
    void *p = NsnMem_Malloc(1024);
    assert(p != NULL);
    printf("Internal Malloc: Success\n");
    NsnMem_Free(p);

    // Test internal opcode helper
    const char *opname = NsnOpcode_GetName(OP_LOAD_CONST);
    printf("Opcode Lookup: %s\n", opname);
    assert(strcmp(opname, "LOAD_CONST") == 0);

    // Test internal symbol table
    nsn_symtable *st = NsnSymtable_New();
    NsnSymtable_Add(st, "secret_var", 1);
    printf("Symtable Entry: Added\n");
    NsnSymtable_Free(st);

    Nsn_Finalize();
    printf("--- Internal Tests Passed ---\n");
    return 0;
}
