DOCS_SOURCE_DIR := docs/source
DOCS_BUILD_DIR := docs/build/html
GITHUB_PAGES_BRANCH := gh-pages
COMMIT_ID := $(shell git rev-parse $(GITHUB_PAGES_BRANCH))
COMMIT_MSG := $(addprefix Documentation for commit ,$(COMMIT_ID))

.PHONY: all
all:
	source activate.sh
	make -C buildroot/ eudyptula_qemu_x86_64_defconfig
	make -C buildroot all

.PHONY: clean-build
clean-build:
	make -C buildroot clean

.PHONY: docs
docs:
	sphinx-build $(DOCS_SOURCE_DIR) $(DOCS_BUILD_DIR)

.PHONY: publish-docs
publish-docs: docs
	cd $(DOCS_BUILD_DIR) && git add -A . && git commit -sm "$(COMMIT_MSG)." && git push origin gh-pages

.PHONY: clean-docs
clean-docs:
	make -C docs/ clean

.PHONY: clean
clean: clean-build clean-docs
	true

