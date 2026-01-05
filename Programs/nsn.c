/*
 * NSN (Network Security Navigator)
 * Main interpreter entry point
 */

#include "nsn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(const char *progname) {
    printf("Usage: %s [options] [-c cmd | script.nsn] [args]\n", progname);
    printf("Options:\n");
    printf("  -c cmd     : program passed in as string\n");
    printf("  -h         : print this help message and exit\n");
    printf("  -v         : print NSN version and exit\n");
    printf("  --sandbox  : enable secure sandboxing mode\n");
}

int main(int argc, char **argv) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    NsnConfig config;
    Nsn_Config_LoadFile(&config, NULL); // Load defaults

    int arg_idx = 1;
    char *command = NULL;
    char *filename = NULL;

    while (arg_idx < argc && argv[arg_idx][0] == '-') {
        if (strcmp(argv[arg_idx], "-h") == 0) {
            print_usage(argv[0]);
            return 0;
        } else if (strcmp(argv[arg_idx], "-v") == 0) {
            printf("NSN %s\n", NSN_VERSION);
            return 0;
        } else if (strcmp(argv[arg_idx], "-c") == 0) {
            if (arg_idx + 1 < argc) {
                command = argv[++arg_idx];
                arg_idx++;
                break;
            } else {
                fprintf(stderr, "Option -c requires an argument\n");
                return 1;
            }
        } else if (strcmp(argv[arg_idx], "--sandbox") == 0) {
            config.sandbox_enabled = 1;
            arg_idx++;
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[arg_idx]);
            print_usage(argv[0]);
            return 1;
        }
    }

    if (!command && arg_idx < argc) {
        filename = argv[arg_idx];
    }

    if (Nsn_Initialize(&config) != 0) {
        fprintf(stderr, "Failed to initialize NSN interpreter\n");
        return 1;
    }

    int result = 0;
    if (command) {
        result = Nsn_EvalString(command);
    } else if (filename) {
        result = Nsn_RunFile(filename);
    } else {
        // Future: Start REPL
        printf("NSN REPL not yet implemented. Use -c or provide a script file.\n");
    }

    Nsn_Finalize();

    return result;
}
