/*
 * Library file type testing program
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

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "cfile_test_libcerror.h"
#include "cfile_test_libcfile.h"
#include "cfile_test_libcstring.h"
#include "cfile_test_macros.h"
#include "cfile_test_memory.h"
#include "cfile_test_unused.h"

/* Define to make cfile_test_file generate verbose output
#define CFILE_TEST_FILE_VERBOSE
 */

/* Tests the libcfile_file_initialize function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_initialize(
     void )
{
	libcfile_file_t *file    = NULL;
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test libcfile_file_initialize without entries
	 */
	result = libcfile_file_initialize(
	          &file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

        CFILE_TEST_ASSERT_IS_NOT_NULL(
         "file",
         file );

        CFILE_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libcfile_file_free(
	          &file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

        CFILE_TEST_ASSERT_IS_NULL(
         "file",
         file );

        CFILE_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libcfile_file_initialize(
	          NULL,
	          &error );

	CFILE_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 -1 );

        CFILE_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	file = (libcfile_file_t *) 0x12345678UL;

	result = libcfile_file_initialize(
	          &file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 -1 );

        CFILE_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	file = NULL;

#if defined( HAVE_CFILE_TEST_MEMORY )

	/* Test libcfile_file_initialize with malloc failing
	 */
	cfile_test_malloc_attempts_before_fail = 0;

	result = libcfile_file_initialize(
	          &file,
	          &error );

	if( cfile_test_malloc_attempts_before_fail != -1 )
	{
		cfile_test_malloc_attempts_before_fail = -1;
	}
	else
	{
		CFILE_TEST_ASSERT_EQUAL(
		 "result",
		 result,
		 -1 );

		CFILE_TEST_ASSERT_IS_NULL(
		 "file",
		 file );

		CFILE_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libcfile_file_initialize with memset failing
	 */
	cfile_test_memset_attempts_before_fail = 0;

	result = libcfile_file_initialize(
	          &file,
	          &error );

	if( cfile_test_memset_attempts_before_fail != -1 )
	{
		cfile_test_memset_attempts_before_fail = -1;
	}
	else
	{
		CFILE_TEST_ASSERT_EQUAL(
		 "result",
		 result,
		 -1 );

		CFILE_TEST_ASSERT_IS_NULL(
		 "file",
		 file );

		CFILE_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_CFILE_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libcfile_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libcfile_file_free function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libcfile_file_free(
	          NULL,
	          &error );

	CFILE_TEST_ASSERT_EQUAL(
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

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libcstring_system_character_t *source = NULL;

	if( argc >= 2 )
	{
		source = argv[ 1 ];
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( CFILE_TEST_FILE_VERBOSE )
	libcfile_notify_set_verbose(
	 1 );
	libcfile_notify_set_stream(
	 stderr,
	 NULL );
#endif

	CFILE_TEST_RUN(
	 "libcfile_file_initialize",
	 cfile_test_file_initialize() )

	CFILE_TEST_RUN(
	 "libcfile_file_free",
	 cfile_test_file_free() )

	if( source != NULL )
	{
	/* TODO: add test for libcfile_file_open */
	/* TODO: add test for libcfile_file_open_with_error_code */
	/* TODO: add test for libcfile_file_open_wide */
	/* TODO: add test for libcfile_file_open_wide_with_error_code */
	/* TODO: add test for libcfile_file_close */
	/* TODO: add test for libcfile_file_read_buffer */
	/* TODO: add test for libcfile_file_read_buffer_with_error_code */
	/* TODO: add test for libcfile_file_seek_offset */
	}
	/* TODO: add test for libcfile_file_write_buffer */
	/* TODO: add test for libcfile_file_write_buffer_with_error_code */
	/* TODO: add test for libcfile_file_resize */
	/* TODO: add test for libcfile_file_is_open */
	/* TODO: add test for libcfile_file_get_offset */
	/* TODO: add test for libcfile_file_get_size */
	/* TODO: add test for libcfile_file_is_device */
	/* TODO: add test for libcfile_file_io_control_read */
	/* TODO: add test for libcfile_file_io_control_read_with_error_code */
	/* TODO: add test for libcfile_file_set_access_behavior */
	/* TODO: add test for libcfile_file_set_block_size */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

