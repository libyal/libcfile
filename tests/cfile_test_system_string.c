/*
 * System string functions test program
 *
 * Copyright (C) 2008-2019, Joachim Metz <joachim.metz@gmail.com>
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
#include <system_string.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "cfile_test_libcerror.h"
#include "cfile_test_libcfile.h"
#include "cfile_test_macros.h"
#include "cfile_test_unused.h"

#include "../libcfile/libcfile_system_string.h"

#if defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT )

/* Tests the libcfile_system_string_size_to_narrow_string function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_system_string_size_to_narrow_string(
     void )
{
	libcerror_error_t *error  = NULL;
	size_t narrow_string_size = 0;
	int result                = 0;

	/* Test regular cases
	 */
	result = libcfile_system_string_size_to_narrow_string(
	          _SYSTEM_STRING( "Test1234" ),
	          9,
	          &narrow_string_size,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_EQUAL_SIZE(
	 "narrow_string_size",
	 narrow_string_size,
	 (size_t) 9 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libcfile_system_string_size_to_narrow_string(
	          NULL,
	          9,
	          &narrow_string_size,
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

	result = libcfile_system_string_size_to_narrow_string(
	          _SYSTEM_STRING( "Test1234" ),
	          (size_t) SSIZE_MAX + 1,
	          &narrow_string_size,
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

	result = libcfile_system_string_size_to_narrow_string(
	          _SYSTEM_STRING( "Test1234" ),
	          9,
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

/* Tests the libcfile_system_string_copy_to_narrow_string function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_system_system_string_copy_to_narrow_string(
     void )
{
	char narrow_string[ 32 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libcfile_system_string_copy_to_narrow_string(
	          _SYSTEM_STRING( "Test1234" ),
	          9,
	          narrow_string,
	          32,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

/* TODO compare string */

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libcfile_system_string_copy_to_narrow_string(
	          NULL,
	          9,
	          narrow_string,
	          32,
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

	result = libcfile_system_string_copy_to_narrow_string(
	          _SYSTEM_STRING( "Test1234" ),
	          (size_t) SSIZE_MAX + 1,
	          narrow_string,
	          32,
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

	result = libcfile_system_string_copy_to_narrow_string(
	          _SYSTEM_STRING( "Test1234" ),
	          9,
	          NULL,
	          32,
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

	result = libcfile_system_string_copy_to_narrow_string(
	          _SYSTEM_STRING( "Test1234" ),
	          9,
	          narrow_string,
	          (size_t) SSIZE_MAX + 1,
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

/* Tests the libcfile_system_string_size_from_narrow_string function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_system_string_size_from_narrow_string(
     void )
{
	libcerror_error_t *error  = NULL;
	size_t system_string_size = 0;
	int result                = 0;

	/* Test regular cases
	 */
	result = libcfile_system_string_size_from_narrow_string(
	          "Test1234",
	          9,
	          &system_string_size,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_EQUAL_SIZE(
	 "system_string_size",
	 system_string_size,
	 (size_t) 9 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libcfile_system_string_size_from_narrow_string(
	          NULL,
	          9,
	          &system_string_size,
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

	result = libcfile_system_string_size_from_narrow_string(
	          "Test1234",
	          (size_t) SSIZE_MAX + 1,
	          &system_string_size,
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

	result = libcfile_system_string_size_from_narrow_string(
	          "Test1234",
	          9,
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

/* Tests the libcfile_system_string_copy_from_narrow_string function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_system_system_string_copy_from_narrow_string(
     void )
{
	system_character_t system_string[ 32 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libcfile_system_string_copy_from_narrow_string(
	          system_string,
	          32,
	          "Test1234",
	          9,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

/* TODO compare string */

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libcfile_system_string_copy_from_narrow_string(
	          NULL,
	          32,
	          "Test1234",
	          9,
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

	result = libcfile_system_string_copy_from_narrow_string(
	          system_string,
	          (size_t) SSIZE_MAX + 1,
	          "Test1234",
	          9,
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

	result = libcfile_system_string_copy_from_narrow_string(
	          system_string,
	          32,
	          NULL,
	          9,
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

	result = libcfile_system_string_copy_from_narrow_string(
	          system_string,
	          32,
	          "Test1234",
	          (size_t) SSIZE_MAX + 1,
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

/* Tests the libcfile_system_string_size_to_wide_string function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_system_string_size_to_wide_string(
     void )
{
	libcerror_error_t *error = NULL;
	size_t wide_string_size  = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libcfile_system_string_size_to_wide_string(
	          _SYSTEM_STRING( "Test1234" ),
	          9,
	          &wide_string_size,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_EQUAL_SIZE(
	 "wide_string_size",
	 wide_string_size,
	 (size_t) 9 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libcfile_system_string_size_to_wide_string(
	          NULL,
	          9,
	          &wide_string_size,
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

	result = libcfile_system_string_size_to_wide_string(
	          _SYSTEM_STRING( "Test1234" ),
	          (size_t) SSIZE_MAX + 1,
	          &wide_string_size,
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

	result = libcfile_system_string_size_to_wide_string(
	          _SYSTEM_STRING( "Test1234" ),
	          9,
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

/* Tests the libcfile_system_string_copy_to_wide_string function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_system_system_string_copy_to_wide_string(
     void )
{
	wchar_t wide_string[ 32 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libcfile_system_string_copy_to_wide_string(
	          _SYSTEM_STRING( "Test1234" ),
	          9,
	          wide_string,
	          32,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

/* TODO compare string */

	/* Test error cases
	 */
	result = libcfile_system_string_copy_to_wide_string(
	          NULL,
	          9,
	          wide_string,
	          32,
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

	result = libcfile_system_string_copy_to_wide_string(
	          _SYSTEM_STRING( "Test1234" ),
	          (size_t) SSIZE_MAX + 1,
	          wide_string,
	          32,
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

	result = libcfile_system_string_copy_to_wide_string(
	          _SYSTEM_STRING( "Test1234" ),
	          9,
	          NULL,
	          32,
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

	result = libcfile_system_string_copy_to_wide_string(
	          _SYSTEM_STRING( "Test1234" ),
	          9,
	          wide_string,
	          (size_t) SSIZE_MAX + 1,
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

/* Tests the libcfile_system_string_size_from_wide_string function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_system_string_size_from_wide_string(
     void )
{
	libcerror_error_t *error  = NULL;
	size_t system_string_size = 0;
	int result                = 0;

	/* Test regular cases
	 */
	result = libcfile_system_string_size_from_wide_string(
	          L"Test1234",
	          9,
	          &system_string_size,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_EQUAL_SIZE(
	 "system_string_size",
	 system_string_size,
	 (size_t) 9 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libcfile_system_string_size_from_wide_string(
	          NULL,
	          9,
	          &system_string_size,
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

	result = libcfile_system_string_size_from_wide_string(
	          L"Test1234",
	          (size_t) SSIZE_MAX + 1,
	          &system_string_size,
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

	result = libcfile_system_string_size_from_wide_string(
	          L"Test1234",
	          9,
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

/* Tests the libcfile_system_string_copy_from_wide_string function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_system_system_string_copy_from_wide_string(
     void )
{
	system_character_t system_string[ 32 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libcfile_system_string_copy_from_wide_string(
	          system_string,
	          32,
	          L"Test1234",
	          9,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

/* TODO compare string */

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libcfile_system_string_copy_from_wide_string(
	          NULL,
	          32,
	          L"Test1234",
	          9,
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

	result = libcfile_system_string_copy_from_wide_string(
	          system_string,
	          (size_t) SSIZE_MAX + 1,
	          L"Test1234",
	          9,
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

	result = libcfile_system_string_copy_from_wide_string(
	          system_string,
	          32,
	          NULL,
	          9,
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

	result = libcfile_system_string_copy_from_wide_string(
	          system_string,
	          32,
	          L"Test1234",
	          (size_t) SSIZE_MAX + 1,
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

#endif /* defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) */

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

#if defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT )

	CFILE_TEST_RUN(
	 "libcfile_system_string_size_to_narrow_string",
	 cfile_test_system_string_size_to_narrow_string );

	CFILE_TEST_RUN(
	 "libcfile_system_string_copy_to_narrow_string",
	 cfile_test_system_system_string_copy_to_narrow_string );

	CFILE_TEST_RUN(
	 "libcfile_system_string_size_from_narrow_string",
	 cfile_test_system_string_size_from_narrow_string );

	CFILE_TEST_RUN(
	 "libcfile_system_string_copy_from_narrow_string",
	 cfile_test_system_system_string_copy_from_narrow_string );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	CFILE_TEST_RUN(
	 "libcfile_system_string_size_to_wide_string",
	 cfile_test_system_string_size_to_wide_string );

	CFILE_TEST_RUN(
	 "libcfile_system_string_copy_to_wide_string",
	 cfile_test_system_system_string_copy_to_wide_string );

	CFILE_TEST_RUN(
	 "libcfile_system_string_size_from_wide_string",
	 cfile_test_system_string_size_from_wide_string );

	CFILE_TEST_RUN(
	 "libcfile_system_string_copy_from_wide_string",
	 cfile_test_system_system_string_copy_from_wide_string );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#endif /* defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

