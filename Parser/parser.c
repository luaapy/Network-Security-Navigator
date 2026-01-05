/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: parser.c
 * Description: Main entry point for the NSN parser.
 */

#include "nsn.h"

nsn_object *Nsn_ParseString(const char *source, const char *filename) {
    /*
     * 1. Tokenize the source
     * 2. Initialize the PEG parser
     * 3. Execute parsing
     * 4. Return the AST (or NULL on error)
     */
    
    // placeholder logic
    nsn_object *tokens = Nsn_TokenizeSource(source);
    if (!tokens) return NULL;
    
    // void *p = NsnPegen_NewParser(tokens);
    // nsn_object *ast = NsnPegen_RunParser(p);
    // NsnPegen_FreeParser(p);
    
    Nsn_DECREF(tokens);
    return NULL;
}

nsn_object *Nsn_ParseFile(const char *path) {
    // Read file and call Nsn_ParseString
    return NULL;
}
