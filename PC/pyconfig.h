/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: pyconfig.h
 * Description: Windows-specific configuration macros.
 */

#ifndef NSN_PYCONFIG_H
#define NSN_PYCONFIG_H

#ifdef _WIN32

/* Use Windows-specific features */
#define NSN_PLATFORM "win32"
#define NSN_PLATFORM_WINDOWS

/* Standard include files */
#define HAVE_STDIO_H
#define HAVE_STDLIB_H
#define HAVE_STRING_H
#define HAVE_WINSOCK2_H

/* Threading */
#define WITH_THREAD
#define NSN_THREAD_WINDOWS

/* Compiler specifics */
#ifdef _MSC_VER
#define NSN_COMPILER_MSVC
#pragma warning(disable: 4996) /* Disable deprecated POSIX warnings */
#endif

#endif /* _WIN32 */

#endif /* NSN_PYCONFIG_H */
