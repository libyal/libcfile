AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@

TESTS = \
	test_file_seek.sh \
	test_file_read.sh \
	test_file_write.sh \
	test_stream_seek.sh \
	test_stream_read.sh \
	test_stream_write.sh

check_SCRIPTS = \
	test_file_seek.sh \
	test_file_read.sh \
	test_file_write.sh \
	test_runner.sh \
	test_stream_seek.sh \
	test_stream_read.sh \
	test_stream_write.sh

input_FILES = \
	input/set1/test.raw

EXTRA_DIST = \
	$(check_SCRIPTS) \
	$(input_FILES)

check_PROGRAMS = \
	cfile_test_file_read \
	cfile_test_file_seek \
	cfile_test_file_write \
	cfile_test_stream_read \
	cfile_test_stream_seek \
	cfile_test_stream_write

cfile_test_file_read_SOURCES = \
	cfile_test_libcerror.h \
	cfile_test_libcfile.h \
	cfile_test_libcstring.h \
	cfile_test_file_read.c \
	cfile_test_unused.h

cfile_test_file_read_LDADD = \
	../libcfile/libcfile.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

cfile_test_file_seek_SOURCES = \
	cfile_test_libcerror.h \
	cfile_test_libcfile.h \
	cfile_test_libcstring.h \
	cfile_test_file_seek.c

cfile_test_file_seek_LDADD = \
	../libcfile/libcfile.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

cfile_test_file_write_SOURCES = \
	cfile_test_libcerror.h \
	cfile_test_libcfile.h \
	cfile_test_libcstring.h \
	cfile_test_file_write.c

cfile_test_file_write_LDADD = \
	../libcfile/libcfile.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

cfile_test_stream_read_SOURCES = \
	cfile_test_libcerror.h \
	cfile_test_libcfile.h \
	cfile_test_libcstring.h \
	cfile_test_stream_read.c \
	cfile_test_unused.h

cfile_test_stream_read_LDADD = \
	../libcfile/libcfile.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

cfile_test_stream_seek_SOURCES = \
	cfile_test_libcerror.h \
	cfile_test_libcfile.h \
	cfile_test_libcstring.h \
	cfile_test_stream_seek.c

cfile_test_stream_seek_LDADD = \
	../libcfile/libcfile.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

cfile_test_stream_write_SOURCES = \
	cfile_test_libcerror.h \
	cfile_test_libcfile.h \
	cfile_test_libcstring.h \
	cfile_test_stream_write.c

cfile_test_stream_write_LDADD = \
	../libcfile/libcfile.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

