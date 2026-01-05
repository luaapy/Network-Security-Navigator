/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: nsnconfig.h
 *
 * Configuration API for the NSN interpreter. This header provides a
 * programmable way to tweak interpreter behaviour at runtime (logging,
 * optimisation levels, resource limits, etc.) and also defines compile‑time
 * feature toggles.
 */

#ifndef NSNCONFIG_H
#define NSNCONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nsn.h"

/* ---------------------------------------------------------------------
 * Compile‑time feature flags (can be overridden by the build system)
 * --------------------------------------------------------------------- */
#ifndef NSN_ENABLE_JIT
#define NSN_ENABLE_JIT 0   /* 1 = enable Just‑In‑Time compilation */
#endif

#ifndef NSN_ENABLE_GC
#define NSN_ENABLE_GC 1    /* 1 = enable garbage collector */
#endif

#ifndef NSN_MAX_STACK_SIZE
#define NSN_MAX_STACK_SIZE 4096  /* Maximum VM value stack entries */
#endif

/* ---------------------------------------------------------------------
 * Runtime configuration structure
 * --------------------------------------------------------------------- */
typedef struct {
    /* Logging ---------------------------------------------------------- */
    int   log_level;            /* 0=none, 1=error, 2=warning, 3=info, 4=debug */
    const char *log_file;       /* Path to log file, NULL = stdout */

    /* Resource limits ------------------------------------------------- */
    size_t max_memory;          /* Hard limit for total allocations (bytes) */
    size_t max_recursion_depth; /* Maximum call‑stack depth */

    /* Optimisation ---------------------------------------------------- */
    int   opt_level;            /* 0 = none, 1 = basic, 2 = aggressive */
    int   enable_jit;           /* Runtime toggle for JIT (overrides compile flag) */

    /* Security -------------------------------------------------------- */
    int   sandbox_enabled;      /* Restrict filesystem/network access */
    const char *allowed_dirs;   /* Comma‑separated list of safe directories */
} NsnConfig;

/* ---------------------------------------------------------------------
 * Global configuration accessor
 * --------------------------------------------------------------------- */
/**
 * Retrieve a pointer to the global configuration structure. The returned
 * pointer is valid for the lifetime of the interpreter. Modifying the fields
 * directly is allowed but changes only take effect after a call to
 * Nsn_Config_Apply().
 */
NsnConfig *Nsn_GetConfig(void);

/**
 * Apply the current configuration. This should be called after any changes
 * to the NsnConfig fields (e.g., after parsing a config file or processing
 * command‑line flags). Returns 0 on success, non‑zero on failure.
 */
int Nsn_Config_Apply(void);

/**
 * Load configuration from a simple INI‑style file. Only a subset of fields is
 * recognised; unknown keys are ignored. Returns 0 on success.
 */
int Nsn_Config_LoadFile(const char *path);

/**
 * Reset configuration to built‑in defaults.
 */
void Nsn_Config_Reset(void);

/* ---------------------------------------------------------------------
 * Helper macros for logging (useful throughout the code base)
 * --------------------------------------------------------------------- */
#define NSN_LOG_ERROR(fmt, ...)   Nsn_Log(1, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define NSN_LOG_WARN(fmt, ...)    Nsn_Log(2, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define NSN_LOG_INFO(fmt, ...)    Nsn_Log(3, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define NSN_LOG_DEBUG(fmt, ...)   Nsn_Log(4, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

/**
 * Low‑level logging function used by the macros above.
 */
void Nsn_Log(int level, const char *file, int line, const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif // NSNCONFIG_H
