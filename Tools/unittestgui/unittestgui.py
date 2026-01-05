#!/usr/bin/env python3
# NSN (Network Security Navigator)
# Copyright (c) NSN Contributors
# Licensed under MIT License
#
# File: unittestgui.py
# Description: Simple Tkinter GUI for running NSN tests.

import os
import sys
import tkinter as tk
from tkinter import messagebox, scrolledtext
import subprocess

class TestGui:
    def __init__(self, root):
        self.root = root
        self.root.title("NSN Test Runner")
        self.root.geometry("600x400")

        self.label = tk.Label(root, text="NSN Integration & Unit Tests", font=("Arial", 14))
        self.label.pack(pady=10)

        self.run_btn = tk.Button(root, text="Run All Tests", command=self.run_tests, bg="green", fg="white")
        self.run_btn.pack(pady=5)

        self.output = scrolledtext.ScrolledText(root, width=70, height=15)
        self.output.pack(padx=10, pady=10)

    def run_tests(self):
        self.output.delete(1.0, tk.END)
        self.output.insert(tk.END, "Starting tests...\n")
        
        # Path to CI script
        ci_script = os.path.join(os.path.dirname(__file__), "..", "buildbot", "test.py")
        
        try:
            res = subprocess.run([sys.executable, ci_script], capture_output=True, text=True)
            self.output.insert(tk.END, res.stdout)
            if res.stderr:
                self.output.insert(tk.END, "\nERRORS:\n" + res.stderr)
        except Exception as e:
            messagebox.showerror("Error", str(e))

if __name__ == "__main__":
    app = tk.Tk()
    gui = TestGui(app)
    app.mainloop()
