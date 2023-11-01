include_HEADERS = \
	libcfile.h

pkginclude_HEADERS = \
	libcfile/codepage.h \
	libcfile/definitions.h \
	libcfile/error.h \
	libcfile/extern.h \
	libcfile/features.h \
	libcfile/types.h

EXTRA_DIST = \
	libcfile.h.in \
	libcfile/definitions.h.in \
	libcfile/features.h.in \
	libcfile/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libcfile.h
	-rm -f libcfile/definitions.h
	-rm -f libcfile/features.h
	-rm -f libcfile/types.h
	-rm -f Makefile

