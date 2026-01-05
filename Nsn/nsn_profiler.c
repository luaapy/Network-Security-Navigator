/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: nsn_profiler.c
 * Description: Execution profiling and timing.
 */

#include "nsn.h"
#include <time.h>
#include <stdio.h>

static clock_t start_time;

void NsnProfile_Start(void) {
    start_time = clock();
}

void NsnProfile_Stop(void) {
    clock_t end_time = clock();
    double cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("[Profiler] Execution time: %f seconds\n", cpu_time_used);
}

void NsnProfile_LogCall(const char *func_name) {
    // Collect statistics for function calls
}
