AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_DLL_IMPORT@

TESTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_write_functions.sh

check_SCRIPTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_runner.sh \
	test_write_functions.sh

input_FILES = \
	input/set1/test.raw

EXTRA_DIST = \
	$(check_SCRIPTS) \
	$(input_FILES)

check_PROGRAMS = \
	cfile_test_error \
	cfile_test_file \
	cfile_test_notify \
	cfile_test_support \
	cfile_test_write

cfile_test_error_SOURCES = \
	cfile_test_error.c \
	cfile_test_libcfile.h \
	cfile_test_macros.h \
	cfile_test_unused.h

cfile_test_error_LDADD = \
	../libcfile/libcfile.la

cfile_test_file_SOURCES = \
	cfile_test_file.c \
	cfile_test_getopt.c cfile_test_getopt.h \
	cfile_test_libcerror.h \
	cfile_test_libcfile.h \
	cfile_test_libclocale.h \
	cfile_test_libcnotify.h \
	cfile_test_libuna.h \
	cfile_test_macros.h \
	cfile_test_memory.c cfile_test_memory.h

cfile_test_file_LDADD = \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libcfile/libcfile.la \
	@LIBCERROR_LIBADD@

cfile_test_notify_SOURCES = \
	cfile_test_libcfile.h \
	cfile_test_macros.h \
	cfile_test_notify.c \
	cfile_test_unused.h

cfile_test_notify_LDADD = \
	../libcfile/libcfile.la

cfile_test_support_SOURCES = \
	cfile_test_libcerror.h \
	cfile_test_libcfile.h \
	cfile_test_macros.h \
	cfile_test_support.c \
	cfile_test_unused.h

cfile_test_support_LDADD = \
	../libcfile/libcfile.la \
	@LIBCERROR_LIBADD@

cfile_test_write_SOURCES = \
	cfile_test_libcerror.h \
	cfile_test_libcfile.h \
	cfile_test_write.c

cfile_test_write_LDADD = \
	../libcfile/libcfile.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

