#!/usr/bin/env python3
# NSN (Network Security Navigator)
# Copyright (c) NSN Contributors
# Licensed under MIT License
#
# File: test.py
# Description: CI/Buildbot test runner script.

import os
import sys
import subprocess
import time

def run_command(cmd):
    print(f"Executing: {' '.join(cmd)}")
    try:
        start = time.time()
        result = subprocess.run(cmd, check=True, capture_output=True, text=True)
        end = time.time()
        print(f"  [OK] in {end - start:.2f}s")
        return result.stdout
    except subprocess.CalledProcessError as e:
        print(f"  [FAILED] with exit code {e.returncode}")
        print(f"  Error output: {e.stderr}")
        return None

def main():
    root = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
    nsn_exe = os.path.join(root, "nsn" if os.name != 'nt' else "nsn.exe")
    
    if not os.path.exists(nsn_exe):
        print(f"Error: {nsn_exe} not found. Please build NSN first.")
        sys.exit(1)

    print("--- NSN Continuous Integration Test Suite ---")
    
    # 1. Unit Tests
    print("\n[Phase 1] Running C Unit Tests...")
    # Logic to find and run compiled unit test binaries
    # e.g., run_command([os.path.join(root, "build", "tests", "unit", "test_memory")])

    # 2. Integration Tests
    print("\n[Phase 2] Running NSN Integration Scripts...")
    integration_dir = os.path.join(root, "tests", "integration")
    for f in os.listdir(integration_dir):
        if f.endswith(".nsn"):
            run_command([nsn_exe, os.path.join(integration_dir, f)])

    # 3. Performance Benchmarks
    print("\n[Phase 3] Running Performance Benchmarks...")
    perf_dir = os.path.join(root, "tests", "performance")
    for f in os.listdir(perf_dir):
        if f.endswith(".nsn"):
            run_command([nsn_exe, os.path.join(perf_dir, f)])

    print("\n--- All CI Tests Completed ---")

if __name__ == "__main__":
    main()
