#!/usr/bin/env python3
# NSN Grammar Tester
# Validates the PEG grammar against sample NSN scripts

import sys

def test_syntax(file):
    print(f"Testing grammar against {file}...")
    # Logic to load pegen and validate
    pass

if __name__ == "__main__":
    if len(sys.argv) > 1:
        test_syntax(sys.argv[1])
    else:
        print("Usage: test_grammar.py <script.nsn>")
