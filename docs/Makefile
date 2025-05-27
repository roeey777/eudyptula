# Minimal makefile for Sphinx documentation
#

# You can set these variables from the command line, and also
# from the environment for the first two.
SPHINXOPTS          ?=
SPHINXBUILD         ?= sphinx-build
SOURCEDIR           := source
BUILDDIR            := build
WORKTREE_DIR        := $(BUILDDIR)/html
GITHUB_PAGES_BRANCH := gh-pages

# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

.PHONY: help Makefile

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
%: Makefile
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)


.PHONY: clean
clean:
	-@$(SPHINXBUILD) -M clean "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O);
	-touch "$(BUILDDIR)"/.gitkeep
	# sphinx-build -M clean also removes the .git **file** which makes the
	# git worktree "orphan", so now fix this by re-adding the worktree.
	-git worktree remove $(WORKTREE_DIR)
	git worktree add $(WORKTREE_DIR) $(GITHUB_PAGES_BRANCH)
