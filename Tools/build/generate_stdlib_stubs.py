#!/usr/bin/env python3
"""
NSN (Network Security Navigator)
Copyright (c) NSN Contributors
Licensed under MIT License

File: generate_stdlib_stubs.py
Description: Scans C extension modules and generates NSN-level stub files 
             for IDE support and static analysis.
"""

import os
import re
import sys

# Regex to find module initialization and function definitions
RE_INIT_FUNC = re.compile(r'void _nsn_init_(\w+)\(void\)')
RE_NSN_METH = re.compile(r'nsn_object\s+\*(\w+)\(nsn_object\s*\*self,\s*nsn_object\s*\*args\)')

def generate_stubs(modules_dir, output_dir):
    print(f"Scanning modules in {modules_dir}...")
    
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    for root, dirs, files in os.walk(modules_dir):
        for file in files:
            if file.endswith('.c'):
                path = os.path.join(root, file)
                with open(path, 'r', encoding='utf-8') as f:
                    content = f.read()
                
                # Identify module name
                init_match = RE_INIT_FUNC.search(content)
                if not init_match:
                    continue
                
                module_name = init_match.group(1)
                stub_file = os.path.join(output_dir, f"{module_name}.nsn")
                
                # Identify functions
                functions = RE_NSN_METH.findall(content)
                
                if not functions:
                    # Check for simple methods list if regex fails
                    # Roughly looking for static nsn_method entries
                    functions = re.findall(r'\{\s*"(\w+)"\s*,\s*\w+\s*\}', content)

                if functions:
                    print(f"  - Generating stub for module: {module_name} ({len(functions)} funcs)")
                    with open(stub_file, 'w', encoding='utf-8') as out:
                        out.write(f"# NSN Stub for C-module: {module_name}\n")
                        out.write(f"# Generated automatically by generate_stdlib_stubs.py\n\n")
                        
                        unique_funcs = sorted(list(set(functions)))
                        for func in unique_funcs:
                            # Strip common prefixes like 'msvcrt_' or 'winreg_' for the stub
                            clean_name = func
                            if func.startswith(module_name + "_"):
                                clean_name = func[len(module_name)+1:]
                            
                            out.write(f"func {clean_name}(*args) {{\n    # C-extension implementation\n    return null;\n}}\n\n")

if __name__ == "__main__":
    # Base paths relative to the project root
    ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
    MOD_DIR = os.path.join(ROOT, "Modules")
    OUT_DIR = os.path.join(ROOT, "Lib", "stubs")
    
    generate_stubs(MOD_DIR, OUT_DIR)
    print("Stub generation complete.")
