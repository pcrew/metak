.PHONY: clean cleanall

all:
	@rm -rf SOURCES && mkdir SOURCES
	@mv $(TOPDIR)/$(PACKAGE)-$(VERSION).tar SOURCES
	@rpmbuild --quiet \
		-D "_topdir `pwd`" \
		-D "version ${VERSION}" \
		-D "package ${PACKAGE}" \
	       	-D "debug_package %{nil}" \
	       	-bb SPECS/${PACKAGE}.spec
clean:
	@rm -rf RPMS
	@rm -rf BUILD
	@rm -rf SRPMS
	@rm -rf SOURCES
	@rm -rf BUILDROOT

cleanall: clean
