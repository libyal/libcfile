dnl Functions for libcfile
dnl
dnl Version: 20120325

dnl Function to detect if libcfile is available
dnl ac_libcfile_dummy is used to prevent AC_CHECK_LIB adding unnecessary -l<library> arguments
AC_DEFUN([AX_LIBCFILE_CHECK_LIB],
 [dnl Check if parameters were provided
 AS_IF(
  [test "x$ac_cv_with_libcfile" != x && test "x$ac_cv_with_libcfile" != xno && test "x$ac_cv_with_libcfile" != xauto-detect],
  [AS_IF(
   [test -d "$ac_cv_with_libcfile"],
   [CFLAGS="$CFLAGS -I${ac_cv_with_libcfile}/include"
   LDFLAGS="$LDFLAGS -L${ac_cv_with_libcfile}/lib"],
   [AC_MSG_WARN([no such directory: $ac_cv_with_libcfile])
   ])
  ])

 AS_IF(
  [test "x$ac_cv_with_libcfile" != xno],
  [dnl Check for headers
  AC_CHECK_HEADERS([libcfile.h])
 
  AS_IF(
   [test "x$ac_cv_header_libcfile_h" = xno],
   [ac_cv_libcfile=no],
   [ac_cv_libcfile=yes
   AC_CHECK_LIB(
    fdatetime,
    libcfile_get_version,
    [ac_cv_libcfile_dummy=yes],
    [ac_cv_libcfile=no])
  
   dnl TODO add functions
   ])
  ])

 AS_IF(
  [test "x$ac_cv_libcfile" = xyes],
  [AC_DEFINE(
   [HAVE_LIBCFILE],
   [1],
   [Define to 1 if you have the `cfile' library (-lcfile).])
  LIBS="-lcfile $LIBS"
  ])

 AS_IF(
  [test "x$ac_cv_libcfile" = xyes],
  [AC_SUBST(
   [HAVE_LIBCFILE],
   [1]) ],
  [AC_SUBST(
   [HAVE_LIBCFILE],
   [0])
  ])
 ])

dnl Function to detect if libcfile dependencies are available
AC_DEFUN([AX_LIBCFILE_CHECK_LOCAL],
 [dnl Headers included in libcfile/libcfile_file.h
 AC_CHECK_HEADERS([errno.h fcntl.h sys/stat.h unistd.h])

 dnl File input/output functions used in libcfile/libcfile_file.h
 AC_CHECK_FUNCS([close fstat ftruncate lseek open read stat write])

 AS_IF(
  [test "x$ac_cv_func_close" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: close],
   [1])
  ])
 
 AS_IF(
  [test "x$ac_cv_func_fstat" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: fstat],
   [1])
  ])
 
 AS_IF(
  [test "x$ac_cv_func_ftruncate" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: ftruncate],
   [1])
  ])
 
 AS_IF(
  [test "x$ac_cv_func_lseek" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: lseek],
   [1])
  ])
 
 AS_IF(
  [test "x$ac_cv_func_open" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: open],
   [1])
  ])
 
 AS_IF(
  [test "x$ac_cv_func_read" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: read],
   [1])
  ])
 
 AS_IF(
  [test "x$ac_cv_func_stat" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: stat],
   [1])
  ])
 
 AS_IF(
  [test "x$ac_cv_func_write" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: write],
   [1])
  ])
 ])

