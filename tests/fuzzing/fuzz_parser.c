/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: fuzz_parser.c
 * Description: LibFuzzer-based fuzzer for the NSN grammar and parser.
 */

#include "nsn.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

/**
 * LibFuzzer entry point targeting the NSN Parser.
 * It feeds fuzzed strings to the PEG-based parser and AST generator
 * to detect syntax-related crashes or memory leaks during compilation.
 */
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    static int initialized = 0;
    if (!initialized) {
        // Initialize runtime with sandbox enabled for safety during fuzzing
        NsnConfig config;
        Nsn_Config_LoadFile(&config, NULL);
        config.sandbox_enabled = 1;
        Nsn_Initialize(&config);
        initialized = 1;
    }

    // Convert raw data to a null-terminated string for the parser
    char *source = (char *)malloc(size + 1);
    if (!source) return 0;
    memcpy(source, data, size);
    source[size] = '\0';

    /* Target 1: Lexing and Tokenization */
    nsn_object *tokens = Nsn_TokenizeSource(source);
    if (tokens) {
        Nsn_DECREF(tokens);
    }

    /* Target 2: Deep Parser and AST Generation */
    nsn_object *ast = Nsn_ParseString(source, "fuzz_input.nsn");
    if (ast) {
        // If parsing succeeded, try to run it through the optimizer
        // to find bugs in the constant folding or visitor logic.
        // NsnAST_Optimize(ast);
        Nsn_DECREF(ast);
    }

    free(source);
    return 0;
}
