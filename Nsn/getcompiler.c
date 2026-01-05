/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: getcompiler.c
 */

#include "nsn.h"

const char *Nsn_GetCompiler(void) {
#if defined(__clang__)
    return "[Clang " __clang_version__ "]";
#elif defined(__GNUC__)
    return "[GCC " __VERSION__ "]";
#elif defined(_MSC_VER)
    return "[MSVC " _CRT_STRINGIZE(_MSC_VER) "]";
#else
    return "[Unknown Compiler]";
#endif
}
