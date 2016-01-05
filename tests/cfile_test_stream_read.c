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

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include <stdio.h>

#include "cfile_test_libcstring.h"
#include "cfile_test_libcerror.h"
#include "cfile_test_libcfile.h"
#include "cfile_test_unused.h"

/* Define to make cfile_test_read generate verbose output
#define CFILE_TEST_READ_VERBOSE
 */

#define CFILE_TEST_READ_BUFFER_SIZE	4096

/* Tests libcfile_file_seek_offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int cfile_stream_test_seek_offset(
     libcfile_stream_t *stream,
     off64_t input_offset,
     int input_whence,
     off64_t expected_offset )
{
	libcerror_error_t *error = NULL;
	off64_t result_offset    = 0;
	int result               = 0;

	if( stream == NULL )
	{
		return( -1 );
	}
	result_offset = libcfile_stream_seek_offset(
	                 stream,
	                 input_offset,
	                 input_whence,
	                 &error );

	if( expected_offset != result_offset )
	{
		fprintf(
		 stderr,
		 "Unexpected result offset: %" PRIi64 "\n",
		 result_offset );
	}
	else
	{
		result = 1;
	}
	if( error != NULL )
	{
		if( result != 1 )
		{
			libcerror_error_backtrace_fprint(
			 error,
			 stderr );
		}
		libcerror_error_free(
		 &error );
	}
	return( result );
}

/* Tests libcfile_stream_read_buffer
 * Returns 1 if successful, 0 if not or -1 on error
 */
int cfile_stream_test_read_buffer(
     libcfile_stream_t *stream,
     size64_t input_size,
     size64_t expected_size )
{
	uint8_t buffer[ CFILE_TEST_READ_BUFFER_SIZE ];

	libcerror_error_t *error = NULL;
	size64_t remaining_size  = 0;
	size64_t result_size     = 0;
	size_t read_size         = 0;
	ssize_t read_count       = 0;
	int result               = 0;

	if( stream == NULL )
	{
		return( -1 );
	}
	remaining_size = input_size;

	while( remaining_size > 0 )
	{
		read_size = CFILE_TEST_READ_BUFFER_SIZE;

		if( remaining_size < (size64_t) read_size )
		{
			read_size = (size_t) remaining_size;
		}
		read_count = libcfile_stream_read_buffer(
			      stream,
			      buffer,
			      read_size,
			      &error );

		if( read_count < 0 )
		{
			break;
		}
		remaining_size -= (size64_t) read_count;
		result_size    += (size64_t) read_count;

		if( read_count != (ssize_t) read_size )
		{
			break;
		}
	}
	if( expected_size != result_size )
	{
		fprintf(
		 stderr,
		 "Unexpected read count: %" PRIu64 "\n",
		 result_size );
	}
	else
	{
		result = 1;
	}
	if( error != NULL )
	{
		if( result != 1 )
		{
			libcerror_error_backtrace_fprint(
			 error,
			 stderr );
		}
		libcerror_error_free(
		 &error );
	}
	return( result );
}

#ifdef TODO

/* Tests libcfile_stream_read_buffer_at_offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int cfile_stream_test_read_buffer_at_offset(
     libcfile_stream_t *stream,
     off64_t input_offset,
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
	int result               = 0;

	if( stream == NULL )
	{
		return( -1 );
	}
	remaining_size = input_size;

	fprintf(
	 stdout,
	 "Testing reading buffer at offset: %" PRIi64 " and size: %" PRIu64 "\t",
	 input_offset,
	 input_size );

	while( remaining_size > 0 )
	{
		read_size = CFILE_TEST_READ_BUFFER_SIZE;

		if( remaining_size < (size64_t) read_size )
		{
			read_size = (size_t) remaining_size;
		}
		read_count = libcfile_stream_read_buffer_at_offset(
			      stream,
			      buffer,
			      read_size,
			      input_offset,
			      &error );

		if( read_count < 0 )
		{
			break;
		}
		input_offset   += (size64_t) read_count;
		remaining_size -= (size64_t) read_count;
		result_size    += (size64_t) read_count;

		if( read_count != (ssize_t) read_size )
		{
			break;
		}
	}
	if( libcfile_stream_get_offset(
	     stream,
	     &result_offset,
	     &error ) != 1 )
	{
		result = -1;
	}
	if( expected_offset != result_offset )
	{
		fprintf(
		 stderr,
		 "Unexpected offset: %" PRIi64 "\n",
		 result_offset );
	}
	else if( expected_size != result_size )
	{
		fprintf(
		 stderr,
		 "Unexpected read count: %" PRIu64 "\n",
		 result_size );
	}
	else
	{
		result = 1;
	}
	if( result == 1 )
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( error != NULL )
	{
		if( result != 1 )
		{
			libcerror_error_backtrace_fprint(
			 error,
			 stderr );
		}
		libcerror_error_free(
		 &error );
	}
	return( result );
}

#endif /* TODO */

/* Tests reading data at a specific offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int cfile_stream_test_seek_offset_and_read_buffer(
     libcfile_stream_t *stream,
     off64_t input_offset,
     int input_whence,
     size64_t input_size,
     off64_t expected_offset,
     size64_t expected_size )
{
	const char *whence_string = NULL;
	int result                = 0;

	if( stream == NULL )
	{
		return( -1 );
	}
	if( input_whence == SEEK_CUR )
	{
		whence_string = "SEEK_CUR";
	}
	else if( input_whence == SEEK_END )
	{
		whence_string = "SEEK_END";
	}
	else if( input_whence == SEEK_SET )
	{
		whence_string = "SEEK_SET";
	}
	else
	{
		whence_string = "UNKNOWN";
	}
	fprintf(
	 stdout,
	 "Testing reading buffer at offset: %" PRIi64 ", whence: %s and size: %" PRIu64 "\t",
	 input_offset,
	 whence_string,
	 input_size );

	result = cfile_stream_test_seek_offset(
	          stream,
	          input_offset,
	          input_whence,
	          expected_offset );

	if( result == 1 )
	{
		if( input_offset >= 0 )
		{
			result = cfile_stream_test_read_buffer(
				  stream,
				  input_size,
				  expected_size );
		}
	}
	if( result == 1 )
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	return( result );
}

/* Tests reading data from a stream
 * Returns 1 if successful, 0 if not or -1 on error
 */
int cfile_stream_test_read_from_stream(
     libcfile_stream_t *stream,
     size64_t stream_size )
{
	int result = 0;

	if( stream == NULL )
	{
		return( -1 );
	}
	if( stream_size > (size64_t) INT64_MAX )
	{
		fprintf(
		 stderr,
		 "Stream size exceeds maximum.\n" );

		return( -1 );
	}
	/* Case 0: test full read
	 */

	/* Test: offset: 0 size: <stream_size>
	 * Expected result: offset: 0 size: <stream_size>
	 */
	result = cfile_stream_test_seek_offset_and_read_buffer(
	          stream,
	          0,
	          SEEK_SET,
	          stream_size,
	          0,
	          stream_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset and read buffer.\n" );

		return( result );
	}
	/* Test: offset: 0 size: <stream_size>
	 * Expected result: offset: 0 size: <stream_size>
	 */
	result = cfile_stream_test_seek_offset_and_read_buffer(
	          stream,
	          0,
	          SEEK_SET,
	          stream_size,
	          0,
	          stream_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset and read buffer.\n" );

		return( result );
	}

	/* Case 1: test buffer at offset read
	 */

	/* Test: offset: <stream_size / 7> size: <stream_size / 2>
	 * Expected result: offset: <stream_size / 7> size: <stream_size / 2>
	 */
	result = cfile_stream_test_seek_offset_and_read_buffer(
	          stream,
	          (off64_t) ( stream_size / 7 ),
	          SEEK_SET,
	          stream_size / 2,
	          (off64_t) ( stream_size / 7 ),
	          stream_size / 2 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset and read buffer.\n" );

		return( result );
	}
	/* Test: offset: <stream_size / 7> size: <stream_size / 2>
	 * Expected result: offset: <stream_size / 7> size: <stream_size / 2>
	 */
	result = cfile_stream_test_seek_offset_and_read_buffer(
	          stream,
	          (off64_t) ( stream_size / 7 ),
	          SEEK_SET,
	          stream_size / 2,
	          (off64_t) ( stream_size / 7 ),
	          stream_size / 2 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset and read buffer.\n" );

		return( result );
	}

	/* Case 2: test read beyond stream size
	 */

	if( stream_size < 1024 )
	{
		/* Test: offset: <stream_size - 1024> size: 4096
		 * Expected result: offset: -1 size: <undetermined>
		 */
		result = cfile_stream_test_seek_offset_and_read_buffer(
		          stream,
		          (off64_t) ( stream_size - 1024 ),
		          SEEK_SET,
		          4096,
		          -1,
		          (size64_t) -1 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset and read buffer.\n" );

			return( result );
		}
		/* Test: offset: <stream_size - 1024> size: 4096
		 * Expected result: offset: -1 size: <undetermined>
		 */
		result = cfile_stream_test_seek_offset_and_read_buffer(
		          stream,
		          (off64_t) ( stream_size - 1024 ),
		          SEEK_SET,
		          4096,
		          -1,
		          (size64_t) -1 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset and read buffer.\n" );

			return( result );
		}
	}
	else
	{
		/* Test: offset: <stream_size - 1024> size: 4096
		 * Expected result: offset: <stream_size - 1024> size: 1024
		 */
		result = cfile_stream_test_seek_offset_and_read_buffer(
		          stream,
		          (off64_t) ( stream_size - 1024 ),
		          SEEK_SET,
		          4096,
		          (off64_t) ( stream_size - 1024 ),
		          1024 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test read.\n" );

			return( result );
		}
		/* Test: offset: <stream_size - 1024> size: 4096
		 * Expected result: offset: <stream_size - 1024> size: 1024
		 */
		result = cfile_stream_test_seek_offset_and_read_buffer(
		          stream,
		          (off64_t) ( stream_size - 1024 ),
		          SEEK_SET,
		          4096,
		          (off64_t) ( stream_size - 1024 ),
		          1024 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset and read buffer.\n" );

			return( result );
		}
	}
#ifdef TODO
	/* Case 3: test buffer at offset read
	 */

	/* Test: offset: <stream_size / 7> size: <stream_size / 2>
	 * Expected result: offset: < ( stream_size / 7 ) + ( stream_size / 2 ) > size: <stream_size / 2>
	 */
	result = cfile_stream_test_read_buffer_at_offset(
	          stream,
	          (off64_t) ( stream_size / 7 ),
	          stream_size / 2,
	          (off64_t) ( stream_size / 7 ) + ( stream_size / 2 ),
	          stream_size / 2 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read buffer at offset.\n" );

		return( result );
	}
	/* Test: offset: <stream_size / 7> size: <stream_size / 2>
	 * Expected result: offset: < ( stream_size / 7 ) + ( stream_size / 2 ) > size: <stream_size / 2>
	 */
	result = cfile_stream_test_read_buffer_at_offset(
	          stream,
	          (off64_t) ( stream_size / 7 ),
	          stream_size / 2,
	          (off64_t) ( stream_size / 7 ) + ( stream_size / 2 ),
	          stream_size / 2 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read buffer at offset.\n" );

		return( result );
	}
#endif /* TODO */
	return( 1 );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libcerror_error_t *error              = NULL;
	libcfile_stream_t *stream             = NULL;
	libcstring_system_character_t *source = NULL;
	size64_t stream_size                  = 0;

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
	/* Test stream read
	 */
	if( libcfile_stream_initialize(
	     &stream,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to create stream.\n" );

		goto on_error;
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( libcfile_stream_open_wide(
	     stream,
	     source,
	     LIBCFILE_OPEN_READ,
	     &error ) != 1 )
#else
	if( libcfile_stream_open(
	     stream,
	     source,
	     LIBCFILE_OPEN_READ,
	     &error ) != 1 )
#endif
	{
		fprintf(
		 stderr,
		 "Unable to open stream.\n" );

		goto on_error;
	}
	if( libcfile_stream_get_size(
	     stream,
	     &stream_size,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve stream size.\n" );

		goto on_error;
	}
	fprintf(
	 stdout,
	 "Stream size: %" PRIu64 " bytes\n",
	 stream_size );

	if( cfile_stream_test_read_from_stream(
	     stream,
	     stream_size ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to read from stream.\n" );

		goto on_error;
	}
	if( libcfile_stream_close(
	     stream,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close stream.\n" );

		goto on_error;
	}
	if( libcfile_stream_free(
	     &stream,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free stream.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_backtrace_fprint(
		 error,
		 stderr );
		libcerror_error_free(
		 &error );
	}
	if( stream != NULL )
	{
		libcfile_stream_close(
		 stream,
		 NULL );
		libcfile_stream_free(
		 &stream,
		 NULL );
	}
	return( EXIT_FAILURE );
}

