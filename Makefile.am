
SUBDIRS = src test

EXTRA_DIST = bootstrap

$(distdir).tar.gz:
	make dist

pkg: $(distdir).tar.gz $(PACKAGE).spec
	$(PACKAGER) 
