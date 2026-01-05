/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: nsn_frame.c
 * Description: Call frame management for the bytecode interpreter.
 */

#include "nsn.h"
#include <stdlib.h>

nsn_frame *NsnFrame_New(nsn_thread_state *tstate, nsn_object *code, nsn_object *globals) {
    nsn_frame *f = (nsn_frame *)Nsn_Malloc(sizeof(nsn_frame));
    if (!f) return NULL;

    f->back = tstate->frame;
    tstate->frame = f;

    f->code = code;
    Nsn_INCREF(code);
    
    // Extract bytecode, constants, names from code object
    // f->code_bytes = ...
    // f->consts = ...
    
    f->globals = globals;
    Nsn_INCREF(globals);
    
    f->locals = nsn_dict_new();
    f->pc = 0;
    f->stack_top = 0;

    return f;
}

void NsnFrame_Delete(nsn_frame *f, nsn_thread_state *tstate) {
    if (tstate->frame == f) {
        tstate->frame = f->back;
    }
    
    Nsn_XDECREF(f->code);
    Nsn_XDECREF(f->globals);
    Nsn_XDECREF(f->locals);
    
    // In a real execution, stack objects would be decref'd here
    
    Nsn_Free(f);
}
