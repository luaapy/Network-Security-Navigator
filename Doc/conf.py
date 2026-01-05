# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

import os
import sys
sys.path.insert(0, os.path.abspath('..'))  # Add project root to sys.path

# -- Project information -----------------------------------------------------

project = 'NSN (Network Security Navigator)'
author = 'NSN Contributors'
copyright = '2026, NSN Contributors'
# The short X.Y version
version = '0.3.0'
# The full version, including alpha/beta/rc tags
release = version

# -- General configuration ---------------------------------------------------

extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.napoleon',
    'sphinx.ext.autosectionlabel',
    'sphinx.ext.todo',
    'sphinx.ext.viewcode',
]

todo_include_todos = True

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

# -- Options for HTML output -------------------------------------------------

html_theme = 'alabaster'
html_static_path = ['_static']

# Custom CSS for a premium look (optional)
html_css_files = ['css/custom.css']

# -- Extension configuration -------------------------------------------------

napoleon_google_docstring = True
napoleon_numpy_docstring = True
