/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: frozenmain.c
 */

#include "nsn.h"

/*
 * Main entry point for a frozen NSN interpreter.
 * This can be used to create standalone binaries that include the stdlib.
 */

int nsn_frozen_main(int argc, char **argv) {
    /* 1. Initialize with frozen modules */
    // nsn_init_frozen();
    
    /* 2. Run the __main__ entry point from frozen library */
    // return nsn_run_module("__main__");
    
    printf("NSN Frozen Main Stub\n");
    return 0;
}

