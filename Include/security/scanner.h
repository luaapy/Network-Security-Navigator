/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * Security scanner
 */

#ifndef NSN_SECURITY_SCANNER_H
#define NSN_SECURITY_SCANNER_H

#ifdef __cplusplus
extern "C" {
#endif



typedef struct {
    nsn_object base;
    char *target;
    int *ports;
    int port_count;
} nsn_scanner_object;

nsn_object *nsn_scanner_new(const char *target);
int nsn_scanner_add_port(nsn_object *scanner, int port);
int nsn_scanner_run(nsn_object *scanner);
nsn_object *nsn_scanner_get_results(nsn_object *scanner);


#ifdef __cplusplus
}
#endif

#endif // NSN_SECURITY_SCANNER_H
