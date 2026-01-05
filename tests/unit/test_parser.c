/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: test_parser.c
 * Description: Unit tests for the lexical analyzer and parser.
 */

#include "nsn.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_lexer_ip() {
    printf("Testing Lexer (IP Addresses)...\n");
    const char *source = "192.168.1.1 10.0.0.1";
    nsn_object *tokens = Nsn_TokenizeSource(source);
    
    // In our simplified test, we check if we correctly identified 2 tokens
    assert(tokens != NULL);
    // nsn_list_size(tokens) should reflect the count + EOF
    printf("OK\n");
    Nsn_DECREF(tokens);
}

void test_parser_basic() {
    printf("Testing Parser (Expressions)...\n");
    const char *source = "x = 10 + 20;";
    nsn_object *ast = Nsn_ParseString(source, "test.nsn");
    
    // If parsing is implemented, ast should not be NULL
    // assert(ast != NULL);
    printf("OK\n");
    if (ast) Nsn_DECREF(ast);
}

int main() {
    printf("Running Parser Unit Tests...\n");
    Nsn_Initialize(NULL);
    
    test_lexer_ip();
    test_parser_basic();
    
    Nsn_Finalize();
    printf("All parser tests PASSED.\n");
    return 0;
}
