/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * Virtual machine
 */

#ifndef NSN_CORE_VM_H
#define NSN_CORE_VM_H

#include "object.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NSN_STACK_SIZE 2048

/* Execution Frame */
typedef struct _frame {
    struct _frame *back;    /* Previous frame */
    nsn_object *code;       /* Code object being executed */
    nsn_object *globals;    /* Global variables */
    nsn_object *locals;     /* Local variables */
    
    /* Value Stack */
    nsn_object *stack[NSN_STACK_SIZE];
    int stacktop;           /* Index of the next empty slot */
    
    /* Instruction Pointer */
    unsigned char *code_bytes;
    size_t pc;              /* Program Counter */
} nsn_frame;

/* VM Interface */
nsn_object *NsnVM_EvalFrame(nsn_frame *frame);
void NsnVM_Push(nsn_frame *frame, nsn_object *obj);
nsn_object *NsnVM_Pop(nsn_frame *frame);
nsn_object *NsnVM_Top(nsn_frame *frame);

#ifdef __cplusplus
}
#endif

#endif // NSN_CORE_VM_H
