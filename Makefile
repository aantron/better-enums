prefix = /usr
includedir = $(prefix)/include
libdir = $(prefix)/lib/$(shell dpkg-architecture | grep DEB_TARGET_MULTIARCH | awk -F= '{print $$2}')

build:

install: enum.h better-enums.pc
	install -D -m 444 enum.h $(DESTDIR)$(includedir)/better-enums/enum.h
	install -D -m 644 better-enums.pc $(DESTDIR)$(libdir)/pkgconfig/better-enums.pc
	dpkg-parsechangelog | grep '^Version: ' >> $(DESTDIR)$(libdir)/pkgconfig/better-enums.pc

clean:
	rm -rf $(DESTDIR)

deb:
	dpkg-buildpackage -us -uc -b

.PHONY: build install clean deb

# vi: ts=8:sw=8:noai:noexpandtab:filetype=make
