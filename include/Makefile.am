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
	/bin/rm -f libcfile.h
	/bin/rm -f libcfile/definitions.h
	/bin/rm -f libcfile/features.h
	/bin/rm -f libcfile/types.h
	/bin/rm -f Makefile

