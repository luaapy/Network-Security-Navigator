# NSN (Network Security Navigator)
# Copyright (c) NSN Contributors
# Licensed under MIT License
#
# File: buildmsi.py
# Description: Automated MSI (Windows Installer) builder for NSN.

import os
import sys
import uuid
import msilib
from msilib import schema, sequence

# NSN Versioning
NSN_VERSION = "1.0.0"
PRODUCT_NAME = "Network Security Navigator"
UPGRADE_CODE = "{47265842-8322-4fcb-b826-0ec997F766AD}" # Static for NSN 1.x

class MSIBuilder:
    def __init__(self, msi_path):
        self.msi_path = msi_path
        self.db = msilib.init_database(msi_path, schema, PRODUCT_NAME, 
                                      msilib.gen_uuid(), NSN_VERSION, "Nosan")
        self.create_tables()
        self.populate_standard_tables()

    def create_tables(self):
        # Create standard MSI tables
        msilib.add_data(self.db, "Property", [("UpgradeCode", UPGRADE_CODE)])
        msilib.add_data(self.db, "Property", [("ProductName", PRODUCT_NAME)])
        msilib.add_data(self.db, "Property", [("ProductVersion", NSN_VERSION)])
        msilib.add_data(self.db, "Property", [("Manufacturer", "Nosan")])

    def populate_standard_tables(self):
        # Add InstallExecuteSequence
        for action, cond, seq in sequence.InstallExecuteSequence:
            msilib.add_data(self.db, "InstallExecuteSequence", [(action, cond, seq)])
        
        # Add InstallUISequence
        for action, cond, seq in sequence.InstallUISequence:
            msilib.add_data(self.db, "InstallUISequence", [(action, cond, seq)])

    def add_files(self, source_dir):
        # 1. Main Binary
        cab = msilib.CAB("NSNFiles")
        feature = msilib.Feature(self.db, "NSNCore", "Core Engine", "Main NSN Interp", 1)
        root_dir = msilib.Directory(self.db, cab, None, source_dir, "TARGETDIR", "SourceDir")
        
        # Add nsn.exe
        exe_path = os.path.join(source_dir, "nsn.exe")
        if os.path.exists(exe_path):
            root_dir.start_component("NSNExe", feature, key_file="nsn.exe")
            root_dir.add_file("nsn.exe")
            print(f"Adding {exe_path} to MSI...")

        # 2. Standard Library (Lib/)
        lib_dir = os.path.join(source_dir, "Lib")
        if os.path.exists(lib_dir):
            nsn_lib = msilib.Directory(self.db, cab, root_dir, lib_dir, "Lib", "NSNLib")
            for root, dirs, files in os.walk(lib_dir):
                for f in files:
                    full_p = os.path.join(root, f)
                    # Simplified: add all .nsn files
                    if f.endswith(".nsn"):
                        nsn_lib.start_component(f.replace(".", "_"), feature)
                        nsn_lib.add_file(f)

        self.db.Commit()

    def finalize(self):
        print(f"MSI build complete: {self.msi_path}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python buildmsi.py <dist_dir>")
        sys.exit(1)

    dist = sys.argv[1]
    msi_name = f"nsn-{NSN_VERSION}-x64.msi"
    
    builder = MSIBuilder(msi_name)
    builder.add_files(dist)
    builder.finalize()
