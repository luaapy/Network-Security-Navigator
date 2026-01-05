/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: compile.c
 * Description: Compiles an AST into NSN bytecode.
 */

#include "nsn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --- Compiler State --- */

typedef struct {
    unsigned char *code;
    size_t pc;
    size_t capacity;
    nsn_object *consts;  /* List of constants */
    nsn_object *names;   /* List of names */
} nsn_compiler;

static void emit_byte(nsn_compiler *c, unsigned char byte) {
    if (c->pc >= c->capacity) {
        c->capacity = c->capacity ? c->capacity * 2 : 1024;
        c->code = realloc(c->code, c->capacity);
    }
    c->code[c->pc++] = byte;
}

static int add_const(nsn_compiler *c, nsn_object *obj) {
    // Add to consts list and return index
    // Placeholder logic
    return 0; 
}

/* --- AST Visitor --- */

// Assuming the AST node structure from ast.c
typedef struct _ast_node nsn_ast_node;
typedef enum {
    AST_MODULE, AST_STMT_EXPR, AST_STMT_ASSIGN,
    AST_EXPR_BINARY, AST_EXPR_NAME, AST_EXPR_CONST,
    AST_EXPR_CALL
} nsn_ast_type;

static void compile_node(nsn_compiler *c, void *node_ptr) {
    nsn_ast_node *node = (nsn_ast_node *)node_ptr;
    if (!node) return;

    // switch (node->type) {
    //     case AST_EXPR_CONST: {
    //         int idx = add_const(c, node->v.constant.obj);
    //         emit_byte(c, OP_LOAD_CONST);
    //         emit_byte(c, (unsigned char)idx);
    //         break;
    //     }
    //     case AST_EXPR_BINARY: {
    //         compile_node(c, node->v.binary.left);
    //         compile_node(c, node->v.binary.right);
    //         if (node->v.binary.op == '+') emit_byte(c, OP_BINARY_ADD);
    //         break;
    //     }
    //     case AST_STMT_EXPR: {
    //         compile_node(c, node->v.list.items[0]); // Simplified
    //         emit_byte(c, OP_POP_TOP);
    //         break;
    //     }
    //     // ... other nodes ...
    // }
}

nsn_object *Nsn_Compile_AST(void *ast_root) {
    nsn_compiler c;
    memset(&c, 0, sizeof(c));
    c.consts = nsn_list_new();
    c.names = nsn_list_new();

    compile_node(&c, ast_root);
    emit_byte(&c, OP_RETURN_VALUE);

    // Bytecode object creation
    // nsn_object *code_obj = nsn_code_new(c.code, c.pc, c.consts, c.names);
    
    // Cleanup
    free(c.code);
    Nsn_DECREF(c.consts);
    Nsn_DECREF(c.names);

    return NULL; // Should return code_obj
}
