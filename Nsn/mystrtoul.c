/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: mystrtoul.c
 * Description: Portable string to unsigned long conversion.
 */

#include "nsn.h"
#include <stdlib.h>
#include <errno.h>

unsigned long Nsn_OS_strtoul(const char *str, char **endptr, int base) {
    unsigned long result;
    
    errno = 0;
    result = strtoul(str, endptr, base);
    
    if (errno == ERANGE) {
        /* Handle overflow/underflow if necessary for the interpreter */
    }
    
    return result;
}
