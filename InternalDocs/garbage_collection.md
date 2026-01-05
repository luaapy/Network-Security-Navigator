# NSN Garbage Collection Design

NSN uses a **hybrid memory‑management strategy** that combines **reference counting** (for deterministic deallocation) with an **optional incremental mark‑and‑sweep collector** for cyclic data structures.  The collector can be enabled or disabled at runtime via the configuration system (`nsnconfig.h`).

---

## 1. Why a Hybrid Approach?
* **Reference counting** provides immediate reclamation of most objects and integrates naturally with the atomic helpers (`pycore_atomic.h`).
* Pure reference counting cannot reclaim **cycles** (e.g., two objects referencing each other).  The mark‑and‑sweep phase detects and frees those cycles.
* The incremental nature keeps pause times short, which is important for network‑tool scripts that must remain responsive.

---

## 2. Core Data Structures

```c
/* In memory.h */
typedef struct _nsn_arena nsn_arena;   // fast bump‑allocator for short‑lived objects

/* In gc.h (exposed via internal/nsn_internal.h) */
typedef struct _nsn_gc_state {
    nsn_arena *arena;          // arena used for allocation
    nsn_object **tracklist;    // dynamically‑grown array of tracked objects
    size_t      tracklen;      // number of entries in tracklist
    size_t      trackcap;      // capacity of tracklist
    int         collecting;    // flag: 1 = GC in progress
} nsn_gc_state;
```

*All heap‑allocated `nsn_object`s are created through `NsnMem_Malloc` and automatically added to the GC’s tracking list via `Nsn_GC_Track`.*

---

## 3. Public GC API (exposed in `nsn_internal.h`)

| Function | Purpose |
|----------|---------|
| `void Nsn_GC_Track(nsn_object *obj);` | Register a newly allocated object with the collector. |
| `void Nsn_GC_Untrack(nsn_object *obj);` | Remove an object from the tracking list (called when the object’s ref‑count reaches zero). |
| `void Nsn_GC_Collect(void);` | Perform a **full incremental collection cycle**.  The function may be called manually or automatically when the interpreter detects memory pressure. |
| `int Nsn_GC_IsEnabled(void);` | Returns the current GC enable flag (set via `nsnconfig.h`). |

The collector is **incremental**: each call to `Nsn_GC_Collect` processes a small slice of the object graph (a few hundred objects) and then returns, allowing the interpreter to continue executing user code.

---

## 4. Collection Algorithm (Mark‑and‑Sweep)
1. **Mark Phase**
   * Start from the *root set*: global variables, the current call stack, and any objects held by the VM’s value stack.
   * Recursively traverse object fields (`ob_type->tp_traverse`) marking each visited object by setting a `gc_mark` flag.
2. **Sweep Phase**
   * Iterate over the `tracklist`.  Any object whose `gc_mark` flag is **clear** is unreachable and therefore freed with `nsn_object_dealloc`.
   * Reset the `gc_mark` flag on live objects for the next cycle.
3. **Incremental Steps**
   * The algorithm splits the mark and sweep work into *steps* based on a configurable `NSN_GC_STEP_SIZE` (default 256 objects).  After each step the VM checks for pending I/O or user interrupts.

---

## 5. Interaction with Reference Counting
* When an object’s reference count drops to zero, `nsn_object_dealloc` is called **immediately** – the object is also removed from the GC tracking list.
* If a cycle exists, each object in the cycle will retain a non‑zero ref‑count, so the GC is the only mechanism that can break the cycle.
* The GC respects atomic reference‑count updates (`nsn_atomic_inc_ref`/`nsn_atomic_dec_ref`) to remain thread‑safe when the optional POSIX‑threads mode is enabled.

---

## 6. Configuration (`nsnconfig.h`)
```c
#ifndef NSN_ENABLE_GC
#define NSN_ENABLE_GC 1   /* 1 = enable GC, 0 = reference‑count only */
#endif

#ifndef NSN_GC_STEP_SIZE
#define NSN_GC_STEP_SIZE 256   /* objects processed per incremental call */
#endif
```
* The flag can be toggled at runtime via `Nsn_Config_Apply()`.
* When disabled, `Nsn_GC_Collect` becomes a no‑op and `Nsn_GC_Track/Untrack` are thin wrappers.

---

## 7. Debugging & Diagnostics
* **GC statistics** can be printed with `NSN_LOG_DEBUG("GC: %zu tracked, %zu live", state->tracklen, live_count);`
* The `NSN_ENABLE_DEBUG` build flag adds assertions that verify the consistency of the `gc_mark` flag after each collection.
* A command‑line switch `--gc‑verbose` (exposed in `nsn.c`) enables periodic logging of collection cycles.

---

## 8. Extending the Collector
When adding a new built‑in type that contains references to other objects (e.g., a custom container), implement the `tp_traverse` slot in the type object:
```c
static void mytype_traverse(nsn_object *obj, void (*visit)(nsn_object *)) {
    mytype *mt = (mytype *)obj;
    if (mt->items) {
        for (size_t i = 0; i < mt->len; ++i) {
            visit(mt->items[i]);
        }
    }
}
```
The GC will call this function during the mark phase, ensuring that all reachable objects are correctly marked.

---

*Keep this document synchronized with any changes to the GC implementation or configuration flags.*
