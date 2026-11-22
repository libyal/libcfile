/*
 * Library support functions test program
 *
 * Copyright (C) 2008-2026, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <memory.h>
#include <narrow_string.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#if defined( HAVE_SYS_STAT_H )
#include <sys/stat.h>
#endif

#if defined( HAVE_SYS_TYPES_H )
#include <sys/types.h>
#endif

#if defined( HAVE_FCNTL_H )
#include <fcntl.h>
#endif

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#include "cfile_test_functions.h"
#include "cfile_test_libcerror.h"
#include "cfile_test_libcfile.h"
#include "cfile_test_macros.h"
#include "cfile_test_unused.h"

#include "../libcfile/libcfile_support.h"

/* Tests the libcfile_get_version function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_get_version(
     void )
{
	const char *version_string = NULL;
	int result                 = 0;

	/* Test regular cases
	 */
	version_string = libcfile_get_version();

	result = narrow_string_compare(
	          version_string,
	          LIBCFILE_VERSION_STRING,
	          9 );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	return( 1 );

on_error:
	return( 0 );
}

/* Tests the libcfile_get_codepage function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_get_codepage(
     void )
{
	libcerror_error_t *error = NULL;
	int codepage             = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libcfile_get_codepage(
	          &codepage,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libcfile_get_codepage(
	          NULL,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libcfile_set_codepage function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_set_codepage(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libcfile_set_codepage(
	          0,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libcfile_set_codepage(
	          -1,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libcfile_file_exists function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_exists(
     void )
{
#if !defined( WINAPI ) && !defined( __MINGW32__ )
	char inaccessible_directory[ 18 ] = {
		'c', 'f', 'i', 'l', 'e', '_', 't', 'e', 's', 't', '_', 'X', 'X', 'X', 'X', 'X', 'X', 0 };

	char inaccessible_file[ 32 ]      = { 0 };
#endif
	libcerror_error_t *error          = NULL;
	int result                        = 0;

#if !defined( WINAPI ) && !defined( __MINGW32__ )
	size_t directory_length           = 0;
	int file_descriptor               = -1;
	int with_directory                = 0;
#endif

	/* Test regular cases
	 */
	result = libcfile_file_exists(
	          "TestFile",
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcfile_file_exists(
	          "bogus",
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#if !defined( WINAPI ) && !defined( __MINGW32__ )
	/* Test a file in a directory without access permission
	 * On POSIX stat() fails with EACCES in this case
	 * the file is expected to be reported as existing
	 */
	result = cfile_test_get_temporary_filename(
	          inaccessible_directory,
	          18,
	          &error );

	CFILE_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	with_directory = result;

	if( with_directory != 0 )
	{
		/* Convert the temporary file into a directory
		 */
		result = libcfile_file_remove(
		          inaccessible_directory,
		          &error );

		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		CFILE_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = mkdir(
		          inaccessible_directory,
		          0700 );

		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		directory_length = narrow_string_length(
		                    inaccessible_directory );

		memory_copy(
		 inaccessible_file,
		 inaccessible_directory,
		 directory_length );

		inaccessible_file[ directory_length ]     = '/';
		inaccessible_file[ directory_length + 1 ] = 'f';
		inaccessible_file[ directory_length + 2 ] = 0;

		file_descriptor = open(
		                   inaccessible_file,
		                   O_WRONLY | O_CREAT,
		                   0600 );

		CFILE_TEST_ASSERT_NOT_EQUAL_INT(
		 "file_descriptor",
		 file_descriptor,
		 -1 );

		close(
		 file_descriptor );

		chmod(
		 inaccessible_directory,
		 0 );

		result = libcfile_file_exists(
		          inaccessible_file,
		          &error );

		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		CFILE_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		chmod(
		 inaccessible_directory,
		 0700 );

		result = libcfile_file_remove(
		          inaccessible_file,
		          &error );

		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		CFILE_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		rmdir(
		 inaccessible_directory );

		with_directory = 0;
	}
#endif /* !defined( WINAPI ) && !defined( __MINGW32__ ) */

	/* Test error cases
	 */
	result = libcfile_file_exists(
	          NULL,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if !defined( WINAPI ) && !defined( __MINGW32__ )
	/* Test a file with an invalid path such as within a non-directory
	 */
	result = libcfile_file_exists(
	          "TestFile/x",
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#endif /* !defined( WINAPI ) && !defined( __MINGW32__ ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
#if !defined( WINAPI ) && !defined( __MINGW32__ )
	if( with_directory != 0 )
	{
		chmod(
		 inaccessible_directory,
		 0700 );

		if( inaccessible_file[ 0 ] != 0 )
		{
			libcfile_file_remove(
			 inaccessible_file,
			 NULL );
		}
		rmdir(
		 inaccessible_directory );
	}
#endif /* !defined( WINAPI ) && !defined( __MINGW32__ ) */
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libcfile_file_exists_wide function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_exists_wide(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libcfile_file_exists_wide(
	          L"TestFile",
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcfile_file_exists_wide(
	          L"bogus",
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libcfile_file_exists_wide(
	          NULL,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libcfile_file_remove function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_remove(
     void )
{
	char temporary_filename[ 18 ] = {
		'c', 'f', 'i', 'l', 'e', '_', 't', 'e', 's', 't', '_', 'X', 'X', 'X', 'X', 'X', 'X', 0 };

	libcerror_error_t *error = NULL;
	int result               = 0;
	int with_temporary_file  = 0;

	/* Test regular cases
	 */
	result = cfile_test_get_temporary_filename(
	          temporary_filename,
	          18,
	          &error );

	CFILE_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	with_temporary_file = result;

	if( with_temporary_file != 0 )
	{
		result = libcfile_file_remove(
		          temporary_filename,
		          &error );

		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		CFILE_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		with_temporary_file = 0;
	}
	/* Test error cases
	 */
	result = libcfile_file_remove(
	          NULL,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test removing a non-existent file
	 */
	result = libcfile_file_remove(
	          "bogus",
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( with_temporary_file != 0 )
	{
		libcfile_file_remove(
		 temporary_filename,
		 NULL );
	}
	return( 0 );
}

/* Tests the libcfile_file_remove_with_error_code function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_remove_with_error_code(
     void )
{
	char temporary_filename[ 18 ] = {
		'c', 'f', 'i', 'l', 'e', '_', 't', 'e', 's', 't', '_', 'X', 'X', 'X', 'X', 'X', 'X', 0 };

	libcerror_error_t *error = NULL;
	uint32_t error_code      = 0;
	int result               = 0;
	int with_temporary_file  = 0;

	/* Test regular cases
	 */
	result = cfile_test_get_temporary_filename(
	          temporary_filename,
	          18,
	          &error );

	CFILE_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	with_temporary_file = result;

	if( with_temporary_file != 0 )
	{
		result = libcfile_file_remove_with_error_code(
		          temporary_filename,
		          &error_code,
		          &error );

		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		CFILE_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		with_temporary_file = 0;
	}
	/* Test error cases
	 */
	result = libcfile_file_remove_with_error_code(
	          NULL,
	          &error_code,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcfile_file_remove_with_error_code(
	          temporary_filename,
	          NULL,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test removing a non-existent file
	 */
	result = libcfile_file_remove_with_error_code(
	          "bogus",
	          &error_code,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( with_temporary_file != 0 )
	{
		libcfile_file_remove(
		 temporary_filename,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libcfile_file_remove_wide function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_remove_wide(
     void )
{
	wchar_t temporary_filename[ 18 ] = {
		'c', 'f', 'i', 'l', 'e', '_', 't', 'e', 's', 't', '_', 'X', 'X', 'X', 'X', 'X', 'X', 0 };

	libcerror_error_t *error = NULL;
	int result               = 0;
	int with_temporary_file  = 0;

	/* Test regular cases
	 */
	result = cfile_test_get_temporary_filename_wide(
	          temporary_filename,
	          18,
	          &error );

	CFILE_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	with_temporary_file = result;

	if( with_temporary_file != 0 )
	{
		result = libcfile_file_remove_wide(
		          temporary_filename,
		          &error );

		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		CFILE_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		with_temporary_file = 0;
	}
	/* Test error cases
	 */
	result = libcfile_file_remove_wide(
	          NULL,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( with_temporary_file != 0 )
	{
		libcfile_file_remove_wide(
		 temporary_filename,
		 NULL );
	}
	return( 0 );
}

/* Tests the libcfile_file_remove_wide_with_error_code function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_remove_wide_with_error_code(
     void )
{
	wchar_t temporary_filename[ 18 ] = {
		'c', 'f', 'i', 'l', 'e', '_', 't', 'e', 's', 't', '_', 'X', 'X', 'X', 'X', 'X', 'X', 0 };

	libcerror_error_t *error = NULL;
	uint32_t error_code      = 0;
	int result               = 0;
	int with_temporary_file  = 0;

	/* Test regular cases
	 */
	result = cfile_test_get_temporary_filename_wide(
	          temporary_filename,
	          18,
	          &error );

	CFILE_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	with_temporary_file = result;

	if( with_temporary_file != 0 )
	{
		result = libcfile_file_remove_wide_with_error_code(
		          temporary_filename,
		          &error_code,
		          &error );

		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		CFILE_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		with_temporary_file = 0;
	}
	/* Test error cases
	 */
	result = libcfile_file_remove_wide_with_error_code(
	          NULL,
	          &error_code,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcfile_file_remove_wide_with_error_code(
	          temporary_filename,
	          NULL,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( with_temporary_file != 0 )
	{
		libcfile_file_remove_wide(
		 temporary_filename,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc CFILE_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] CFILE_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc CFILE_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] CFILE_TEST_ATTRIBUTE_UNUSED )
#endif
{
	FILE *file_stream = NULL;
	int result        = 0;

	CFILE_TEST_UNREFERENCED_PARAMETER( argc )
	CFILE_TEST_UNREFERENCED_PARAMETER( argv )

	file_stream = file_stream_open(
	               "TestFile",
	               "a" );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "file_stream",
	 file_stream );

	result = file_stream_close(
	          file_stream );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	file_stream = NULL;

	CFILE_TEST_RUN(
	 "libcfile_get_version",
	 cfile_test_get_version );

	CFILE_TEST_RUN(
	 "libcfile_get_codepage",
	 cfile_test_get_codepage );

	CFILE_TEST_RUN(
	 "libcfile_set_codepage",
	 cfile_test_set_codepage );

	CFILE_TEST_RUN(
	 "libcfile_file_exists",
	 cfile_test_file_exists );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	CFILE_TEST_RUN(
	 "libcfile_file_exists_wide",
	 cfile_test_file_exists_wide );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

	CFILE_TEST_RUN(
	 "libcfile_file_remove",
	 cfile_test_file_remove );

	CFILE_TEST_RUN(
	 "libcfile_file_remove_with_error_code",
	 cfile_test_file_remove_with_error_code );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	CFILE_TEST_RUN(
	 "libcfile_file_remove_wide",
	 cfile_test_file_remove_wide );

	CFILE_TEST_RUN(
	 "libcfile_file_remove_wide_with_error_code",
	 cfile_test_file_remove_wide_with_error_code );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

