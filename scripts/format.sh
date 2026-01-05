#!/bin/bash
# NSN Code Formatting Script
# Uses clang-format for C code

find . -name "*.c" -o -name "*.h" | xargs clang-format -i

echo "C code formatted successfully."
