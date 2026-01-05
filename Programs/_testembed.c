/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: _testembed.c
 * Description: Testing embedding NSN in a C application.
 */

#include "nsn.h"
#include <stdio.h>

int main(int argc, char **argv) {
    printf("--- NSN Embedding Test ---\n");

    NsnConfig config;
    Nsn_Config_LoadFile(&config, NULL);
    
    if (Nsn_Initialize(&config) != 0) {
        fprintf(stderr, "Initialization failed\n");
        return 1;
    }

    const char *script = 
        "func hello(name) {\n"
        "    print('Hello from embedded NSN, ' + name);\n"
        "}\n"
        "hello('Developer');\n";

    printf("Executing script from memory...\n");
    Nsn_EvalString(script);

    Nsn_Finalize();
    printf("--- Test Complete ---\n");
    return 0;
}
