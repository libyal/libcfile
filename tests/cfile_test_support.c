/*
 * Library support functions test program
 *
 * Copyright (C) 2008-2016, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <narrow_string.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "cfile_test_libcerror.h"
#include "cfile_test_libcfile.h"
#include "cfile_test_macros.h"
#include "cfile_test_unused.h"

/* Tests the libcfile_get_version function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_get_version(
     void )
{
	const char *version_string = NULL;
	int result                 = 0;

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
	libcerror_error_t *error = NULL;
	int result               = 0;

	result = libcfile_file_exists(
	          "Makefile.am",
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
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

	result = libcfile_file_exists_wide(
	          L"Makefile.am",
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
	CFILE_TEST_UNREFERENCED_PARAMETER( argc )
	CFILE_TEST_UNREFERENCED_PARAMETER( argv )

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

	/* TODO add tests for libcfile_file_remove */
	/* TODO add tests for libcfile_file_remove_with_error_code */
	/* TODO add tests for libcfile_file_remove_wide */
	/* TODO add tests for libcfile_file_remove_wide_with_error_code */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

