/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * Core runtime implementation
 */

#include "nsn.h"
#include <stdio.h>

int Nsn_Initialize(void) {
    if (NsnNetwork_Init() != 0) {
        fprintf(stderr, "Fatal: Network initialization failed\n");
        return 1;
    }

    // 1. Initialize memory allocator (integrated in initialization)
    // 2. Initialize object system (exceptions, types)
    _NsnExc_Init();

    // 3. Initialize interpreter state
    NsnInterpreterState_New();
    
    // 4. Load built-in modules
    Nsn_InitBuiltinModules();
    
    return 0; 
}

void Nsn_Finalize(void) {
    _NsnExc_Fini();
    NsnNetwork_Cleanup();
    
    nsn_interpreter_state *interp = NsnInterpreterState_Main();
    if (interp) {
        NsnInterpreterState_Delete(interp);
    }
}

const char *Nsn_GetVersion(void) {
    return NSN_VERSION_STRING;
}

nsn_object *Nsn_RunFile(const char *path) {
    // 1. Read file
    // 2. Compile to bytecode
    // 3. Execute top-level frame
    // 4. Return result
    return Nsn_None;
}

nsn_object *Nsn_EvalString(const char *source) {
    // 1. Compile string to bytecode
    // 2. Execute
    return Nsn_None;
}
