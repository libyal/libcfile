AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@MEMWATCH_CPPFLAGS@

TESTS = \
	test_seek.sh \
	test_read.sh \
	test_write.sh

check_SCRIPTS = \
	test_seek.sh \
	test_read.sh \
	test_write.sh

input_FILES = \
	input/test.raw

EXTRA_DIST = \
	$(check_SCRIPTS) \
	$(input_FILES)

check_PROGRAMS = \
	cfile_test_read \
	cfile_test_seek \
	cfile_test_write

cfile_test_read_SOURCES = \
	cfile_test_libcerror.h \
	cfile_test_libcfile.h \
	cfile_test_libcstring.h \
	cfile_test_read.c

cfile_test_read_LDADD = \
	@LIBCSTRING_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	../libcfile/libcfile.la \
        @MEMWATCH_LIBADD@

cfile_test_seek_SOURCES = \
	cfile_test_libcerror.h \
	cfile_test_libcfile.h \
	cfile_test_libcstring.h \
	cfile_test_seek.c

cfile_test_seek_LDADD = \
	@LIBCSTRING_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	../libcfile/libcfile.la \
        @MEMWATCH_LIBADD@

cfile_test_write_SOURCES = \
	cfile_test_libcerror.h \
	cfile_test_libcfile.h \
	cfile_test_libcstring.h \
	cfile_test_write.c

cfile_test_write_LDADD = \
	@LIBCSTRING_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	../libcfile/libcfile.la \
        @MEMWATCH_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

