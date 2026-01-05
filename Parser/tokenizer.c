/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: tokenizer.c
 * Description: High-level tokenization interface for the parser.
 */

#include "nsn.h"
#include <stdlib.h>

nsn_object *Nsn_TokenizeSource(const char *source) {
    /* 
     * 1. Call the internal lexer (from lexer.c)
     * 2. Convert raw NsnToken array into an NSN List of Token objects
     * 3. Return the list
     */
    return nsn_list_new(); 
}

void Nsn_TokenFree(nsn_object *token_list) {
    Nsn_XDECREF(token_list);
}
