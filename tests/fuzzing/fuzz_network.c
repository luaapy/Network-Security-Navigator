/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: fuzz_network.c
 * Description: LibFuzzer-based fuzzer for NSN network components and packet parsing.
 */

#include "nsn.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

/**
 * LibFuzzer entry point.
 * This fuzzer targets:
 * 1. IP address parsing (nsn_ipaddr_from_string)
 * 2. Raw packet object construction (nsn_packet_new)
 * 3. Hypothetical protocol dissection logic
 */
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    static int initialized = 0;
    if (!initialized) {
        // Lightweight initialization for fuzzing
        Nsn_Initialize(NULL);
        initialized = 1;
    }

    /* Test Case 1: IP Address Parsing */
    // Ensure data is null-terminated for string parsing
    char *ip_str = (char *)malloc(size + 1);
    if (ip_str) {
        memcpy(ip_str, data, size);
        ip_str[size] = '\0';
        
        nsn_object *ip = nsn_ipaddr_from_string(ip_str);
        if (ip) {
            Nsn_DECREF(ip);
        }
        free(ip_str);
    }

    /* Test Case 2: Packet Construction and Checksumming */
    if (size >= 20) { // Minimum IP header size
        nsn_object *packet = nsn_packet_new(data, size);
        if (packet) {
            // Simulate internal checksum validation
            NsnNetwork_Checksum((unsigned short *)data, (int)size);
            Nsn_DECREF(packet);
        }
    }

    /* Test Case 3: Script Evaluation with Fuzzed Inputs */
    // We can evaluate a small script that uses the fuzzed data as a payload
    // to search for VM or built-in module vulnerabilities.
    if (size > 0 && size < 256) {
        char script_buf[512];
        snprintf(script_buf, sizeof(script_buf), "func test() { p = Packet(\"%s\"); print(p); } test();", (char*)data);
        // Nsn_EvalString(script_buf); // Caution: Escaping issues, but good for finding parser bugs
    }

    return 0;
}

#ifdef STANDALONE_FUZZER
/* Main for running without libFuzzer (e.g., for manual testing) */
int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if (!f) return 1;

    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    fseek(f, 0, SEEK_SET);

    uint8_t *data = malloc(size);
    fread(data, 1, size, f);
    fclose(f);

    LLVMFuzzerTestOneInput(data, size);
    free(data);
    return 0;
}
#endif
