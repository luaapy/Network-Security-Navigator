/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * Abstract Syntax Tree definitions
 */

#ifndef NSN_CORE_AST_H
#define NSN_CORE_AST_H

#include "core/token.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    // Expressions
    NSN_AST_LITERAL,
    NSN_AST_BINARY,
    NSN_AST_UNARY,
    NSN_AST_VARIABLE,
    NSN_AST_CALL,
    NSN_AST_ASSIGNMENT,

    // Statements
    NSN_AST_EXPR_STMT,
    NSN_AST_PRINT_STMT,
    NSN_AST_SCAN_STMT,
    NSN_AST_PING_STMT,
    NSN_AST_BLOCK,
    NSN_AST_IF,
    NSN_AST_WHILE,
    NSN_AST_FUNCTION,
    NSN_AST_RETURN
} NsnASTNodeKind;

typedef struct NsnASTNode NsnASTNode;

struct NsnASTNode {
    NsnASTNodeKind kind;
    int line;
    // Union of possible node data could go here, 
    // or we can use specific structs and cast.
    // For simplicity in Phase 1 C, let's use a tagged union approach.
    
    union {
        // Literal
        struct {
            NsnToken value; 
        } literal;

        // Binary Op
        struct {
            NsnASTNode *left;
            NsnToken op;
            NsnASTNode *right;
        } binary;

        // Unary Op
        struct {
            NsnToken op;
            NsnASTNode *right;
        } unary;
        
        // Variable
        struct {
            NsnToken name;
        } variable;

        // Assignment
        struct {
            NsnToken name;
            NsnASTNode *value;
        } assignment;

        // Call
        struct {
            NsnASTNode *callee;
            NsnASTNode **args; // Array of pointers
            int arg_count;
        } call;
        
        // Expression Statement & Print/Scan/Ping
        struct {
            NsnASTNode *expression;
        } expr_stmt;

        // Block
        struct {
            NsnASTNode **statements;
            int stmt_count;
        } block;

        // If
        struct {
            NsnASTNode *condition;
            NsnASTNode *then_branch;
            NsnASTNode *else_branch;
        } if_stmt;

        // Function
        struct {
            NsnToken name;
            NsnToken *params; // Array of tokens
            int param_count;
            NsnASTNode *body;
        } function;
        
        // Return
        struct {
            NsnToken keyword;
            NsnASTNode *value;
        } return_stmt;
    } as;
};

// Constructor prototypes
NsnASTNode* NsnAST_NewLiteral(NsnToken value);
NsnASTNode* NsnAST_NewBinary(NsnASTNode *left, NsnToken op, NsnASTNode *right);
NsnASTNode* NsnAST_NewUnary(NsnToken op, NsnASTNode *right);
NsnASTNode* NsnAST_NewVariable(NsnToken name);
NsnASTNode* NsnAST_NewAssignment(NsnToken name, NsnASTNode *value);
NsnASTNode* NsnAST_NewCall(NsnASTNode *callee, NsnASTNode **args, int arg_count);
NsnASTNode* NsnAST_NewExprStmt(NsnASTNode *expression);
NsnASTNode* NsnAST_NewPrintStmt(NsnASTNode *expression);
NsnASTNode* NsnAST_NewBlock(NsnASTNode **statements, int stmt_count);

void NsnAST_Free(NsnASTNode *node);

#ifdef __cplusplus
}
#endif

#endif // NSN_CORE_AST_H
