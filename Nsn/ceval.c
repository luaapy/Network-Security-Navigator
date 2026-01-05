/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * Bytecode evaluator (Interpreter Loop)
 */

#include "nsn.h"
#include <stdio.h>

#define PUSH(obj) (f->stack[f->stack_top++] = (obj))
#define POP() (f->stack[--f->stack_top])
#define TOP() (f->stack[f->stack_top - 1])

nsn_object *NsnVM_EvalFrame(nsn_frame *f) {
    unsigned char *code = f->code_bytes;
    
    for (;;) {
        unsigned char opcode = code[f->pc++];
        
        switch (opcode) {
            case OP_LOAD_CONST: {
                int idx = code[f->pc++];
                nsn_object *val = f->consts[idx];
                Nsn_IncRef(val);
                PUSH(val);
                break;
            }
            case OP_LOAD_NAME: {
                // Simplified name lookup
                int idx = code[f->pc++];
                nsn_object *name = f->names[idx];
                nsn_object *val = Nsn_GetGlobal(((nsn_string_object*)name)->data);
                if (!val) {
                    NsnErr_SetString(NsnExc_RuntimeError, "Name not found");
                    goto error;
                }
                Nsn_IncRef(val);
                PUSH(val);
                break;
            }
            case OP_STORE_NAME: {
                int idx = code[f->pc++];
                nsn_object *name = f->names[idx];
                nsn_object *val = POP();
                Nsn_SetGlobal(((nsn_string_object*)name)->data, val);
                Nsn_DecRef(val);
                break;
            }
            case OP_BINARY_ADD: {
                nsn_object *right = POP();
                nsn_object *left = POP();
                nsn_object *res = NULL;
                
                if (left->ob_type->tp_as_number && left->ob_type->tp_as_number->nb_add) {
                    res = left->ob_type->tp_as_number->nb_add(left, right);
                } else {
                    NsnErr_SetString(NsnExc_TypeError, "unsupported operand type(s) for +");
                }
                
                Nsn_DecRef(left);
                Nsn_DecRef(right);
                if (!res) goto error;
                PUSH(res);
                break;
            }
            case OP_CALL_FUNCTION: {
                int argc = code[f->pc++];
                nsn_object **args = &f->stack[f->stack_top - argc];
                nsn_object *func = f->stack[f->stack_top - argc - 1];
                nsn_object *res = Nsn_CallFunction(func, args, argc);
                
                // Cleanup stack
                for (int i = 0; i < argc + 1; i++) {
                    Nsn_DecRef(POP());
                }
                
                if (!res) goto error;
                PUSH(res);
                break;
            }
            case OP_RETURN_VALUE: {
                return POP();
            }
            case OP_POP_TOP: {
                Nsn_DecRef(POP());
                break;
            }
            case OP_COMPARE_OP: {
                int op = code[f->pc++];
                nsn_object *right = POP();
                nsn_object *left = POP();
                // nsn_object *res = nsn_object_compare(left, right, op);
                // PUSH(res);
                Nsn_DecRef(left);
                Nsn_DecRef(right);
                break;
            }
            case OP_JUMP_ABSOLUTE: {
                f->pc = code[f->pc++];
                break;
            }
            case OP_POP_JUMP_IF_FALSE: {
                int target = code[f->pc++];
                nsn_object *cond = POP();
                if (cond == Nsn_False || cond == Nsn_None) {
                    f->pc = target;
                }
                Nsn_DecRef(cond);
                break;
            }
            default:
                fprintf(stderr, "Unhandled opcode: %d at PC %zu\n", opcode, f->pc - 1);
                NsnErr_SetString(NsnExc_RuntimeError, "Unknown opcode");
                goto error;
        }

        if (Nsn_Err_Occurred()) goto error;
    }

error:
    while (f->stack_top > 0) {
        Nsn_DecRef(POP());
    }
    return NULL;
}
