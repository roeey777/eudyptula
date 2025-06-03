DOCS_SOURCE_DIR     := docs/source
DOCS_BUILD_DIR      := docs/build/html
DEFAULT_BRANCH      := master
GITHUB_PAGES_BRANCH := gh-pages
COMMIT_ID           := $(shell git rev-parse $(DEFAULT_BRANCH))
COMMIT_MSG          := $(addprefix Documentation for commit ,$(COMMIT_ID))
VIRTUAL_ENVIRONMENT := .venv

# override the default shell (/bin/bash) so source would be possible.
SHELL := /bin/bash

.PHONY: all
all:
	@if [ ! -f buildroot/.config ]; then \
		source activate.sh && make -C buildroot/ eudyptula_qemu_x86_64_defconfig; \
	fi
	source activate.sh && make -C buildroot all

.PHONY: defconfig
defconfig:
	source activate.sh && make -C buildroot/ eudyptula_qemu_x86_64_defconfig

.PHONY: savedefconfig
savedefconfig:
	source activate.sh && make -C buildroot savedefconfig

.PHONY: clean-build
clean-build:
	make -C buildroot clean

$(VIRTUAL_ENVIRONMENT):
	virtualenv $(VIRTUAL_ENVIRONMENT)
	source $(VIRTUAL_ENVIRONMENT)/bin/activate && pip install -r docs/requirements.txt

.PHONY: docs
docs: $(VIRTUAL_ENVIRONMENT)
	source $(VIRTUAL_ENVIRONMENT)/bin/activate && make -C docs/ html

.PHONY: publish-docs
publish-docs: docs
	cd $(DOCS_BUILD_DIR) && git add -A . && git commit --allow-empty -sm "$(COMMIT_MSG)." && git push origin $(GITHUB_PAGES_BRANCH)

.PHONY: clean-docs
clean-docs: $(VIRTUAL_ENVIRONMENT)
	source $(VIRTUAL_ENVIRONMENT)/bin/activate && make -C docs/ clean

.PHONY: clean
clean: clean-build clean-docs
	true

