/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: nsn_security.c
 * Description: Security manager and sandbox enforcement.
 */

#include "nsn.h"
#include <stdio.h>

static int g_sandbox_enabled = 0;

void NsnSecurity_EnableSandbox(void) {
    g_sandbox_enabled = 1;
}

int NsnSecurity_CheckPermission(const char *action, const char *resource) {
    if (!g_sandbox_enabled) return 1;

    /* Sandbox Policy:
     * - "file_read": only allowed in ./tmp/
     * - "net_connect": restricted to specific IP ranges (managed via types.nsn)
     */
    
    // Simplified enforcement logic
    printf("[Security] Checking permission for %s on %s\n", action, resource);
    
    return 1; // For now, all allowed, but hook is active
}

void NsnSecurity_LogViolation(const char *msg) {
    fprintf(stderr, "[Security Alert] Sandbox violation: %s\n", msg);
}
