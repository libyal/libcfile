AC_PREREQ( 2.59 )

AC_INIT(
 [libcfile],
 [20120903],
 [joachim.metz@gmail.com])

AC_CONFIG_SRCDIR(
 [include/libcfile.h.in])

AM_INIT_AUTOMAKE([gnu 1.6])

AC_CONFIG_MACRO_DIR([m4])

dnl Check for host type
AC_CANONICAL_HOST

dnl Check for large file support
AC_SYS_LARGEFILE

dnl Check for libtool DLL support
AC_LIBTOOL_WIN32_DLL

dnl Checks for programs
AC_PROG_CC
AC_PROG_GCC_TRADITIONAL
AC_PROG_MAKE_SET
AC_PROG_INSTALL

dnl Check for libtool
AC_PROG_LIBTOOL
AC_SUBST(LIBTOOL_DEPS)

dnl Check for pkg-config
AC_PATH_PROG(PKGCONFIG,[pkg-config])

dnl Support of internationalization (i18n)
AM_GNU_GETTEXT([external])

dnl Check for compiler language support
AC_C_CONST
AC_C_INLINE
AC_C_VOLATILE

dnl Check if WINAPI support should be enabled
AX_COMMON_CHECK_ENABLE_WINAPI

dnl Check if wide character type should be enabled
AX_COMMON_CHECK_ENABLE_WIDE_CHARACTER_TYPE

dnl Check for type definitions
AX_TYPES_CHECK_LOCAL

dnl Checks for libraries and library functions
AX_COMMON_CHECK_LOCAL

dnl Check for enabling libcstring for cross-platform C string functions
AX_LIBCSTRING_CHECK_ENABLE

dnl Check for enabling libcerror for cross-platform C error functions
AX_LIBCERROR_CHECK_ENABLE

dnl Check for enabling libclocale for cross-platform C locale functions
AX_LIBCLOCALE_CHECK_ENABLE

dnl Check for enabling libuna for Unicode string support
AX_LIBUNA_CHECK_ENABLE

dnl Check for library function support
AX_LIBCFILE_CHECK_LOCAL

dnl Set additional compiler flags
CFLAGS="$CFLAGS -Wall";

dnl Set memwatch support
ac_cv_enable_memwatch=no

AS_IF(
 [test "x$ac_cv_enable_memwatch" != xno ],
 [AC_SUBST(
  [MEMWATCH_CPPFLAGS],
  ["-DMEMWATCH -DMEMWATCH_STDIO"])
 AC_SUBST(
  [MEMWATCH_LIBADD],
  [../common/libmemwatch.la]) ])

AM_CONDITIONAL(
 [HAVE_MEMWATCH],
 [test "x$ac_cv_enable_memwatch" != xno])

dnl Check if requires and build requires should be set in spec file
AS_IF(
 [test "x$ac_cv_libcstring" = xyes || test "x$ac_cv_libcerror" = xyes || test "x$ac_cv_libclocale" = xyes || test "x$ac_cv_libuna" = xyes],
 [AC_SUBST(
  [libcfile_spec_requires],
  [Requires:])
 AC_SUBST(
  [libcfile_spec_build_requires],
  [BuildRequires:])
 ])

dnl Set the date for dpkg files
AC_SUBST(
 [DATE],
 [`date -R 2> /dev/null`])

dnl Have configure make the Makefiles
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([include/Makefile])
AC_CONFIG_FILES([common/Makefile])
AC_CONFIG_FILES([libcstring/Makefile])
AC_CONFIG_FILES([libcerror/Makefile])
AC_CONFIG_FILES([libclocale/Makefile])
AC_CONFIG_FILES([libuna/Makefile])
AC_CONFIG_FILES([libcfile/Makefile])
AC_CONFIG_FILES([po/Makefile.in])
AC_CONFIG_FILES([po/Makevars])
AC_CONFIG_FILES([manuals/Makefile])
AC_CONFIG_FILES([tests/Makefile])
dnl Have configure make the include files
AC_CONFIG_FILES([include/libcfile.h])
AC_CONFIG_FILES([include/libcfile/definitions.h])
AC_CONFIG_FILES([include/libcfile/features.h])
AC_CONFIG_FILES([include/libcfile/types.h])
AC_CONFIG_FILES([libcfile/libcfile_definitions.h])
dnl Have configure make distribution specific files
AC_CONFIG_FILES([common/types.h])
AC_CONFIG_FILES([dpkg/changelog])
AC_CONFIG_FILES([dpkg/copyright])
AC_CONFIG_FILES([libcfile/libcfile.rc])
AC_CONFIG_FILES([libcfile.pc])
AC_CONFIG_FILES([libcfile.spec])
dnl Have configure write its configuration
AC_CONFIG_HEADERS([common/config.h])

AC_OUTPUT

dnl Print a summary
AC_MSG_NOTICE([
Building:
   libcstring support:          $ac_cv_libcstring
   libcerror support:           $ac_cv_libcerror
   libclocale support:          $ac_cv_libclocale
   libuna support:              $ac_cv_libuna

Features:
   Wide character type support: $ac_cv_enable_wide_character_type
]);

