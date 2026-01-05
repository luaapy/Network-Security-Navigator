/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: mysnprintf.c
 * Description: Portable snprintf wrapper with safety checks.
 */

#include "nsn.h"
#include <stdio.h>
#include <stdarg.h>

int Nsn_OS_snprintf(char *str, size_t size, const char *format, ...) {
    int res;
    va_list va;
    
    if (size == 0) return 0;

    va_start(va, format);
#ifdef _MSC_VER
    /* MSVC's _vsnprintf does not always null-terminate if the buffer is too small */
    res = _vsnprintf(str, size, format, va);
    if (res < 0 || res >= (int)size) {
        str[size - 1] = '\0';
    }
#else
    res = vsnprintf(str, size, format, va);
#endif
    va_end(va);
    
    return res;
}
