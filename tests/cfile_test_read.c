/*
 * Library read testing program
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

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "cfile_test_libcerror.h"
#include "cfile_test_libcfile.h"
#include "cfile_test_libcstring.h"
#include "cfile_test_macros.h"
#include "cfile_test_unused.h"

/* Define to make cfile_test_read generate verbose output
#define CFILE_TEST_READ_VERBOSE
 */

#define CFILE_TEST_READ_BUFFER_SIZE	4096

/* Tests reading data at a specific offset
 * Returns 1 if successful or 0 if not
 */
int cfile_test_seek_offset_and_read_buffer(
     libcfile_file_t *file,
     off64_t input_offset,
     int input_whence,
     size64_t input_size,
     off64_t expected_offset,
     size64_t expected_size )
{
	uint8_t buffer[ CFILE_TEST_READ_BUFFER_SIZE ];

	libcerror_error_t *error = NULL;
	off64_t result_offset    = 0;
	size64_t remaining_size  = 0;
	size64_t result_size     = 0;
	size_t read_size         = 0;
	ssize_t read_count       = 0;

	result_offset = libcfile_file_seek_offset(
	                 file,
	                 input_offset,
	                 input_whence,
	                 &error );

	CFILE_TEST_ASSERT_EQUAL_INT64(
	 "result_offset",
	 result_offset,
	 expected_offset );

        CFILE_TEST_ASSERT_IS_NULL(
         "error",
         error );

	remaining_size = input_size;

	while( remaining_size > 0 )
	{
		if( remaining_size < (size64_t) read_size )
		{
			read_size = (size_t) remaining_size;
		}
		else
		{
			read_size = CFILE_TEST_READ_BUFFER_SIZE;
		}
		read_count = libcfile_file_read_buffer(
			      file,
			      buffer,
			      read_size,
			      &error );

		if( read_count <= 0 )
		{
			break;
		}
		remaining_size -= (size64_t) read_count;
		result_size    += (size64_t) read_count;
	}
	CFILE_TEST_ASSERT_EQUAL_UINT64(
	 "result_size",
	 result_size,
	 expected_size );

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

/* Tests reading data from a file
 * Returns 1 if successful or 0 if not
 */
int cfile_test_read_from_file(
     libcfile_file_t *file )
{
	libcerror_error_t *error = NULL;
	off64_t read_offset      = 0;
	size64_t file_size       = 0;
	size64_t read_size       = 0;
	int result               = 0;

	result = libcfile_file_get_size(
	          file,
	          &file_size,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CFILE_TEST_ASSERT_LESS_THAN_UINT64(
	 "file_size",
	 file_size,
	 (size64_t) INT64_MAX );

	/* Case 0: test full read
	 */

	/* Test: offset: 0 size: <file_size>
	 * Expected result: offset: 0 size: <file_size>
	 */
	read_offset = 0;
	read_size   = file_size;

	result = cfile_test_seek_offset_and_read_buffer(
	          file,
	          read_offset,
	          SEEK_SET,
	          read_size,
	          read_offset,
	          read_size );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = cfile_test_seek_offset_and_read_buffer(
	          file,
	          read_offset,
	          SEEK_SET,
	          read_size,
	          read_offset,
	          read_size );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	/* Case 1: test buffer at offset read
	 */

	/* Test: offset: <file_size / 7> size: <file_size / 2>
	 * Expected result: offset: <file_size / 7> size: <file_size / 2>
	 */
	read_offset = (off64_t) ( file_size / 7 );
	read_size   = file_size / 2;

	result = cfile_test_seek_offset_and_read_buffer(
	          file,
	          read_offset,
	          SEEK_SET,
	          read_size,
	          read_offset,
	          read_size );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = cfile_test_seek_offset_and_read_buffer(
	          file,
	          read_offset,
	          SEEK_SET,
	          read_size,
	          read_offset,
	          read_size );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	/* Case 2: test read beyond file size
	 */
	read_offset = (off64_t) ( file_size - 1024 );
	read_size   = 4096;

	if( file_size >= 1024 )
	{
		/* Test: offset: <file_size - 1024> size: 4096
		 * Expected result: offset: <file_size - 1024> size: 1024
		 */
		result = cfile_test_seek_offset_and_read_buffer(
		          file,
		          read_offset,
		          SEEK_SET,
		          read_size,
		          read_offset,
		          1024 );

		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		result = cfile_test_seek_offset_and_read_buffer(
		          file,
		          read_offset,
		          SEEK_SET,
		          read_size,
		          read_offset,
		          1024 );

		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );
	}

#ifdef TODO
		/* Test: offset: <file_size - 1024> size: 4096
		 * Expected result: offset: -1 size: <undetermined>
		 */
		result = cfile_test_seek_offset_and_read_buffer(
		          file,
		          read_offset,
		          SEEK_SET,
		          read_size,
		          -1,
		          (size64_t) -1 );

		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		result = cfile_test_seek_offset_and_read_buffer(
		          file,
		          read_offset,
		          SEEK_SET,
		          read_size,
		          -1,
		          (size64_t) -1 );

		CFILE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );
#endif
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests reading a file
 * Returns 1 if successful or 0 if not
 */
int cfile_test_read(
     libcstring_system_character_t *source )
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

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
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

	/* Test reading file
	 */
	result = cfile_test_read_from_file(
	          file );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	/* Clean up
	 */
	result = libcfile_file_close(
	          file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = libcfile_file_free(
	          &file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	return( 1 );

on_error:
	if( file != NULL )
	{
		libcfile_file_close(
		 file,
		 NULL );
		libcfile_file_free(
		 &file,
		 NULL );
	}
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests reading a file with a block size
 * Returns 1 if successful, 0 if not or -1 on error
 */
int cfile_test_read_with_block_size(
     libcstring_system_character_t *source )
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

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
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

	result = libcfile_file_set_block_size(
	          file,
	          512,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	/* Test reading file
	 */
	result = cfile_test_read_from_file(
	          file );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	/* Clean up
	 */
	result = libcfile_file_close(
	          file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = libcfile_file_free(
	          &file,
	          &error );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	return( 1 );

on_error:
	if( file != NULL )
	{
		libcfile_file_close(
		 file,
		 NULL );
		libcfile_file_free(
		 &file,
		 NULL );
	}
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

	if( argc < 2 )
	{
		fprintf(
		 stderr,
		 "Missing filename.\n" );

		return( EXIT_FAILURE );
	}
	source = argv[ 1 ];

#if defined( HAVE_DEBUG_OUTPUT ) && defined( CFILE_TEST_READ_VERBOSE )
	libcfile_notify_set_verbose(
	 1 );
	libcfile_notify_set_stream(
	 stderr,
	 NULL );
#endif

#if defined( __BORLANDC__ ) && ( __BORLANDC__ < 0x0560 )
	/* Return exit ignore
	 */
	return( 77 );

#else
	CFILE_TEST_RUN_WITH_ARGS(
	 "read",
	 cfile_test_read,
	 source );

	CFILE_TEST_RUN_WITH_ARGS(
	 "read with block size",
	 cfile_test_read_with_block_size,
	 source );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __BORLANDC__ ) && ( __BORLANDC__ < 0x0560 ) */
}

