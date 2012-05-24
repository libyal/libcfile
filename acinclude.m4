dnl Functions for libcfile
dnl
dnl Version: 20120325

dnl Function to detect if libcfile dependencies are available
AC_DEFUN([AX_LIBCFILE_CHECK_LOCAL],
 [dnl Headers included in libcfile/libcfile_file.h and libcfile/libcfile_support.h
 AC_CHECK_HEADERS([errno.h sys/stat.h])

 dnl Headers included in libcfile/libcfile_file.h
 AC_CHECK_HEADERS([fcntl.h unistd.h])

 dnl File input/output functions used in libcfile/libcfile_file.h
 AC_CHECK_FUNCS([close fstat ftruncate lseek open read write])

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
  [test "x$ac_cv_func_write" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: write],
   [1])
  ])

 dnl File stream functions used in libcfile/libcfile_stream.h
 AC_CHECK_FUNCS([fclose feof fopen fread fseeko fseeko64 ftello ftello64 fwrite])

 AS_IF(
  [test "x$ac_cv_func_fclose" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: fclose],
   [1])
  ])
 
 AS_IF(
  [test "x$ac_cv_func_feof" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: feof],
   [1])
  ])
 
 AS_IF(
  [test "x$ac_cv_func_fgets" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: fgets],
   [1])
  ])
 
 AS_IF(
  [test "x$ac_cv_func_fopen" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: fopen],
   [1])
  ])
 
 AS_IF(
  [test "x$ac_cv_func_fread" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: fread],
   [1])
  ])
 
 AS_IF(
  [test "x$ac_cv_func_fseeko" != xyes && test "x$ac_cv_func_fseeko64" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: fseeko and fseeko64],
   [1])
  ])
 
 AS_IF(
  [test "x$ac_cv_func_ftello" != xyes && test "x$ac_cv_func_ftello64" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: ftello and ftello64],
   [1])
  ])
 
 AS_IF(
  [test "x$ac_cv_func_fwrite" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: fwrite],
   [1])
  ])
 
 dnl File input/output functions used in libcfile/libcfile_support.h
 AC_CHECK_FUNCS([stat])

 AS_IF(
  [test "x$ac_cv_func_stat" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: stat],
   [1])
  ])
 ])

