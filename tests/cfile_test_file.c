/*
 * Library file type test program
 *
 * Copyright (C) 2008-2021, Joachim Metz <joachim.metz@gmail.com>
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "cfile_test_functions.h"
#include "cfile_test_getopt.h"
#include "cfile_test_libcerror.h"
#include "cfile_test_libcfile.h"
#include "cfile_test_macros.h"
#include "cfile_test_memory.h"

#include "../libcfile/libcfile_file.h"

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make cfile_test_file generate verbose output
#define CFILE_TEST_FILE_VERBOSE
 */

/* Creates and opens a source file
 * Returns 1 if successful or -1 on error
 */
int cfile_test_file_open_source(
     libcfile_file_t **file,
     const system_character_t *source,
     libcerror_error_t **error )
{
	static char *function = "cfile_test_file_open_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( libcfile_file_initialize(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize file.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libcfile_file_open_wide(
	          *file,
	          source,
	          LIBCFILE_OPEN_READ,
	          error );
#else
	result = libcfile_file_open(
	          *file,
	          source,
	          LIBCFILE_OPEN_READ,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *file != NULL )
	{
		libcfile_file_free(
		 file,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source file
 * Returns 1 if successful or -1 on error
 */
int cfile_test_file_close_source(
     libcfile_file_t **file,
     libcerror_error_t **error )
{
	static char *function = "cfile_test_file_close_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( libcfile_file_close(
	     *file,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close file.",
		 function );

		result = -1;
	}
	if( libcfile_file_free(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free file.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libcfile_file_initialize function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libcfile_file_t *file           = NULL;
	int result                      = 0;

#if defined( HAVE_CFILE_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libcfile_file_initialize(
	          &file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
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

	CFILE_TEST_ASSERT_EQUAL_INT(
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

	CFILE_TEST_ASSERT_EQUAL_INT(
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

	file = NULL;

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_CFILE_TEST_MEMORY )
	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libcfile_file_initialize with malloc failing
		 */
		cfile_test_malloc_attempts_before_fail = test_number;

		result = libcfile_file_initialize(
		          &file,
		          &error );

		if( cfile_test_malloc_attempts_before_fail != -1 )
		{
			cfile_test_malloc_attempts_before_fail = -1;

			if( file != NULL )
			{
				libcfile_file_free(
				 &file,
				 NULL );
			}
		}
		else
		{
			CFILE_TEST_ASSERT_EQUAL_INT(
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
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libcfile_file_initialize with memset failing
		 */
		cfile_test_memset_attempts_before_fail = test_number;

		result = libcfile_file_initialize(
		          &file,
		          &error );

		if( cfile_test_memset_attempts_before_fail != -1 )
		{
			cfile_test_memset_attempts_before_fail = -1;

			if( file != NULL )
			{
				libcfile_file_free(
				 &file,
				 NULL );
			}
		}
		else
		{
			CFILE_TEST_ASSERT_EQUAL_INT(
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

/* Tests the libcfile_file_write_buffer function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_write_buffer(
     void )
{
	char narrow_temporary_filename[ 18 ] = {
		'c', 'f', 'i', 'l', 'e', '_', 't', 'e', 's', 't', '_', 'X', 'X', 'X', 'X', 'X', 'X', 0 };

	uint8_t buffer[ 32 ] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5' };

	libcerror_error_t *error = NULL;
	libcfile_file_t *file    = NULL;
	ssize_t write_count      = 0;
	int result               = 0;
	int with_temporary_file  = 0;

	/* Initialize test
	 */
	result = libcfile_file_initialize(
	          &file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = cfile_test_get_temporary_filename(
	          narrow_temporary_filename,
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
		result = libcfile_file_open(
		          file,
		          narrow_temporary_filename,
		          LIBCFILE_OPEN_WRITE,
		          &error );

		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		CFILE_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Test regular cases
		 */
		write_count = libcfile_file_write_buffer(
		               file,
		               buffer,
		               32,
		               &error );

		CFILE_TEST_ASSERT_EQUAL_SSIZE(
		 "write_count",
		 write_count,
		 (ssize_t) 32 );

		CFILE_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	write_count = libcfile_file_write_buffer(
	               NULL,
	               buffer,
	               32,
	               &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "write_count",
	 write_count,
	 (ssize_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	if( with_temporary_file != 0 )
	{
		result = libcfile_file_close(
		          file,
		          &error );

		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		CFILE_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libcfile_file_remove(
		          narrow_temporary_filename,
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
	result = libcfile_file_free(
	          &file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

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
		 narrow_temporary_filename,
		 NULL );
	}
	if( file != NULL )
	{
		libcfile_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libcfile_file_write_buffer_with_error_code function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_write_buffer_with_error_code(
     void )
{
	char narrow_temporary_filename[ 18 ] = {
		'c', 'f', 'i', 'l', 'e', '_', 't', 'e', 's', 't', '_', 'X', 'X', 'X', 'X', 'X', 'X', 0 };

	uint8_t buffer[ 32 ] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5' };

	libcerror_error_t *error     = NULL;
	libcfile_file_t *closed_file = NULL;
	libcfile_file_t *file        = NULL;
	ssize_t write_count          = 0;
	uint32_t error_code          = 0;
	int result                   = 0;
	int with_temporary_file      = 0;

#if defined( WINAPI )
	HANDLE file_handle           = INVALID_HANDLE_VALUE;
#else
	int file_descriptor          = -1;
#endif

	/* Initialize test
	 */
	result = libcfile_file_initialize(
	          &file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = cfile_test_get_temporary_filename(
	          narrow_temporary_filename,
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
		result = libcfile_file_open(
		          file,
		          narrow_temporary_filename,
		          LIBCFILE_OPEN_WRITE,
		          &error );

		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		CFILE_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Test regular cases
		 */
		write_count = libcfile_file_write_buffer_with_error_code(
		               file,
		               buffer,
		               32,
		               &error_code,
		               &error );

		CFILE_TEST_ASSERT_EQUAL_SSIZE(
		 "write_count",
		 write_count,
		 (ssize_t) 32 );

		CFILE_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	write_count = libcfile_file_write_buffer_with_error_code(
	               NULL,
	               buffer,
	               0,
	               &error_code,
	               &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "write_count",
	 write_count,
	 (ssize_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( WINAPI )
	file_handle = ( (libcfile_internal_file_t *) file )->handle;

	( (libcfile_internal_file_t *) file )->handle = INVALID_HANDLE_VALUE;
#else
	file_descriptor = ( (libcfile_internal_file_t *) file )->descriptor;

	( (libcfile_internal_file_t *) file )->descriptor = -1;
#endif

	write_count = libcfile_file_write_buffer_with_error_code(
	               file,
	               buffer,
	               0,
	               &error_code,
	               &error );

#if defined( WINAPI )
	( (libcfile_internal_file_t *) file )->handle = file_handle;
#else
	( (libcfile_internal_file_t *) file )->descriptor = file_descriptor;
#endif

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "write_count",
	 write_count,
	 (ssize_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	write_count = libcfile_file_write_buffer_with_error_code(
	               file,
	               NULL,
	               0,
	               &error_code,
	               &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "write_count",
	 write_count,
	 (ssize_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	write_count = libcfile_file_write_buffer_with_error_code(
	               file,
	               buffer,
	               (size_t) SSIZE_MAX + 1,
	               &error_code,
	               &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "write_count",
	 write_count,
	 (ssize_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	write_count = libcfile_file_write_buffer_with_error_code(
	               file,
	               buffer,
	               0,
	               NULL,
	               &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "write_count",
	 write_count,
	 (ssize_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Initialize test
	 */
	result = libcfile_file_initialize(
	          &closed_file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "closed_file",
	 closed_file );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test write buffer with error code on a closed file
	 */
	write_count = libcfile_file_write_buffer_with_error_code(
	               closed_file,
	               buffer,
	               0,
	               &error_code,
	               &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "write_count",
	 write_count,
	 (ssize_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libcfile_file_free(
	          &closed_file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "closed_file",
	 closed_file );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( with_temporary_file != 0 )
	{
		result = libcfile_file_close(
		          file,
		          &error );

		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		CFILE_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libcfile_file_remove(
		          narrow_temporary_filename,
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
	result = libcfile_file_free(
	          &file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( closed_file != NULL )
	{
		libcfile_file_free(
		 &closed_file,
		 NULL );
	}
	if( with_temporary_file != 0 )
	{
		libcfile_file_remove(
		 narrow_temporary_filename,
		 NULL );
	}
	if( file != NULL )
	{
		libcfile_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libcfile_file_seek_offset function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_seek_offset(
     libcfile_file_t *file )
{
	libcerror_error_t *error     = NULL;
	libcfile_file_t *closed_file = NULL;
	size64_t file_size           = 0;
	off64_t offset               = 0;
	off64_t seek_offset          = 0;
	int result                   = 0;

	/* Initialize test
	 */
	result = libcfile_file_get_size(
	          file,
	          &file_size,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset with offset: 0 and whence: SEEK_SET
	 */
	seek_offset = 0;

	offset = libcfile_file_seek_offset(
	          file,
	          seek_offset,
	          SEEK_SET,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) seek_offset );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset with offset: <file_size> and whence: SEEK_SET
	 */
	seek_offset = (off64_t) file_size;

	offset = libcfile_file_seek_offset(
	          file,
	          seek_offset,
	          SEEK_SET,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) seek_offset );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset with offset: <file_size / 5> and whence: SEEK_SET
	 */
	seek_offset = (off64_t) ( file_size / 5 );

	offset = libcfile_file_seek_offset(
	          file,
	          seek_offset,
	          SEEK_SET,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) seek_offset );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset with offset: <file_size / 5> and whence: SEEK_CUR
	 */
	offset = libcfile_file_seek_offset(
	          file,
	          seek_offset,
	          SEEK_CUR,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) seek_offset + seek_offset );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset with offset: <-1 * (file_size / 5)> and whence: SEEK_CUR
	 */
	offset = libcfile_file_seek_offset(
	          file,
	          -1 * seek_offset,
	          SEEK_CUR,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) seek_offset );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset with offset: <file_size + 987> and whence: SEEK_SET
	 */
	seek_offset = (off64_t) ( file_size + 987 );

	offset = libcfile_file_seek_offset(
	          file,
	          seek_offset,
	          SEEK_SET,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) seek_offset );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset with offset: 0 and whence: SEEK_CUR
	 */
	offset = libcfile_file_seek_offset(
	          file,
	          0,
	          SEEK_CUR,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) seek_offset );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset with offset: 0 and whence: SEEK_END
	 */
	offset = libcfile_file_seek_offset(
	          file,
	          0,
	          SEEK_END,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) file_size );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset with offset: <-1 * (file_size / 4)> and whence: SEEK_END
	 */
	seek_offset = (off64_t) ( file_size / 4 );

	offset = libcfile_file_seek_offset(
	          file,
	          -1 * seek_offset,
	          SEEK_END,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) file_size - seek_offset );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset with offset: 542 and whence: SEEK_END
	 */
	offset = libcfile_file_seek_offset(
	          file,
	          542,
	          SEEK_END,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) file_size + 542 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset with offset: <-1 * file_size> and whence: SEEK_END
	 */
	offset = libcfile_file_seek_offset(
	          file,
	          -1 * file_size,
	          SEEK_END,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	offset = libcfile_file_seek_offset(
	          NULL,
	          0,
	          SEEK_SET,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test seek offset with offset: -987 and whence: SEEK_SET
	 */
	offset = libcfile_file_seek_offset(
	          file,
	          -987,
	          SEEK_SET,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test seek offset with offset: <1 * (file_size + 542)> and whence: SEEK_END
	 */
	offset = libcfile_file_seek_offset(
	          file,
	          -1 * (file_size + 542),
	          SEEK_END,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test seek offset with offset: 0 and whence: UNKNOWN (88)
	 */
	offset = libcfile_file_seek_offset(
	          file,
	          0,
	          88,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Initialize test
	 */
	result = libcfile_file_initialize(
	          &closed_file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "closed_file",
	 closed_file );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset on a closed file
	 */
	offset = libcfile_file_seek_offset(
	          closed_file,
	          0,
	          SEEK_SET,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libcfile_file_free(
	          &closed_file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "closed_file",
	 closed_file );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( closed_file != NULL )
	{
		libcfile_file_free(
		 &closed_file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libcfile_file_resize function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_resize(
     void )
{
	char narrow_temporary_filename[ 18 ] = {
		'c', 'f', 'i', 'l', 'e', '_', 't', 'e', 's', 't', '_', 'X', 'X', 'X', 'X', 'X', 'X', 0 };

	uint8_t buffer[ 32 ] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5' };

	libcerror_error_t *error = NULL;
	libcfile_file_t *file    = NULL;
	ssize_t write_count      = 0;
	int result               = 0;
	int with_temporary_file  = 0;

	/* Initialize test
	 */
	result = libcfile_file_initialize(
	          &file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = cfile_test_get_temporary_filename(
	          narrow_temporary_filename,
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
		result = libcfile_file_open(
		          file,
		          narrow_temporary_filename,
		          LIBCFILE_OPEN_WRITE,
		          &error );

		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		CFILE_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		write_count = libcfile_file_write_buffer(
		               file,
		               buffer,
		               32,
		               &error );

		CFILE_TEST_ASSERT_EQUAL_SSIZE(
		 "write_count",
		 write_count,
		 (ssize_t) 32 );

		CFILE_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Test regular cases
		 */
		result = libcfile_file_resize(
		          file,
		          16,
		          &error );

		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		CFILE_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libcfile_file_resize(
	          NULL,
	          16,
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

	result = libcfile_file_resize(
	          file,
	          (size64_t) INT64_MAX + 1,
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

	/* Clean up
	 */
	if( with_temporary_file != 0 )
	{
		result = libcfile_file_close(
		          file,
		          &error );

		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		CFILE_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libcfile_file_remove(
		          narrow_temporary_filename,
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
	result = libcfile_file_free(
	          &file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

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
		 narrow_temporary_filename,
		 NULL );
	}
	if( file != NULL )
	{
		libcfile_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libcfile_file_open functions
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	libcfile_file_t *file    = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = cfile_test_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcfile_file_initialize(
	          &file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libcfile_file_open(
	          file,
	          narrow_source,
	          LIBCFILE_OPEN_READ,
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
	result = libcfile_file_open(
	          file,
	          narrow_source,
	          LIBCFILE_OPEN_READ,
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

	/* Clean up
	 */
	result = libcfile_file_close(
	          file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcfile_file_free(
	          &file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

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

/* Tests the libcfile_file_open_with_error_code functions
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_open_with_error_code(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	libcfile_file_t *file    = NULL;
	uint32_t error_code      = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = cfile_test_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcfile_file_initialize(
	          &file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libcfile_file_open_with_error_code(
	          file,
	          narrow_source,
	          LIBCFILE_OPEN_READ,
	          &error_code,
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
	result = libcfile_file_open_with_error_code(
	          file,
	          narrow_source,
	          LIBCFILE_OPEN_READ,
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

	/* Clean up
	 */
	result = libcfile_file_close(
	          file,
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
	result = libcfile_file_open_with_error_code(
	          NULL,
	          narrow_source,
	          LIBCFILE_OPEN_READ,
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

	result = libcfile_file_open_with_error_code(
	          file,
	          NULL,
	          LIBCFILE_OPEN_READ,
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

	result = libcfile_file_open_with_error_code(
	          file,
	          narrow_source,
	          0,
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

	result = libcfile_file_open_with_error_code(
	          file,
	          narrow_source,
	          LIBCFILE_OPEN_READ,
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

	/* Clean up
	 */
	result = libcfile_file_close(
	          file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcfile_file_free(
	          &file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

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

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libcfile_file_open_wide functions
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	libcfile_file_t *file    = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = cfile_test_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcfile_file_initialize(
	          &file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libcfile_file_open_wide(
	          file,
	          wide_source,
	          LIBCFILE_OPEN_READ,
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
	result = libcfile_file_open_wide(
	          file,
	          wide_source,
	          LIBCFILE_OPEN_READ,
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

	/* Clean up
	 */
	result = libcfile_file_close(
	          file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcfile_file_free(
	          &file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

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

/* Tests the libcfile_file_open_wide_with_error_code functions
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_open_wide_with_error_code(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	libcfile_file_t *file    = NULL;
	uint32_t error_code      = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = cfile_test_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcfile_file_initialize(
	          &file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libcfile_file_open_wide_with_error_code(
	          file,
	          wide_source,
	          LIBCFILE_OPEN_READ,
	          &error_code,
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
	result = libcfile_file_open_wide_with_error_code(
	          file,
	          wide_source,
	          LIBCFILE_OPEN_READ,
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

	/* Clean up
	 */
	result = libcfile_file_close(
	          file,
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
	result = libcfile_file_open_wide_with_error_code(
	          NULL,
	          wide_source,
	          LIBCFILE_OPEN_READ,
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

	result = libcfile_file_open_wide_with_error_code(
	          file,
	          NULL,
	          LIBCFILE_OPEN_READ,
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

	result = libcfile_file_open_wide_with_error_code(
	          file,
	          wide_source,
	          0,
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

	result = libcfile_file_open_wide_with_error_code(
	          file,
	          wide_source,
	          LIBCFILE_OPEN_READ,
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

	/* Clean up
	 */
	result = libcfile_file_close(
	          file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcfile_file_free(
	          &file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

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

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libcfile_file_close function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_close(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libcfile_file_close(
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

/* Tests the libcfile_file_open and libcfile_file_close functions
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_open_close(
     const system_character_t *source )
{
	libcerror_error_t *error = NULL;
	libcfile_file_t *file    = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libcfile_file_initialize(
	          &file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libcfile_file_open_wide(
	          file,
	          source,
	          LIBCFILE_OPEN_READ,
	          &error );
#else
	result = libcfile_file_open(
	          file,
	          source,
	          LIBCFILE_OPEN_READ,
	          &error );
#endif

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcfile_file_close(
	          file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close a second time to validate clean up on close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libcfile_file_open_wide(
	          file,
	          source,
	          LIBCFILE_OPEN_READ,
	          &error );
#else
	result = libcfile_file_open(
	          file,
	          source,
	          LIBCFILE_OPEN_READ,
	          &error );
#endif

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcfile_file_close(
	          file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libcfile_file_free(
	          &file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

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

/* Tests the libcfile_file_read_buffer function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_read_buffer(
     libcfile_file_t *file )
{
	uint8_t buffer[ 32 ];

	libcerror_error_t *error = NULL;
	size64_t file_size       = 0;
	ssize_t read_count       = 0;
	off64_t offset           = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libcfile_file_get_size(
	          file,
	          &file_size,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( file_size < 32 )
	{
		return( 1 );
	}
	offset = libcfile_file_seek_offset(
	          file,
	          0,
	          SEEK_SET,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	read_count = libcfile_file_read_buffer(
	              file,
	              buffer,
	              32,
	              &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 32 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	read_count = libcfile_file_read_buffer(
	              NULL,
	              buffer,
	              32,
	              &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

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

#if defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) && defined( WINAPI )

/* Tests the libcfile_internal_file_read_buffer_at_offset_with_error_code function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_internal_file_read_buffer_at_offset_with_error_code(
     libcfile_file_t *file )
{
	uint8_t buffer[ 32 ];

	libcerror_error_t *error     = NULL;
	libcfile_file_t *closed_file = NULL;
	size64_t file_size           = 0;
	ssize_t read_count           = 0;
	off64_t offset               = 0;
	uint32_t error_code          = 0;
	int result                   = 0;

	/* Initialize test
	 */
	result = libcfile_file_get_size(
	          file,
	          &file_size,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( file_size < 32 )
	{
		return( 1 );
	}
	offset = libcfile_file_seek_offset(
	          file,
	          0,
	          SEEK_SET,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	read_count = libcfile_internal_file_read_buffer_at_offset_with_error_code(
	              (libcfile_internal_file_t *) file,
	              0,
	              buffer,
	              32,
	              &error_code,
	              &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 32 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	read_count = libcfile_internal_file_read_buffer_at_offset_with_error_code(
	              NULL,
	              0,
	              buffer,
	              32,
	              &error_code,
	              &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libcfile_internal_file_read_buffer_at_offset_with_error_code(
	              (libcfile_internal_file_t *) file,
	              -1,
	              buffer,
	              32,
	              &error_code,
	              &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libcfile_internal_file_read_buffer_at_offset_with_error_code(
	              (libcfile_internal_file_t *) file,
	              0,
	              NULL,
	              32,
	              &error_code,
	              &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libcfile_internal_file_read_buffer_at_offset_with_error_code(
	              (libcfile_internal_file_t *) file,
	              0,
	              buffer,
	              (size_t) SSIZE_MAX + 1,
	              &error_code,
	              &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libcfile_internal_file_read_buffer_at_offset_with_error_code(
	              (libcfile_internal_file_t *) file,
	              0,
	              buffer,
	              32,
	              NULL,
	              &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Initialize test
	 */
	result = libcfile_file_initialize(
	          &closed_file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "closed_file",
	 closed_file );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test read buffer with error code on a closed file
	 */
	read_count = libcfile_internal_file_read_buffer_at_offset_with_error_code(
	              (libcfile_internal_file_t *) closed_file,
	              0,
	              buffer,
	              32,
	              &error_code,
	              &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libcfile_file_free(
	          &closed_file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "closed_file",
	 closed_file );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( closed_file != NULL )
	{
		libcfile_file_free(
		 &closed_file,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) && defined( WINAPI ) */

/* Tests the libcfile_file_read_buffer_with_error_code function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_read_buffer_with_error_code(
     libcfile_file_t *file )
{
	uint8_t buffer[ 32 ];

	libcerror_error_t *error     = NULL;
	libcfile_file_t *closed_file = NULL;
	size64_t file_size           = 0;
	ssize_t read_count           = 0;
	off64_t offset               = 0;
	uint32_t error_code          = 0;
	int result                   = 0;

#if defined( WINAPI )
	HANDLE file_handle           = INVALID_HANDLE_VALUE;
#else
	int file_descriptor          = -1;
#endif

	/* Initialize test
	 */
	result = libcfile_file_get_size(
	          file,
	          &file_size,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( file_size < 32 )
	{
		return( 1 );
	}
	offset = libcfile_file_seek_offset(
	          file,
	          0,
	          SEEK_SET,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	read_count = libcfile_file_read_buffer_with_error_code(
	              file,
	              buffer,
	              32,
	              &error_code,
	              &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 32 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	read_count = libcfile_file_read_buffer_with_error_code(
	              NULL,
	              buffer,
	              0,
	              &error_code,
	              &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( WINAPI )
	file_handle = ( (libcfile_internal_file_t *) file )->handle;

	( (libcfile_internal_file_t *) file )->handle = INVALID_HANDLE_VALUE;
#else
	file_descriptor = ( (libcfile_internal_file_t *) file )->descriptor;

	( (libcfile_internal_file_t *) file )->descriptor = -1;
#endif

	read_count = libcfile_file_read_buffer_with_error_code(
	              file,
	              buffer,
	              0,
	              &error_code,
	              &error );

#if defined( WINAPI )
	( (libcfile_internal_file_t *) file )->handle = file_handle;
#else
	( (libcfile_internal_file_t *) file )->descriptor = file_descriptor;
#endif

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libcfile_file_read_buffer_with_error_code(
	              file,
	              NULL,
	              0,
	              &error_code,
	              &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libcfile_file_read_buffer_with_error_code(
	              file,
	              buffer,
	              (size_t) SSIZE_MAX + 1,
	              &error_code,
	              &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libcfile_file_read_buffer_with_error_code(
	              file,
	              buffer,
	              0,
	              NULL,
	              &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Initialize test
	 */
	result = libcfile_file_initialize(
	          &closed_file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "closed_file",
	 closed_file );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test read buffer with error code on a closed file
	 */
	read_count = libcfile_file_read_buffer_with_error_code(
	              closed_file,
	              buffer,
	              0,
	              &error_code,
	              &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libcfile_file_free(
	          &closed_file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "closed_file",
	 closed_file );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( closed_file != NULL )
	{
		libcfile_file_free(
		 &closed_file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libcfile_file_is_open function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_is_open(
     libcfile_file_t *file )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libcfile_file_is_open(
	          file,
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
	result = libcfile_file_is_open(
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

/* Tests the libcfile_file_get_offset function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_get_offset(
     libcfile_file_t *file )
{
	libcerror_error_t *error = NULL;
	off64_t offset           = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libcfile_file_get_offset(
	          file,
	          &offset,
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
	result = libcfile_file_get_offset(
	          NULL,
	          &offset,
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

	result = libcfile_file_get_offset(
	          file,
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

#if defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT )

/* Tests the libcfile_internal_file_get_size function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_internal_file_get_size(
     libcfile_file_t *file )
{
	libcerror_error_t *error = NULL;
	size64_t size            = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libcfile_internal_file_get_size(
	          (libcfile_internal_file_t *) file,
	          &size,
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
	result = libcfile_internal_file_get_size(
	          NULL,
	          &size,
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

	result = libcfile_internal_file_get_size(
	          (libcfile_internal_file_t *) file,
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

#endif /* defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) */

/* Tests the libcfile_file_get_size function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_get_size(
     libcfile_file_t *file )
{
	libcerror_error_t *error = NULL;
	size64_t size            = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libcfile_file_get_size(
	          file,
	          &size,
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
	result = libcfile_file_get_size(
	          NULL,
	          &size,
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

	result = libcfile_file_get_size(
	          file,
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

/* Tests the libcfile_file_is_device function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_is_device(
     libcfile_file_t *file )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libcfile_file_is_device(
	          file,
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
	result = libcfile_file_is_device(
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

#if defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT )

/* Tests the libcfile_internal_file_io_control_read_with_error_code function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_internal_file_io_control_read_with_error_code(
     libcfile_file_t *file )
{
	uint8_t control_data[ 32 ];
	uint8_t data[ 128 ];

	libcerror_error_t *error = NULL;
	ssize_t read_count       = 0;
	uint32_t error_code      = 0;
	int result               = 0;

#if defined( WINAPI )
	HANDLE file_handle       = INVALID_HANDLE_VALUE;
#else
	int file_descriptor      = -1;
#endif

	/* Initialize test
	 */
	result = libcfile_file_is_device(
	          file,
	          &error );

	CFILE_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	if( result == 0 )
	{
/* TODO implement */
	}
	/* Test error cases
	 */
	read_count = libcfile_internal_file_io_control_read_with_error_code(
	              NULL,
	              0,
	              control_data,
	              32,
	              data,
	              128,
	              &error_code,
	              &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( WINAPI )
	file_handle = ( (libcfile_internal_file_t *) file )->handle;

	( (libcfile_internal_file_t *) file )->handle = INVALID_HANDLE_VALUE;
#else
	file_descriptor = ( (libcfile_internal_file_t *) file )->descriptor;

	( (libcfile_internal_file_t *) file )->descriptor = -1;
#endif

	read_count = libcfile_internal_file_io_control_read_with_error_code(
	              (libcfile_internal_file_t *) file,
	              0,
	              control_data,
	              32,
	              data,
	              128,
	              &error_code,
	              &error );

#if defined( WINAPI )
	( (libcfile_internal_file_t *) file )->handle = file_handle;
#else
	( (libcfile_internal_file_t *) file )->descriptor = file_descriptor;
#endif

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libcfile_internal_file_io_control_read_with_error_code(
	              (libcfile_internal_file_t *) file,
	              0,
	              NULL,
	              32,
	              data,
	              128,
	              &error_code,
	              &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libcfile_internal_file_io_control_read_with_error_code(
	              (libcfile_internal_file_t *) file,
	              0,
	              control_data,
	              32,
	              NULL,
	              128,
	              &error_code,
	              &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libcfile_internal_file_io_control_read_with_error_code(
	              (libcfile_internal_file_t *) file,
	              0,
	              control_data,
	              32,
	              data,
	              128,
	              NULL,
	              &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_IOCTL )
	read_count = libcfile_internal_file_io_control_read_with_error_code(
	              (libcfile_internal_file_t *) file,
	              0,
	              control_data,
	              0,
	              data,
	              128,
	              &error_code,
	              &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#endif /* defined( HAVE_IOCTL ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) */

/* Tests the libcfile_file_io_control_read function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_io_control_read(
     libcfile_file_t *file )
{
	uint8_t control_data[ 32 ];
	uint8_t data[ 128 ];

	libcerror_error_t *error = NULL;
	ssize_t read_count       = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libcfile_file_is_device(
	          file,
	          &error );

	CFILE_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	if( result == 0 )
	{
/* TODO implement */
	}
	/* Test error cases
	 */
	read_count = libcfile_file_io_control_read(
	              NULL,
	              0,
	              control_data,
	              32,
	              data,
	              128,
	              &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

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

/* Tests the libcfile_file_io_control_read_with_error_code function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_io_control_read_with_error_code(
     libcfile_file_t *file )
{
	uint8_t control_data[ 32 ];
	uint8_t data[ 128 ];

	libcerror_error_t *error = NULL;
	ssize_t read_count       = 0;
	uint32_t error_code      = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libcfile_file_is_device(
	          file,
	          &error );

	CFILE_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	if( result == 0 )
	{
/* TODO implement */
	}
	/* Test error cases
	 */
	read_count = libcfile_file_io_control_read_with_error_code(
	              NULL,
	              0,
	              control_data,
	              32,
	              data,
	              128,
	              &error_code,
	              &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

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

/* Tests the libcfile_file_set_access_behavior function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_set_access_behavior(
     libcfile_file_t *file )
{
	libcerror_error_t *error = NULL;
	size64_t file_size       = 0;
	int result               = 0;

#if defined( WINAPI )
	HANDLE file_handle       = INVALID_HANDLE_VALUE;
#else
	int file_descriptor      = -1;
#endif

	/* Initialize test
	 */
	result = libcfile_file_get_size(
	          file,
	          &file_size,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libcfile_file_set_access_behavior(
	          file,
	          LIBCFILE_ACCESS_BEHAVIOR_NORMAL,
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
	result = libcfile_file_set_access_behavior(
	          NULL,
	          LIBCFILE_ACCESS_BEHAVIOR_NORMAL,
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

#if defined( WINAPI )
	file_handle = ( (libcfile_internal_file_t *) file )->handle;

	( (libcfile_internal_file_t *) file )->handle = INVALID_HANDLE_VALUE;
#else
	file_descriptor = ( (libcfile_internal_file_t *) file )->descriptor;

	( (libcfile_internal_file_t *) file )->descriptor = -1;
#endif

	result = libcfile_file_set_access_behavior(
	          file,
	          LIBCFILE_ACCESS_BEHAVIOR_NORMAL,
	          &error );

#if defined( WINAPI )
	( (libcfile_internal_file_t *) file )->handle = file_handle;
#else
	( (libcfile_internal_file_t *) file )->descriptor = file_descriptor;
#endif

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcfile_file_set_access_behavior(
	          file,
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

#if defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT )

/* Tests the libcfile_internal_file_set_block_size function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_internal_file_set_block_size(
     libcfile_file_t *file )
{
	libcerror_error_t *error = NULL;
	size64_t file_size       = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libcfile_file_get_size(
	          file,
	          &file_size,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libcfile_internal_file_set_block_size(
	          (libcfile_internal_file_t *) file,
	          512,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libcfile_internal_file_set_block_size(
	          (libcfile_internal_file_t *) file,
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
	result = libcfile_internal_file_set_block_size(
	          NULL,
	          512,
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

	result = libcfile_internal_file_set_block_size(
	          (libcfile_internal_file_t *) file,
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

#if defined( HAVE_CFILE_TEST_MEMORY )

	/* Test libcfile_file_initialize with malloc failing
	 */
	cfile_test_malloc_attempts_before_fail = 0;

	result = libcfile_internal_file_set_block_size(
	          (libcfile_internal_file_t *) file,
	          512,
	          &error );

	if( cfile_test_malloc_attempts_before_fail != -1 )
	{
		cfile_test_malloc_attempts_before_fail = -1;
	}
	else
	{
		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		CFILE_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libcfile_file_initialize with memset failing
	 */
	cfile_test_memset_attempts_before_fail = 0;

	result = libcfile_internal_file_set_block_size(
	          (libcfile_internal_file_t *) file,
	          512,
	          &error );

	if( cfile_test_memset_attempts_before_fail != -1 )
	{
		cfile_test_memset_attempts_before_fail = -1;
	}
	else
	{
		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		CFILE_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_CFILE_TEST_MEMORY ) */

	/* Clean up
	 */
	result = libcfile_internal_file_set_block_size(
	          (libcfile_internal_file_t *) file,
	          0,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) */

/* Tests the libcfile_file_set_block_size function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_set_block_size(
     libcfile_file_t *file )
{
	libcerror_error_t *error = NULL;
	size64_t file_size       = 0;
	int result               = 0;

#if defined( WINAPI )
	HANDLE file_handle       = INVALID_HANDLE_VALUE;
#else
	int file_descriptor      = -1;
#endif

	/* Initialize test
	 */
	result = libcfile_file_get_size(
	          file,
	          &file_size,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	if( ( file_size % 512 ) == 0 )
	{
		result = libcfile_file_set_block_size(
		          file,
		          512,
		          &error );

		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		CFILE_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Clean up
		 */
		result = libcfile_file_set_block_size(
		          file,
		          0,
		          &error );

		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		CFILE_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libcfile_file_set_block_size(
	          NULL,
	          512,
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

#if defined( WINAPI )
	file_handle = ( (libcfile_internal_file_t *) file )->handle;

	( (libcfile_internal_file_t *) file )->handle = INVALID_HANDLE_VALUE;
#else
	file_descriptor = ( (libcfile_internal_file_t *) file )->descriptor;

	( (libcfile_internal_file_t *) file )->descriptor = -1;
#endif

	result = libcfile_file_set_block_size(
	          file,
	          512,
	          &error );

#if defined( WINAPI )
	( (libcfile_internal_file_t *) file )->handle = file_handle;
#else
	( (libcfile_internal_file_t *) file )->descriptor = file_descriptor;
#endif

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CFILE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcfile_file_set_block_size(
	          file,
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

	if( ( file_size % 511 ) == 0 )
	{
		result = libcfile_file_set_block_size(
		          NULL,
		          511,
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
	}
	/* Clean up
	 */
	result = libcfile_file_set_block_size(
	          file,
	          0,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libcerror_error_t *error   = NULL;
	libcfile_file_t *file      = NULL;
	system_character_t *source = NULL;
	system_integer_t option    = 0;
	size64_t file_size         = 0;
	int result                 = 0;

	while( ( option = cfile_test_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
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
	 cfile_test_file_initialize );

	CFILE_TEST_RUN(
	 "libcfile_file_free",
	 cfile_test_file_free );

	CFILE_TEST_RUN(
	 "libcfile_file_write_buffer",
	 cfile_test_file_write_buffer );

	CFILE_TEST_RUN(
	 "libcfile_file_write_buffer_with_error_code",
	 cfile_test_file_write_buffer_with_error_code );

	CFILE_TEST_RUN(
	 "libcfile_file_resize",
	 cfile_test_file_resize );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_open",
		 cfile_test_file_open,
		 source );

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_open_with_error_code",
		 cfile_test_file_open_with_error_code,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_open_wide",
		 cfile_test_file_open_wide,
		 source );

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_open_wide_with_error_code",
		 cfile_test_file_open_wide_with_error_code,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

		CFILE_TEST_RUN(
		 "libcfile_file_close",
		 cfile_test_file_close );

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_open_close",
		 cfile_test_file_open_close,
		 source );

		/* Initialize test
		 */
		result = cfile_test_file_open_source(
		          &file,
		          source,
		          &error );

		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        CFILE_TEST_ASSERT_IS_NOT_NULL(
	         "file",
	         file );

	        CFILE_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		result = libcfile_file_get_size(
		          file,
		          &file_size,
		          &error );

		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		CFILE_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		if( ( file_size % 512 ) == 0 )
		{
			/* Test with block size if possible
			 */
			result = libcfile_file_set_block_size(
			          file,
			          512,
			          &error );

			CFILE_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 1 );

		        CFILE_TEST_ASSERT_IS_NULL(
		         "error",
		         error );
		}
		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_seek_offset",
		 cfile_test_file_seek_offset,
		 file );

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_read_buffer",
		 cfile_test_file_read_buffer,
		 file );

#if defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) && defined( WINAPI )

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_internal_file_read_buffer_at_offset_with_error_code",
		 cfile_test_internal_file_read_buffer_at_offset_with_error_code,
		 file );

#endif /* defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) && defined( WINAPI ) */

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_read_buffer_with_error_code",
		 cfile_test_file_read_buffer_with_error_code,
		 file );

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_is_open",
		 cfile_test_file_is_open,
		 file );

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_get_offset",
		 cfile_test_file_get_offset,
		 file );

#if defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT )

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_internal_file_get_size",
		 cfile_test_internal_file_get_size,
		 file );

#endif /* defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) */

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_get_size",
		 cfile_test_file_get_size,
		 file );

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_is_device",
		 cfile_test_file_is_device,
		 file );

#if defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT )

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_internal_file_io_control_read_with_error_code",
		 cfile_test_internal_file_io_control_read_with_error_code,
		 file );

#endif /* defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) */

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_io_control_read",
		 cfile_test_file_io_control_read,
		 file );

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_io_control_read_with_error_code",
		 cfile_test_file_io_control_read_with_error_code,
		 file );

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_set_access_behavior",
		 cfile_test_file_set_access_behavior,
		 file );

#if defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT )

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_internal_file_set_block_size",
		 cfile_test_internal_file_set_block_size,
		 file );

#endif /* defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) */

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_set_block_size",
		 cfile_test_file_set_block_size,
		 file );

		/* Clean up
		 */
		result = cfile_test_file_close_source(
		          &file,
		          &error );

		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		CFILE_TEST_ASSERT_IS_NULL(
	         "file",
	         file );

	        CFILE_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		cfile_test_file_close_source(
		 &file,
		 NULL );
	}
	return( EXIT_FAILURE );
}

