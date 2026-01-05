/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: getopt.c
 * Description: Command line option parsing logic.
 */

#include "nsn.h"
#include <string.h>
#include <stdio.h>

int Nsn_GetOpt(int argc, char **argv, const char *optstring, char **optarg, int *optind) {
    if (*optind >= argc) return -1;

    char *arg = argv[*optind];
    if (arg[0] != '-' || arg[1] == '\0') return -1;

    char opt = arg[1];
    const char *p = strchr(optstring, opt);
    
    if (p == NULL) {
        fprintf(stderr, "nsn: unknown option -%c\n", opt);
        (*optind)++;
        return '?';
    }

    if (p[1] == ':') {
        if (arg[2] != '\0') {
            *optarg = &arg[2];
            (*optind)++;
        } else if (*optind + 1 < argc) {
            *optarg = argv[*optind + 1];
            *optind += 2;
        } else {
            fprintf(stderr, "nsn: option -%c requires an argument\n", opt);
            (*optind)++;
            return ':';
        }
    } else {
        *optarg = NULL;
        (*optind)++;
    }

    return opt;
}
