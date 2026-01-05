/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: main.c
 * Description: High-level entry point wrapper for the NSN interpreter.
 */

#include "nsn.h"
#include <stdio.h>
#include <stdlib.h>

int Nsn_Main(int argc, char **argv) {
    NsnConfig config;
    Nsn_Config_LoadFile(&config, NULL);

    // Command line processing logic could be moved here from Programs/nsn.c
    // to allow better embedding.
    
    if (Nsn_Initialize() != 0) {
        fprintf(stderr, "Fatal error: NSN initialization failed\n");
        return 1;
    }

    int status = 0;
    if (argc > 1) {
        nsn_object *res = Nsn_RunFile(argv[1]);
        if (!res) {
            if (Nsn_Err_Occurred()) {
                fprintf(stderr, "Error: %s\n", Nsn_Err_GetMessage());
                Nsn_Err_Clear();
            }
            status = 1;
        } else {
            Nsn_DECREF(res);
        }
    } else {
        printf("NSN %s (%s, %s)\n", NSN_VERSION_STRING, Nsn_GetPlatform(), Nsn_GetCompiler());
        printf("Use 'nsn script.nsn' to run a file.\n");
    }

    Nsn_Finalize();
    return status;
}
