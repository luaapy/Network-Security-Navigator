from setuptools import setup, Extension
import os

# NSN (Network Security Navigator) Build Script
# This setup.py is primarily used to build the NSN core as a Python-compatible 
# C extension for those who wish to embed NSN in Python environments.

setup(
    name="nsn-lang",
    version="1.0.0",
    author="Nosan",
    description="Network Security Navigator core runtime",
    url="https://github.com/luaapy/Network-Security-Navigator",
    ext_modules=[
        Extension(
            "nsn_core",
            sources=[
                "Nsn/nsn.c", "Nsn/ceval.c", "Nsn/nsn_memory.c", 
                "Nsn/nsn_state.c", "Objects/object.c"
            ],
            include_dirs=["Include", "."],
        )
    ],
    python_requires=">=3.8",
)
