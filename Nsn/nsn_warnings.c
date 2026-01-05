/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: nsn_warnings.c
 * Description: Warning and notification system.
 */

#include "nsn.h"
#include <stdio.h>

void NsnWarn_Explicit(const char *category, const char *message, const char *filename, int lineno) {
    fprintf(stderr, "[Warning] %s: %s (in %s at line %d)\n", category, message, filename, lineno);
}

void NsnWarn_Deprecated(const char *feature, const char *filename, int lineno) {
    NsnWarn_Explicit("DeprecationWarning", feature, filename, lineno);
}

void NsnWarn_Security(const char *msg, const char *filename, int lineno) {
    NsnWarn_Explicit("SecurityWarning", msg, filename, lineno);
}
