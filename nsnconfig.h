/*
 * NSN (Network Security Navigator)
 * Copyright (c) Nosan
 * Licensed under MIT License
 *
 * File: nsnconfig.h
 * Description: Auto-generated or manual project configuration macros.
 */

#ifndef NSN_CONFIG_H
#define NSN_CONFIG_H

/* Version Information */
#define NSN_VERSION_MAJOR 1
#define NSN_VERSION_MINOR 0
#define NSN_VERSION_PATCH 0
#define NSN_VERSION "1.0.0"

/* Feature Flags */
#define WITH_PCAP        1
#define WITH_OPENSSL     1
#define WITH_SSH         1
#define WITH_THREAD      1

/* Platform Configuration */
#ifdef _WIN32
  #define NSN_PLATFORM "win32"
#elif defined(__APPLE__)
  #define NSN_PLATFORM "darwin"
#else
  #define NSN_PLATFORM "linux"
#endif

/* Memory management */
#define NSN_MALLOC_MAX 0x7FFFFFFF

#endif /* NSN_CONFIG_H */
