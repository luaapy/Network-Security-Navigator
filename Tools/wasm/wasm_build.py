#!/usr/bin/env python3
# NSN (Network Security Navigator)
# Copyright (c) NSN Contributors
# Licensed under MIT License
#
# File: wasm_build.py
# Description: Orchestrates the WebAssembly (Emscripten) build for NSN.

import os
import sys
import subprocess

def build_wasm():
    print("--- NSN WebAssembly Build ---")
    
    if not subprocess.run(["emcc", "--version"], capture_output=True).returncode == 0:
        print("Error: emcc (Emscripten) not found in PATH.")
        return

    root = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
    out_dir = os.path.join(root, "build_wasm")
    if not os.path.exists(out_dir):
        os.makedirs(out_dir)

    # Core source files
    srcs = [
        "Nsn/nsn.c", "Nsn/ceval.c", "Nsn/nsn_memory.c", "Nsn/nsn_state.c",
        "Objects/object.c", "Objects/dictobject.c", "Objects/intobject.c",
        "Parser/lexer.c", "Parser/parser.c"
    ]
    src_paths = [os.path.join(root, s) for s in srcs]

    # Emscripten flags
    flags = [
        "-O3",
        "-s", "WASM=1",
        "-s", "EXPORTED_FUNCTIONS=['_Nsn_Initialize', '_Nsn_EvalString', '_main']",
        "-s", "EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap']",
        "-I", os.path.join(root, "Include"),
        "-o", os.path.join(out_dir, "nsn.js")
    ]

    cmd = ["emcc"] + src_paths + flags
    print(f"Executing: {' '.join(cmd)}")
    
    res = subprocess.run(cmd)
    if res.returncode == 0:
        print(f"Successfully built NSN for WebAssembly in {out_dir}")
    else:
        print("Build failed.")

if __name__ == "__main__":
    build_wasm()
