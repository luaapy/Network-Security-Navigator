#!/usr/bin/env python3
# Script to generate Include/core/opcode.h from a definition file

import sys

def generate():
    opcodes = {
        "OP_NOP": 0,
        "OP_LOAD_CONST": 1,
        "OP_LOAD_NAME": 2,
        "OP_STORE_NAME": 3,
        "OP_BINARY_ADD": 10,
        "OP_JUMP_FORWARD": 20,
        "OP_CALL_FUNCTION": 50,
        "OP_RETURN_VALUE": 60,
        "OP_SCAN_HOST": 90,
        "OP_PING_HOST": 91
    }
    
    with open("Include/core/opcode.h", "w") as f:
        f.write("/* Auto-generated opcode definitions */\n")
        f.write("#ifndef NSN_OPCODE_H\n")
        f.write("#define NSN_OPCODE_H\n\n")
        for name, val in opcodes.items():
            f.write(f"#define {name} {val}\n")
        f.write("\n#endif\n")

if __name__ == "__main__":
    generate()
    print("Generated Include/core/opcode.h")
