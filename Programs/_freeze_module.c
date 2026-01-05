/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: _freeze_module.c
 * Description: Tool to freeze NSN modules into C arrays.
 */

#include "nsn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "Usage: _freeze_module <name> <input.nsn> <output.h>\n");
        return 1;
    }

    const char *module_name = argv[1];
    const char *input_path = argv[2];
    const char *output_path = argv[3];

    FILE *in = fopen(input_path, "rb");
    if (!in) {
        perror("Failed to open input file");
        return 1;
    }

    fseek(in, 0, SEEK_END);
    long size = ftell(in);
    fseek(in, 0, SEEK_SET);

    unsigned char *buffer = malloc(size);
    fread(buffer, 1, size, in);
    fclose(in);

    // In a real freeze tool, we would compile to bytecode here.
    // For this implementation, we freeze the raw source for simplicity
    // but the structure supports pre-compiled bytecode.

    FILE *out = fopen(output_path, "w");
    if (!out) {
        perror("Failed to open output file");
        free(buffer);
        return 1;
    }

    fprintf(out, "/* Frozen module: %s */\n", module_name);
    fprintf(out, "static const unsigned char _nsn_frozen_%s[] = {\n", module_name);
    
    for (long i = 0; i < size; i++) {
        fprintf(out, "0x%02x%s", buffer[i], (i == size - 1) ? "" : ", ");
        if ((i + 1) % 12 == 0) fprintf(out, "\n    ");
    }

    fprintf(out, "\n};\n\n");
    fprintf(out, "const struct _nsn_frozen _nsn_frozen_data_%s = {\n", module_name);
    fprintf(out, "    \"%s\",\n", module_name);
    fprintf(out, "    _nsn_frozen_%s,\n", module_name);
    fprintf(out, "    %ld\n", size);
    fprintf(out, "};\n");

    fclose(out);
    free(buffer);

    printf("Successfully froze module %s to %s\n", module_name, output_path);
    return 0;
}
