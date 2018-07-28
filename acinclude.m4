dnl Checks for required headers and functions
dnl
dnl Version: 20180407

dnl Function to detect if posix_fadvise is available
AC_DEFUN([AX_LIBCFILE_CHECK_FUNC_POSIX_FADVISE],
  [AC_CHECK_FUNCS([posix_fadvise])

  AS_IF(
    [test "x$ac_cv_func_posix_fadvise" = xyes],
    [AC_MSG_CHECKING(
        [whether posix_fadvise can be linked])

      SAVE_CFLAGS="$CFLAGS"
      CFLAGS="$CFLAGS -Wall -Werror"
      AC_LANG_PUSH(C)

      AC_LINK_IFELSE(
        [AC_LANG_PROGRAM(
          [[#include <fcntl.h>]],
          [[#if !defined( POSIX_FADV_SEQUENTIAL )
#define POSIX_FADV_SEQUENTIAL 2
#endif
posix_fadvise( 0, 0, 0, POSIX_FADV_SEQUENTIAL )]] )],
          [ac_cv_func_posix_fadvise=yes],
          [ac_cv_func_posix_fadvise=no])

      AC_LANG_POP(C)
      CFLAGS="$SAVE_CFLAGS"

      AS_IF(
        [test "x$ac_cv_func_posix_fadvise" = xyes],
        [AC_MSG_RESULT(
          [yes])
        AC_DEFINE(
          [HAVE_POSIX_FADVISE],
          [1],
          [Define to 1 if you have the posix_fadvise function.]) ],
        [AC_MSG_RESULT(
          [no]) ])
    ])
  ])

dnl Function to detect if libcfile dependencies are available
AC_DEFUN([AX_LIBCFILE_CHECK_LOCAL],
  [dnl Headers included in libcfile/libcfile_file.c and libcfile/libcfile_support.c
  AC_CHECK_HEADERS([errno.h stdio.h sys/stat.h])

  dnl Headers included in libcfile/libcfile_file.c
  AC_CHECK_HEADERS([cygwin/fs.h fcntl.h linux/fs.h sys/disk.h sys/disklabel.h sys/ioctl.h unistd.h])

  dnl File input/output functions used in libcfile/libcfile_file.c
  AC_CHECK_FUNCS([close fstat ftruncate ioctl lseek open read write])

  AS_IF(
    [test "x$ac_cv_func_close" != xyes],
    [AC_MSG_FAILURE(
      [Missing function: close],
      [1])
    ])

  AX_LIBCFILE_CHECK_FUNC_POSIX_FADVISE

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
    [test x"$ac_cv_enable_winapi" = xno],
    [AS_IF(
      [test "x$ac_cv_func_ioctl" != xyes],
      [AC_MSG_FAILURE(
        [Missing function: ioctl],
        [1])
      ])
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
    [test "x$ac_cv_func_write" != xyes],
    [AC_MSG_FAILURE(
      [Missing function: write],
      [1])
    ])

  dnl File input/output functions used in libcfile/libcfile_support.c
  AC_CHECK_FUNCS([stat unlink])

  AS_IF(
    [test "x$ac_cv_func_stat" != xyes],
    [AC_MSG_FAILURE(
      [Missing function: stat],
      [1])
    ])

  AS_IF(
    [test "x$ac_cv_func_unlink" != xyes],
    [AC_MSG_FAILURE(
      [Missing function: unlink],
      [1])
    ])
  ])

