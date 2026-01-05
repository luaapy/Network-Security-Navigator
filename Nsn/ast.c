/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: ast.c
 * Description: Abstract Syntax Tree (AST) node management.
 */

#include "nsn.h"
#include <stdlib.h>
#include <string.h>

/* --- AST Node Management --- */

typedef enum {
    AST_MODULE,
    AST_STMT_EXPR,
    AST_STMT_ASSIGN,
    AST_EXPR_BINARY,
    AST_EXPR_NAME,
    AST_EXPR_CONST,
    AST_EXPR_CALL,
    AST_NET_SCAN,
    AST_NET_PING
} nsn_ast_type;

typedef struct _nsn_ast_node {
    nsn_ast_type type;
    int line;
    union {
        struct {
            struct _nsn_ast_node **items;
            int count;
        } list;
        struct {
            struct _nsn_ast_node *left;
            struct _nsn_ast_node *right;
            int op;
        } binary;
        struct {
            const char *id;
            struct _nsn_ast_node *value;
        } assign;
        struct {
            nsn_object *obj;
        } constant;
        struct {
            const char *id;
        } name;
        struct {
            struct _nsn_ast_node *func;
            struct _nsn_ast_node **args;
            int arg_count;
        } call;
    } v;
} nsn_ast_node;

nsn_ast_node *NsnAST_NewNode(nsn_ast_type type, int line) {
    nsn_ast_node *node = (nsn_ast_node *)malloc(sizeof(nsn_ast_node));
    if (!node) return NULL;
    memset(node, 0, sizeof(nsn_ast_node));
    node->type = type;
    node->line = line;
    return node;
}

nsn_ast_node *NsnAST_NewConstant(nsn_object *obj, int line) {
    nsn_ast_node *node = NsnAST_NewNode(AST_EXPR_CONST, line);
    if (node) {
        Nsn_INCREF(obj);
        node->v.constant.obj = obj;
    }
    return node;
}

nsn_ast_node *NsnAST_NewBinary(nsn_ast_node *left, int op, nsn_ast_node *right, int line) {
    nsn_ast_node *node = NsnAST_NewNode(AST_EXPR_BINARY, line);
    if (node) {
        node->v.binary.left = left;
        node->v.binary.right = right;
        node->v.binary.op = op;
    }
    return node;
}

void NsnAST_Free(nsn_ast_node *node) {
    if (!node) return;
    
    switch (node->type) {
        case AST_MODULE:
            for (int i = 0; i < node->v.list.count; i++) {
                NsnAST_Free(node->v.list.items[i]);
            }
            free(node->v.list.items);
            break;
        case AST_STMT_ASSIGN:
            free((void *)node->v.assign.id);
            NsnAST_Free(node->v.assign.value);
            break;
        case AST_EXPR_BINARY:
            NsnAST_Free(node->v.binary.left);
            NsnAST_Free(node->v.binary.right);
            break;
        case AST_EXPR_CONST:
            Nsn_XDECREF(node->v.constant.obj);
            break;
        case AST_EXPR_NAME:
            free((void *)node->v.name.id);
            break;
        case AST_EXPR_CALL:
            NsnAST_Free(node->v.call.func);
            for (int i = 0; i < node->v.call.arg_count; i++) {
                NsnAST_Free(node->v.call.args[i]);
            }
            free(node->v.call.args);
            break;
        default:
            break;
    }
    free(node);
}
