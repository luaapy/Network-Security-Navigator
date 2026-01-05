# Makefile for building NSN documentation with Sphinx

SPHINXBUILD   = sphinx-build
SOURCEDIR    = Doc
BUILDDIR     = _build

.PHONY: html clean

html:
	$(SPHINXBUILD) -b html $(SOURCEDIR) $(BUILDDIR)/html
	@echo "Documentation built successfully in $(BUILDDIR)/html"

clean:
	@rm -rf $(BUILDDIR)/*
	@echo "Cleaned build directory"
