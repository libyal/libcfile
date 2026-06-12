AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_DLL_IMPORT@

BUILT_SOURCES = package.m4

check_AUTOTESTS = \
	test_library \
	test_manpages

input_FILES = \
	input/set1/block_size_file \
	input/set1/empty_file \
	input/set1/small_file

check_PROGRAMS = \
	cfile_test_error \
	cfile_test_file \
	cfile_test_notify \
	cfile_test_support \
	cfile_test_system_string \
	cfile_test_winapi

cfile_test_error_SOURCES = \
	cfile_test_error.c \
	cfile_test_libcfile.h \
	cfile_test_macros.h \
	cfile_test_unused.h

cfile_test_error_LDADD = \
	../libcfile/libcfile.la

cfile_test_file_SOURCES = \
	cfile_test_file.c \
	cfile_test_functions.c cfile_test_functions.h \
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
	cfile_test_libcerror.h \
	cfile_test_libcfile.h \
	cfile_test_macros.h \
	cfile_test_notify.c \
	cfile_test_unused.h

cfile_test_notify_LDADD = \
	../libcfile/libcfile.la \
	@LIBCERROR_LIBADD@

cfile_test_support_SOURCES = \
	cfile_test_functions.c cfile_test_functions.h \
	cfile_test_libcerror.h \
	cfile_test_libcfile.h \
	cfile_test_macros.h \
	cfile_test_support.c \
	cfile_test_unused.h

cfile_test_support_LDADD = \
	@LIBUNA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libcfile/libcfile.la \
	@LIBCERROR_LIBADD@

cfile_test_system_string_SOURCES = \
	cfile_test_libcerror.h \
	cfile_test_libcfile.h \
	cfile_test_macros.h \
	cfile_test_system_string.c \
	cfile_test_unused.h

cfile_test_system_string_LDADD = \
	../libcfile/libcfile.la \
	@LIBCERROR_LIBADD@

cfile_test_winapi_SOURCES = \
	cfile_test_libcfile.h \
	cfile_test_macros.h \
	cfile_test_unused.h \
	cfile_test_winapi.c

cfile_test_winapi_LDADD = \
	../libcfile/libcfile.la

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

SUFFIXES = .at

.at:
	$(AM_V_GEN)rm -f $@ $@.tmp; \
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $< && \
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

check-build: $(check_PROGRAMS)

check-local: $(check_AUTOTESTS)
	@fail=0; \
	for test_suite in $(check_AUTOTESTS); do \
		$(AM_TESTS_ENVIRONMENT) $(SHELL) "./$$test_suite" $(TESTSUITEFLAGS) || fail=1; \
		echo ""; \
	done; \
	exit $$fail

clean-local:
	for test_suite in $(check_AUTOTESTS); do \
		test ! -f "$$test_suite" || $(SHELL) "./$$test_suite" --clean; \
	done

package.m4: $(top_srcdir)/configure.ac
	$(AM_V_GEN):; \
	{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [$(PACKAGE_NAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [$(PACKAGE_TARNAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [$(PACKAGE_VERSION)])' ; \
	  echo 'm4_define([AT_PACKAGE_STRING], [$(PACKAGE_STRING)])' ; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [$(PACKAGE_BUGREPORT)])' ; \
	} > $@

test_inputs_libcfile.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) libcfile

test_library: package.m4 test_inputs_libcfile.at test_library.at test_macros.at

test_manpages: package.m4 test_manpages.at

EXTRA_DIST = \
	$(check_AUTOTESTS:=.at) \
	$(input_FILES) \
	generate_test_inputs.sh \
	package.m4 \
	test_macros.at

CLEANFILES = \
	$(check_AUTOTESTS) \
	*.exe \
	*.tmp \
	notify_stream.log \
	test_inputs_*.at \
	TestFile

DISTCLEANFILES = \
	*.log \
	atconfig \
	Makefile \
	Makefile.in

