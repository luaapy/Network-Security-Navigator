/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: getplatform.c
 */

#include "nsn.h"

const char *Nsn_GetPlatform(void) {
#if defined(_WIN32) || defined(_WIN64)
    return "win32";
#elif defined(__APPLE__)
    return "darwin";
#elif defined(__linux__)
    return "linux";
#elif defined(__freebsd__)
    return "freebsd";
#else
    return "unknown";
#endif
}
