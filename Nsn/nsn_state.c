/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: nsn_state.c
 * Description: Interpreter and thread state management.
 */

#include "nsn.h"
#include <stdlib.h>

/* Global interpreter state */
static nsn_interpreter_state *main_interp = NULL;

nsn_interpreter_state *NsnInterpreterState_New(void) {
    nsn_interpreter_state *interp = (nsn_interpreter_state *)Nsn_Malloc(sizeof(nsn_interpreter_state));
    if (!interp) return NULL;
    
    interp->modules = nsn_dict_new();
    interp->builtins = nsn_dict_new();
    interp->codec_search_path = nsn_list_new();
    
    if (!main_interp) main_interp = interp;
    return interp;
}

void NsnInterpreterState_Clear(nsn_interpreter_state *interp) {
    Nsn_XDECREF(interp->modules);
    Nsn_XDECREF(interp->builtins);
    Nsn_XDECREF(interp->codec_search_path);
}

void NsnInterpreterState_Delete(nsn_interpreter_state *interp) {
    NsnInterpreterState_Clear(interp);
    if (main_interp == interp) main_interp = NULL;
    Nsn_Free(interp);
}

nsn_thread_state *NsnThreadState_New(nsn_interpreter_state *interp) {
    nsn_thread_state *tstate = (nsn_thread_state *)Nsn_Malloc(sizeof(nsn_thread_state));
    if (!tstate) return NULL;

    tstate->interp = interp;
    tstate->frame = NULL;
    tstate->recursion_depth = 0;
    tstate->overflowed = 0;

    return tstate;
}

void NsnThreadState_Delete(nsn_thread_state *tstate) {
    Nsn_Free(tstate);
}

nsn_interpreter_state *NsnInterpreterState_Main(void) {
    return main_interp;
}
