#!/usr/bin/env python3
# Script to generate a C header containing all standard library module names

import os

def generate():
    lib_path = "Lib"
    modules = []
    
    for root, dirs, files in os.walk(lib_path):
        for file in files:
            if file.endswith(".nsn") and not file.startswith("__"):
                rel_path = os.path.relpath(os.path.join(root, file), lib_path)
                mod_name = rel_path.replace(os.sep, ".").replace(".nsn", "")
                modules.append(mod_name)
    
    with open("Nsn/stdlib_modules.h", "w") as f:
        f.write("/* Auto-generated list of stdlib modules */\n")
        f.write("static const char* stdlib_modules[] = {\n")
        for mod in sorted(modules):
            f.write(f'    "{mod}",\n')
        f.write("    NULL\n};\n")

if __name__ == "__main__":
    generate()
    print("Generated Nsn/stdlib_modules.h")
