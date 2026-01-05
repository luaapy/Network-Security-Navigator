/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: ast_unparse.c
 * Description: Converting AST back to source string.
 */

#include "nsn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Recursive unparser */
static void unparse_node(void *node_ptr, char **buf, size_t *cap, size_t *len) {
    // In a real implementation, this would switch on node types 
    // and append text to the buffer.
    
    const char *stub = "<ast_node>";
    size_t slen = strlen(stub);
    
    if (*len + slen >= *cap) {
        *cap *= 2;
        *buf = realloc(*buf, *cap);
    }
    
    strcpy(*buf + *len, stub);
    *len += slen;
}

char *NsnAST_Unparse(void *ast_root) {
    size_t cap = 1024;
    size_t len = 0;
    char *buf = malloc(cap);
    
    unparse_node(ast_root, &buf, &cap, &len);
    buf[len] = '\0';
    
    return buf;
}
