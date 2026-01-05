/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: string_parser.c
 * Description: Logic for parsing string literals and escape sequences.
 */

#include "nsn.h"
#include <string.h>
#include <stdlib.h>

char *Nsn_ParseStringLiteral(const char *raw, size_t *out_len) {
    /* 
     * Handle:
     * - \n, \t, \r
     * - \" and \\
     * - \xHH hex escapes
     */
    size_t len = strlen(raw);
    char *result = malloc(len + 1);
    size_t j = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (raw[i] == '\\' && i + 1 < len) {
            switch (raw[++i]) {
                case 'n': result[j++] = '\n'; break;
                case 't': result[j++] = '\t'; break;
                case 'r': result[j++] = '\r'; break;
                case '"': result[j++] = '"'; break;
                case '\\': result[j++] = '\\'; break;
                default: result[j++] = raw[i]; break;
            }
        } else {
            result[j++] = raw[i];
        }
    }
    
    result[j] = '\0';
    if (out_len) *out_len = j;
    return result;
}
