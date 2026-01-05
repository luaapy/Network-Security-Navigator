/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: scannermodule.c
 * Description: Core port scanner implementation.
 */

#include "nsn.h"
#include "security/scanner.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#endif

/* --- Scanner Object Logic --- */

static void scanner_dealloc(nsn_object *op) {
    nsn_scanner_object *s = (nsn_scanner_object *)op;
    free(s->target);
    free(s->ports);
    NsnMem_Free(s);
}

nsn_type Nsn_ScannerType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "_security.Scanner",
    .tp_basicsize = sizeof(nsn_scanner_object),
    .tp_dealloc = scanner_dealloc
};

nsn_object *nsn_scanner_new(const char *target) {
    nsn_scanner_object *s = (nsn_scanner_object *)NsnMem_Malloc(sizeof(nsn_scanner_object));
    s->ob_refcnt = 1;
    s->ob_type = &Nsn_ScannerType;
    s->target = strdup(target);
    s->ports = NULL;
    s->port_count = 0;
    return (nsn_object *)s;
}

int nsn_scanner_add_port(nsn_object *scanner, int port) {
    nsn_scanner_object *s = (nsn_scanner_object *)scanner;
    s->ports = realloc(s->ports, sizeof(int) * (s->port_count + 1));
    s->ports[s->port_count++] = port;
    return 0;
}

int nsn_scanner_run(nsn_object *scanner) {
    nsn_scanner_object *s = (nsn_scanner_object *)scanner;
    int open_count = 0;

    for (int i = 0; i < s->port_count; i++) {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) continue;

        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(s->ports[i]);
        inet_pton(AF_INET, s->target, &addr.sin_addr);

        // Simple blocking connect with small timeout would be better, 
        // but for now synchronous connect:
        if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == 0) {
            open_count++;
        }

#ifdef WIN32
        closesocket(sock);
#else
        close(sock);
#endif
    }
    return open_count;
}

nsn_object *nsn_scanner_get_results(nsn_object *scanner) {
    // Return a list of open ports (placeholder)
    return nsn_list_new();
}

/* --- Module Registration --- */

void _nsn_init_scanner(void) {
    nsn_object *m = nsn_module_new("scanner");
    // Register methods...
}
