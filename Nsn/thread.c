/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: thread.c
 * Description: Multi-threading support wrappers.
 */

#include "nsn.h"

#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

long NsnThread_GetID(void) {
#ifdef WIN32
    return (long)GetCurrentThreadId();
#else
    return (long)pthread_self();
#endif
}

void NsnThread_Yield(void) {
#ifdef WIN32
    Sleep(0);
#else
    sched_yield();
#endif
}

/* Global Interpreter Lock (GIL) support placeholders */
static void *gil_mutex = NULL;

void NsnThread_AcquireGIL(void) {
    /* lock gil_mutex */
}

void NsnThread_ReleaseGIL(void) {
    /* unlock gil_mutex */
}