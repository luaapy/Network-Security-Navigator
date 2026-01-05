#!/bin/bash
# NSN Linting Script
# Uses clang-tidy for C code

echo "Running clang-tidy..."
find Nsn Objects Parser Modules -name "*.c" | xargs clang-tidy -p . --config-file=.clang-tidy

echo "Linting complete."
