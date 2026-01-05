#!/bin/bash
# NSN (Network Security Navigator)
# Test Runner Script

set -e

echo "Running NSN Test Suite..."

# 1. Run C Unit Tests
if [ -d "build" ]; then
    echo "--- Running C Unit Tests ---"
    cd build
    ctest --output-on-failure
    cd ..
else
    echo "Warning: No build directory found. Skipping C unit tests."
fi

# 2. Run NSN Integration Tests
echo "--- Running NSN Integration Tests ---"
if [ ! -f "./nsn" ] && [ ! -f "./nsn.exe" ]; then
    echo "Error: nsn binary not found. Run ./scripts/build.sh first."
    exit 1
fi

NSN_BIN="./nsn"
[ -f "./nsn.exe" ] && NSN_BIN="./nsn.exe"

# Run sample scripts
$NSN_BIN examples/basic/01_hello_ping.nsn
$NSN_BIN examples/basic/03_dns_lookup.nsn

# Run the test standard library modules
$NSN_BIN -m test.test_net
$NSN_BIN -m test.test_utils

echo "---------------------------------------"
echo "All tests passed!"
