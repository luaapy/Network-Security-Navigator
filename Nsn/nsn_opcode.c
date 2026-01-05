/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: nsn_opcode.c
 * Description: Opcode definitions and mapping.
 */

#include "nsn.h"

const char *NsnOpcode_GetName(int opcode) {
    switch (opcode) {
        case OP_POP_TOP: return "POP_TOP";
        case OP_LOAD_CONST: return "LOAD_CONST";
        case OP_LOAD_NAME: return "LOAD_NAME";
        case OP_STORE_NAME: return "STORE_NAME";
        case OP_BINARY_ADD: return "BINARY_ADD";
        case OP_BINARY_SUB: return "BINARY_SUB";
        case OP_CALL_FUNCTION: return "CALL_FUNCTION";
        case OP_RETURN_VALUE: return "RETURN_VALUE";
        case OP_COMPARE_OP: return "COMPARE_OP";
        case OP_JUMP_ABSOLUTE: return "JUMP_ABSOLUTE";
        case OP_POP_JUMP_IF_FALSE: return "POP_JUMP_IF_FALSE";
        case OP_NET_SCAN: return "NET_SCAN";
        case OP_NET_PING: return "NET_PING";
        default: return "<UNKNOWN>";
    }
}
