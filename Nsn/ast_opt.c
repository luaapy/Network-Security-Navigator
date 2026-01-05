/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: ast_opt.c
 * Description: AST-level optimizations including constant folding.
 */

#include "nsn.h"

/* 
 * AST Node Structure (Internal Preview)
 * typedef struct _ast_node {
 *     int type;
 *     struct _ast_node *left, *right;
 *     nsn_object *value;
 * } nsn_ast_node;
 */

typedef struct _ast_node {
    int type;
    struct _ast_node *left, *right;
    nsn_object *value;
} nsn_ast_node;

#define NODE_BINARY_ADD 1
#define NODE_CONSTANT   2

static nsn_ast_node *fold_constants(nsn_ast_node *node) {
    if (!node) return NULL;

    node->left = fold_constants(node->left);
    node->right = fold_constants(node->right);

    /* Constant Folding for Addition */
    if (node->type == NODE_BINARY_ADD) {
        if (node->left && node->left->type == NODE_CONSTANT &&
            node->right && node->right->type == NODE_CONSTANT) {
            
            nsn_object *lv = node->left->value;
            nsn_object *rv = node->right->value;
            
            /* Assuming simple integer addition for the optimizer demo */
            if (strcmp(lv->ob_type->tp_name, "int") == 0 &&
                strcmp(rv->ob_type->tp_name, "int") == 0) {
                
                typedef struct { NSN_OBJECT_HEAD long lval; } nsn_int_object;
                long result = ((nsn_int_object*)lv)->lval + ((nsn_int_object*)rv)->lval;
                
                nsn_object *new_val = nsn_int_from_long(result);
                
                /* Transform to constant node */
                node->type = NODE_CONSTANT;
                node->value = new_val;
                // In a real implementation, we'd free left/right nodes here
                node->left = node->right = NULL;
            }
        }
    }

    return node;
}

void NsnAST_Optimize(void *ast_root) {
    fold_constants((nsn_ast_node *)ast_root);
}
