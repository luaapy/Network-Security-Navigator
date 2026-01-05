/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: _bootstrap_nsn.c
 * Description: Minimal bootstrap entry point.
 */

#include "nsn.h"
#include <stdio.h>

int main(int argc, char **argv) {
    /* 
     * This is used for early-stage bootstrapping tests 
     * where we only need the core initialized without full command line 
     * or file handling logic.
     */
    printf("NSN Bootstrapping...\n");

    NsnConfig config;
    Nsn_Config_LoadFile(&config, NULL);

    if (Nsn_Initialize(&config) != 0) {
        return 1;
    }

    printf("Kernel initialized. Thread ID: %ld\n", NsnThread_GetID());
    
    Nsn_Finalize();
    return 0;
}
