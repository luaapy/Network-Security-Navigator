/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * Internal APIs
 */

#ifndef NSN_INTERNAL_H
#define NSN_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "core/object.h"
#include "core/memory.h"
#include "core/error.h"
#include "core/vm.h"

/* ------------------------------------------------------------
 * Runtime initialization / finalization
 * ------------------------------------------------------------ */

/**
 * Initialize the NSN runtime. Must be called before any other NSN API.
 * Returns 0 on success, non‑zero on failure.
 */
int Nsn_Initialize(void);

/**
 * Finalize the NSN runtime, releasing all resources.
 */
void Nsn_Finalize(void);

/**
 * Initialize all built-in modules defined in Modules/Setup.
 */
void Nsn_InitBuiltinModules(void);

/**
 * Retrieve the version string of the NSN interpreter.
 */
const char *Nsn_GetVersion(void);

/* ------------------------------------------------------------
 * Compilation & Execution
 * ------------------------------------------------------------ */

/**
 * Compile NSN source code (UTF‑8 string) to a code object.
 * On success returns a new nsn_object representing compiled bytecode.
 * On error sets the current error state and returns NULL.
 */
nsn_object *Nsn_Compile(const char *source, const char *filename);

/**
 * Execute a compiled code object in a new frame.
 * Returns the result of the script or NULL on error.
 */
nsn_object *Nsn_Execute(nsn_object *code_obj);

/**
 * Run a script file directly (convenience wrapper).
 */
nsn_object *Nsn_RunFile(const char *path);

/* ------------------------------------------------------------
 * Import system
 * ------------------------------------------------------------ */

/**
 * Import a module by name. Returns a module object on success.
 */
nsn_object *Nsn_ImportModule(const char *name);

/* ------------------------------------------------------------
 * Garbage collection helpers (internal)
 * ------------------------------------------------------------ */

/**
 * Trigger a full garbage‑collection cycle.
 */
void Nsn_GC_Collect(void);

/**
 * Register an object with the GC (called when a new object is created).
 */
void Nsn_GC_Track(nsn_object *obj);

/**
 * Unregister an object from the GC (called when an object is destroyed).
 */
void Nsn_GC_Untrack(nsn_object *obj);

/* ------------------------------------------------------------
 * Utility functions
 * ------------------------------------------------------------ */

/**
 * Convert a C string to an NSN string object.
 */
nsn_object *nsn_string_from_cstring(const char *cstr);

/**
 * Convert a long integer to an NSN integer object.
 */
nsn_object *nsn_int_from_long(long value);

/**
 * Create a new empty list object.
 */
nsn_object *nsn_list_new(void);

/**
 * Create a new empty dict object.
 */
nsn_object *nsn_dict_new(void);

/**
 * Print an NSN object to stdout (used by the built‑in print function).
 */
void nsn_print_object(nsn_object *obj);

#ifdef __cplusplus
}
#endif

#endif // NSN_INTERNAL_H
