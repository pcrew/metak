
SHELL := bash

PACKAGE = metak
VERSION = 1.0

export PACKAGE VERSION

TOPDIR = $(shell /bin/pwd)
INCDIR = $(TOPDIR)/include

CC = $(CROSS_COMPILE)g++
STRIP = $(CROSS_COMPILE) strip
CPPFLAGS = -Wall -std=gnu++17 -I$(INCDIR) -O3

export CC STRIP CPPFLAGS TOPDIR INCDIR

archive:
	@echo -n "Archiving source code... "
	@rm -rf $(PACKAGE)-$(VERSION) || exit 1
	@mkdir $(PACKAGE)-$(VERSION) || exit 1
	@cp -r $(INCDIR) $(PACKAGE)-$(VERSION)/ || exit 1
	@tar zcvf $(PACKAGE)-$(VERSION).tar $(PACKAGE)-$(VERSION) 1> /dev/null || exit 1
	@rm -rf $(PACKAGE)-$(VERSION) || exit 1
	@echo "done"


rpm: archive
	@echo -n "Making RPM package for ${PACKAGE} version ${VERSION}... "
	@$(MAKE) -C builds &> /dev/null || exit 1
	@echo "done"

example:
	$(MAKE) -C examples

clean:
	@$(MAKE) clean -C builds
	@$(MAKE) clean -C examples

cleanall: clean
	@rm -vf `find . -name *.o`
	@rm -vf `find . -name *.sw`
