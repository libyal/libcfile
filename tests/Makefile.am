AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@MEMWATCH_CPPFLAGS@

TESTS = \
	test_path.sh

check_SCRIPTS = \
	test_path.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	cpath_test_path

cpath_test_path_SOURCES = \
	cpath_test_libcerror.h \
	cpath_test_libcpath.h \
	cpath_test_libcstring.h \
	cpath_test_path.c

cpath_test_path_LDADD = \
	@LIBCSTRING_LIBADD@ \
	../libcpath/libcpath.la \
        @MEMWATCH_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

