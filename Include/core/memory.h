/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * Memory management
 */

#ifndef NSN_CORE_MEMORY_H
#define NSN_CORE_MEMORY_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Core allocator (wraps malloc/free) */
void *NsnMem_Malloc(size_t size);
void *NsnMem_Realloc(void *ptr, size_t size);
void NsnMem_Free(void *ptr);

/* Arena Allocator for rapid short-lived object allocation */
typedef struct _nsn_arena nsn_arena;

nsn_arena *NsnArena_New(size_t block_size);
void *NsnArena_Alloc(nsn_arena *arena, size_t size);
void NsnArena_Free(nsn_arena *arena);
void NsnArena_Reset(nsn_arena *arena);

/* Garbage Collector Interface */
void NsnGC_Collect(void);
void NsnGC_Track(void *obj);
void NsnGC_Untrack(void *obj);

#ifdef __cplusplus
}
#endif

#endif // NSN_CORE_MEMORY_H
