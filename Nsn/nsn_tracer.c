/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: nsn_tracer.c
 * Description: Execution tracing hooks.
 */

#include "nsn.h"
#include <stdio.h>

typedef void (*nsn_trace_func)(nsn_frame *, int, nsn_object *);

static nsn_trace_func global_tracer = NULL;

void NsnTrace_SetTracer(nsn_trace_func func) {
    global_tracer = func;
}

void NsnTrace_Dispatch(nsn_frame *frame, int event, nsn_object *arg) {
    if (global_tracer) {
        global_tracer(frame, event, arg);
    }
}

void NsnTrace_Default(nsn_frame *frame, int event, nsn_object *arg) {
    // printf("Trace: frame %p, event %d\n", (void*)frame, event);
}
