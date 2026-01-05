/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * Main API header – high‑level public interface for embedding and using the NSN interpreter.
 */

#ifndef NSN_H
#define NSN_H

#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------------------------------------------
 * Core object system and type definitions
 * --------------------------------------------------------------------- */
#include "core/object.h"
#include "core/types.h"
#include "core/error.h"
#include "core/vm.h"

/* ---------------------------------------------------------------------
 * Internal runtime helpers (initialization, GC, etc.)
 * --------------------------------------------------------------------- */
#include "internal/nsn_internal.h"

/* ---------------------------------------------------------------------
 * Standard library headers – expose the most common modules at the top level
 * --------------------------------------------------------------------- */
#include "network/socket.h"
#include "network/tcp.h"
#include "network/udp.h"
#include "network/http.h"
#include "network/dns.h"
#include "network/icmp.h"
#include "network/packet.h"

/* ---------------------------------------------------------------------
 * Version information
 * --------------------------------------------------------------------- */
#define NSN_VERSION_MAJOR 1
#define NSN_VERSION_MINOR 0
#define NSN_VERSION_PATCH 0
#define NSN_VERSION_STRING "1.0.0"

/* ---------------------------------------------------------------------
 * Runtime lifecycle
 * --------------------------------------------------------------------- */
/**
 * Initialise the NSN interpreter. Must be called before any other NSN API.
 * Returns 0 on success, non‑zero on failure.
 */
int Nsn_Initialize(void);

/**
 * Finalise the interpreter, releasing all allocated resources.
 */
void Nsn_Finalize(void);

/**
 * Retrieve the interpreter version string.
 */
const char *Nsn_GetVersion(void);

/* ---------------------------------------------------------------------
 * Compilation & execution helpers
 * --------------------------------------------------------------------- */
/**
 * Compile a source string into a code object. `filename` is used for error
 * messages and debugging information. Returns a new code object or NULL on
 * error (the error state can be inspected via Nsn_Err_* functions).
 */
nsn_object *Nsn_Compile(const char *source, const char *filename);

/**
 * Convenience wrapper – compile and immediately execute a source string.
 */
nsn_object *Nsn_EvalString(const char *source);

/**
 * Execute a previously compiled code object. Returns the result of the script
 * or NULL if an exception was raised.
 */
nsn_object *Nsn_Execute(nsn_object *code_obj);

/**
 * Run a script file directly (compile + execute). Returns the script result.
 */
nsn_object *Nsn_RunFile(const char *path);

/* ---------------------------------------------------------------------
 * Import system
 * --------------------------------------------------------------------- */
/**
 * Import a module by name (e.g. "socket", "http"). Returns the module object
 * or NULL on failure.
 */
nsn_object *Nsn_ImportModule(const char *name);

/**
 * Retrieve a built‑in object (function, constant, etc.) by name.
 */
nsn_object *Nsn_GetBuiltin(const char *name);

/* ---------------------------------------------------------------------
 * Function calling utilities
 * --------------------------------------------------------------------- */
/**
 * Call a callable NSN object with the supplied argument array.
 * `args` may be NULL if `nargs` is 0.
 */
nsn_object *Nsn_CallFunction(nsn_object *callable,
                             nsn_object **args,
                             size_t nargs);

/* ---------------------------------------------------------------------
 * Global namespace manipulation
 * --------------------------------------------------------------------- */
/**
 * Retrieve a global variable from the interpreter's main module.
 */
nsn_object *Nsn_GetGlobal(const char *name);

/**
 * Set a global variable in the interpreter's main module. Returns 0 on success.
 */
int Nsn_SetGlobal(const char *name, nsn_object *value);

/* ---------------------------------------------------------------------
 * Error handling (mirrors core/error.h but convenient at top level)
 * --------------------------------------------------------------------- */
int Nsn_Err_Occurred(void);
const char *Nsn_Err_GetMessage(void);
void Nsn_Err_Clear(void);

/* ---------------------------------------------------------------------
 * Reference‑counting helpers – thin wrappers around the core macros
 * --------------------------------------------------------------------- */
static inline void Nsn_IncRef(nsn_object *obj) { if (obj) NSN_INCREF(obj); }
static inline void Nsn_DecRef(nsn_object *obj) { if (obj) NSN_DECREF(obj); }

/* ---------------------------------------------------------------------
 * Utility printing – used by the built‑in `print` function
 * --------------------------------------------------------------------- */
void Nsn_PrintObject(nsn_object *obj);

#ifdef __cplusplus
}
#endif

#endif // NSN_H
