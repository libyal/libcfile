/*
 * Library file seek testing program
 *
 * Copyright (c) 2008-2014, Joachim Metz <joachim.metz@gmail.com>
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

#include "cfile_test_libcerror.h"
#include "cfile_test_libcfile.h"
#include "cfile_test_libcstring.h"

/* Tests libcfile_stream_seek_offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int cfile_stream_test_seek_offset(
     libcfile_stream_t *stream,
     off64_t input_offset,
     int input_whence,
     off64_t output_offset )
{
	const char *whence_string = NULL;
	libcerror_error_t *error  = NULL;
	off64_t result_offset     = 0;
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
	 "Testing seek of offset: %" PRIi64 " and whence: %s\t",
	 input_offset,
	 whence_string );

	result_offset = libcfile_stream_seek_offset(
	                 stream,
	                 input_offset,
	                 input_whence,
	                 &error );

	if( result_offset == -1 )
	{
		libcfile_error_backtrace_fprint(
		 error,
		 stderr );

		libcfile_error_free(
		 &error );
	}
	if( result_offset == output_offset )
	{
		result = 1;
	}
	if( result != 0 )
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

/* Tests seeking in a stream
 * Returns 1 if successful, 0 if not or -1 on error
 */
int cfile_stream_test_seek_stream(
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
	/* Test: SEEK_SET offset: 0
	 * Expected result: 0
	 */
	result = cfile_stream_test_seek_offset(
	          stream,
	          0,
	          SEEK_SET,
	          0 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: <stream_size>
	 * Expected result: <stream_size>
	 */
	if( cfile_stream_test_seek_offset(
	     stream,
	     (off64_t) stream_size,
	     SEEK_SET,
	     (off64_t) stream_size ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: <stream_size / 5>
	 * Expected result: <stream_size / 5>
	 */
	if( cfile_stream_test_seek_offset(
	     stream,
	     (off64_t) ( stream_size / 5 ),
	     SEEK_SET,
	     (off64_t) ( stream_size / 5 ) ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: <stream_size + 987>
	 * Expected result: <stream_size + 987>
	 */
	if( cfile_stream_test_seek_offset(
	     stream,
	     (off64_t) ( stream_size + 987 ),
	     SEEK_SET,
	     (off64_t) ( stream_size + 987 ) ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: -987
	 * Expected result: -1
	 */
	if( cfile_stream_test_seek_offset(
	     stream,
	     -987,
	     SEEK_SET,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_CUR offset: 0
	 * Expected result: <stream_size + 987>
	 */
	if( cfile_stream_test_seek_offset(
	     stream,
	     0,
	     SEEK_CUR,
	     (off64_t) ( stream_size + 987 ) ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_CUR offset: <-1 * (stream_size + 987)>
	 * Expected result: 0
	 */
	if( cfile_stream_test_seek_offset(
	     stream,
	     -1 * (off64_t) ( stream_size + 987 ),
	     SEEK_CUR,
	     0 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_CUR offset: <stream_size / 3>
	 * Expected result: <stream_size / 3>
	 */
	if( cfile_stream_test_seek_offset(
	     stream,
	     (off64_t) ( stream_size / 3 ),
	     SEEK_CUR,
	     (off64_t) ( stream_size / 3 ) ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	if( stream_size == 0 )
	{
		/* Test: SEEK_CUR offset: <-2 * (stream_size / 3)>
		 * Expected result: 0
		 */
		if( cfile_stream_test_seek_offset(
		     stream,
		     -2 * (off64_t) ( stream_size / 3 ),
		     SEEK_CUR,
		     0 ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset.\n" );

			return( result );
		}
	}
	else
	{
		/* Test: SEEK_CUR offset: <-2 * (stream_size / 3)>
		 * Expected result: -1
		 */
		if( cfile_stream_test_seek_offset(
		     stream,
		     -2 * (off64_t) ( stream_size / 3 ),
		     SEEK_CUR,
		     -1 ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset.\n" );

			return( result );
		}
	}
	/* Test: SEEK_END offset: 0
	 * Expected result: <stream_size>
	 */
	if( cfile_stream_test_seek_offset(
	     stream,
	     0,
	     SEEK_END,
	     (off64_t) stream_size ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: <-1 * stream_size>
	 * Expected result: 0
	 */
	if( cfile_stream_test_seek_offset(
	     stream,
	     -1 * (off64_t) stream_size,
	     SEEK_END,
	     0 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: <-1 * (stream_size / 4)>
	 * Expected result: <stream_size - (stream_size / 4)>
	 */
	if( cfile_stream_test_seek_offset(
	     stream,
	     -1 * (off64_t) ( stream_size / 4 ),
	     SEEK_END,
	     (off64_t) stream_size - (off64_t) ( stream_size / 4 ) ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: 542
	 * Expected result: <stream_size + 542>
	 */
	if( cfile_stream_test_seek_offset(
	     stream,
	     542,
	     SEEK_END,
	     (off64_t) ( stream_size + 542 ) ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: <-1 * (stream_size + 542)>
	 * Expected result: -1
	 */
	if( cfile_stream_test_seek_offset(
	     stream,
	     -1 * (off64_t) ( stream_size + 542 ),
	     SEEK_END,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: UNKNOWN (88) offset: 0
	 * Expected result: -1
	 */
	if( cfile_stream_test_seek_offset(
	     stream,
	     0,
	     88,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	return( result );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libcerror_error_t *error  = NULL;
	libcfile_stream_t *stream = NULL;
	size64_t stream_size      = 0;

	if( argc != 2 )
	{
		fprintf(
		 stderr,
		 "Unsupported number of arguments.\n" );

		return( EXIT_FAILURE );
	}
	/* Test stream seek
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
	     argv[ 1 ],
	     LIBCFILE_OPEN_READ,
	     &error ) != 1 )
#else
	if( libcfile_stream_open(
	     stream,
	     argv[ 1 ],
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
	if( cfile_stream_test_seek_stream(
	     stream,
	     stream_size ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to seek in stream.\n" );

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
		libcfile_error_backtrace_fprint(
		 error,
		 stderr );
		libcfile_error_free(
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

