/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: config.c
 * Description: Build-time configuration data.
 */

#include "nsn.h"

#ifndef NSN_PLATFORM
#define NSN_PLATFORM "unknown"
#endif

const char *Nsn_GetPlatform(void) {
    return NSN_PLATFORM;
}

const char *Nsn_GetCopyright(void) {
    return "Copyright (c) 2025-2026 NSN Contributors";
}

const char *Nsn_GetCompiler(void) {
#ifdef __clang__
    return "clang " __clang_version__;
#elif defined(__GNUC__)
    return "gcc " __VERSION__;
#elif defined(_MSC_VER)
    return "msvc";
#else
    return "unknown";
#endif
}

void _nsn_init_config(void) {
    // This file mostly provides string constants used by other modules
}
