AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_DLL_EXPORT@

lib_LTLIBRARIES = libcfile.la

libcfile_la_SOURCES = \
	libcfile.c \
	libcfile_definitions.h \
	libcfile_error.c libcfile_error.h \
	libcfile_extern.h \
	libcfile_file.c libcfile_file.h \
	libcfile_libcerror.h \
	libcfile_libclocale.h \
	libcfile_libcnotify.h \
	libcfile_libuna.h \
	libcfile_notify.c libcfile_notify.h \
	libcfile_support.c libcfile_support.h \
	libcfile_system_string.c libcfile_system_string.h \
	libcfile_types.h \
	libcfile_unused.h \
	libcfile_winapi.c libcfile_winapi.h

libcfile_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBUNA_LIBADD@

libcfile_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libcfile_definitions.h.in \
	libcfile.rc \
	libcfile.rc.in

DISTCLEANFILES = \
	libcfile_definitions.h \
	libcfile.rc \
	Makefile \
	Makefile.in

sources-local: $(BUILT_SOURCES)

splint-local:
	@echo "Running splint on libcfile ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libcfile_la_SOURCES)

