# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

from datetime import date

project = "Eudyptula"
author = "Eyal Royee"
copyright = f"{date.today().year}, {author}"

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    # sphinx-builtin extensions
    "sphinx.ext.duration",       # Measure durations of Sphinx processing.
    "sphinx.ext.todo",           # Support for todo items & todolist in sphinx.
    "sphinx.ext.viewcode",       # Add links to highlighted source code.
    "sphinx.ext.autodoc",        # Include documentation from docstrings.
    "sphinx.ext.githubpages",    # Adds .nojekyll so everythings works in gh-pages.

    # sphinx external extensions
    "myst_parser",               # To support Markdown-based documentation, Sphinx can use MyST-Parser.
    "sphinx_copybutton",         # Adds a copy button to each code block.
    "sphinx_rtd_dark_mode",      # Adds dark-mode theme to read-the-docs theme.
    "sphinxcontrib.shellcheck",  # Use shellcheck **inside** code blocks.
]

source_suffix = {
    '.rst': 'restructuredtext',
    '.md': 'markdown',
}

templates_path = ["templates"]
exclude_patterns = []

# Enables nitpicky mode if True.
# In nitpicky mode, Sphinx will warn about all references where the target cannot be found.
# This is recommended for new projects as it ensures that all references are to valid targets.
nitpicky = True

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = "sphinx_rtd_theme"
html_static_path = ["static"]


# -- Custom configuration ----------------------------------------------------
# user starts in dark mode
default_dark_mode = True
