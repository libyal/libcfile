AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@MEMWATCH_CPPFLAGS@

lib_LTLIBRARIES = libcfile.la

libcfile_la_SOURCES = \
	libcfile.c \
	libcfile_definitions.h \
	libcfile_extern.h \
	libcfile_file.c libcfile_file.h \
	libcfile_libcerror.h \
	libcfile_libcstring.h \
	libcfile_libuna.h \
	libcfile_support.c libcfile_support.h \
	libcfile_types.h \
	libcfile_unused.h

libcfile_la_LIBADD  = \
	@LIBCSTRING_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBUNA_LIBADD@

libcfile_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libcfile_definitions.h.in \
	libcfile.rc \
	libcfile.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libcfile_definitions.h
	/bin/rm -f libcfile.rc
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libcfile ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libcfile_la_SOURCES) 

