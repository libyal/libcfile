/*
 * Library file type test program
 *
 * Copyright (C) 2008-2018, Joachim Metz <joachim.metz@gmail.com>
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
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "cfile_test_getopt.h"
#include "cfile_test_libcerror.h"
#include "cfile_test_libcfile.h"
#include "cfile_test_libclocale.h"
#include "cfile_test_libuna.h"
#include "cfile_test_macros.h"
#include "cfile_test_memory.h"

#include "../libcfile/libcfile_file.h"

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make cfile_test_file generate verbose output
#define CFILE_TEST_FILE_VERBOSE
 */

/* Retrieves source as a narrow string
 * Returns 1 if successful or -1 on error
 */
int cfile_test_file_get_narrow_source(
     const system_character_t *source,
     char *narrow_string,
     size_t narrow_string_size,
     libcerror_error_t **error )
{
	static char *function     = "cfile_test_file_get_narrow_source";
	size_t narrow_source_size = 0;
	size_t source_length      = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result                = 0;
#endif

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
	if( narrow_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid narrow string.",
		 function );

		return( -1 );
	}
	if( narrow_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid narrow string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	source_length = system_string_length(
	                 source );

	if( source_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid source length value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          &narrow_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          &narrow_source_size,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &narrow_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &narrow_source_size,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine narrow string size.",
		 function );

		return( -1 );
	}
#else
	narrow_source_size = source_length + 1;

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( narrow_string_size < narrow_source_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: narrow string too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_copy_from_utf32(
		          (libuna_utf8_character_t *) narrow_string,
		          narrow_string_size,
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_copy_from_utf16(
		          (libuna_utf8_character_t *) narrow_string,
		          narrow_string_size,
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_copy_from_utf32(
		          (uint8_t *) narrow_string,
		          narrow_string_size,
		          libclocale_codepage,
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_copy_from_utf16(
		          (uint8_t *) narrow_string,
		          narrow_string_size,
		          libclocale_codepage,
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set narrow string.",
		 function );

		return( -1 );
	}
#else
	if( system_string_copy(
	     narrow_string,
	     source,
	     source_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set narrow string.",
		 function );

		return( -1 );
	}
	narrow_string[ source_length ] = 0;

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Retrieves source as a wide string
 * Returns 1 if successful or -1 on error
 */
int cfile_test_file_get_wide_source(
     const system_character_t *source,
     wchar_t *wide_string,
     size_t wide_string_size,
     libcerror_error_t **error )
{
	static char *function   = "cfile_test_file_get_wide_source";
	size_t source_length    = 0;
	size_t wide_source_size = 0;

#if !defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result              = 0;
#endif

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
	if( wide_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid wide string.",
		 function );

		return( -1 );
	}
	if( wide_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid wide string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	source_length = system_string_length(
	                 source );

	if( source_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid source length value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	wide_source_size = source_length + 1;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_utf8(
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          &wide_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_utf8(
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          &wide_source_size,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_byte_stream(
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &wide_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_byte_stream(
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &wide_source_size,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine wide string size.",
		 function );

		return( -1 );
	}

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( wide_string_size < wide_source_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: wide string too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( system_string_copy(
	     wide_string,
	     source,
	     source_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set wide string.",
		 function );

		return( -1 );
	}
	wide_string[ source_length ] = 0;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_utf8(
		          (libuna_utf32_character_t *) wide_string,
		          wide_string_size,
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_utf8(
		          (libuna_utf16_character_t *) wide_string,
		          wide_string_size,
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_byte_stream(
		          (libuna_utf32_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_byte_stream(
		          (libuna_utf16_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set wide string.",
		 function );

		return( -1 );
	}

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

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

#if defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) && defined( WINAPI ) && ( WINVER <= 0x0500 )

/* Tests the libcfile_CloseHandle function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_libcfile_CloseHandle(
     void )
{
	HANDLE library_handle = NULL;
	BOOL result           = FALSE;

	/* Test regular cases
	 */
#ifdef TODO
	library_handle = LoadLibrary(
	                  _SYSTEM_STRING( "kernel32.dll" ) );

	result = libcfile_CloseHandle(
	          library_handle );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 TRUE );
#endif

	/* Test error cases
	 */
	result = libcfile_CloseHandle(
	          NULL );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 FALSE );

	return( 1 );

on_error:
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) && defined( WINAPI ) && ( WINVER <= 0x0500 ) */

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

#if defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) && defined( WINAPI ) && ( WINVER <= 0x0500 )

/* Tests the libcfile_CreateFileA function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_libcfile_CreateFileA(
     void )
{
	HANDLE result = INVALID_HANDLE_VALUE;

	/* Test error cases
	 */
	result = libcfile_CreateFileA(
	          NULL,
	          0,
	          0,
	          NULL,
	          0,
	          0,
	          NULL );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 INVALID_HANDLE_VALUE );

	return( 1 );

on_error:
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) && defined( WINAPI ) && ( WINVER <= 0x0500 ) */

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
	result = cfile_test_file_get_narrow_source(
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

	/* Test open
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
	result = cfile_test_file_get_narrow_source(
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

	/* Test open
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
	          -1,
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

#if defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) && defined( WINAPI ) && ( WINVER <= 0x0500 )

/* Tests the libcfile_CreateFileW function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_libcfile_CreateFileW(
     void )
{
	HANDLE result = INVALID_HANDLE_VALUE;

	/* Test error cases
	 */
	result = libcfile_CreateFileW(
	          NULL,
	          0,
	          0,
	          NULL,
	          0,
	          0,
	          NULL );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 INVALID_HANDLE_VALUE );

	return( 1 );

on_error:
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) && defined( WINAPI ) && ( WINVER <= 0x0500 ) */

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
	result = cfile_test_file_get_wide_source(
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

	/* Test open
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
	result = cfile_test_file_get_wide_source(
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

	/* Test open
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
	          -1,
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
	uint8_t buffer[ 4 ];

	libcerror_error_t *error = NULL;
	ssize_t read_count       = 0;

	read_count = libcfile_file_read_buffer(
	              file,
	              buffer,
	              0,
	              &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 0 );

	CFILE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	read_count = libcfile_file_read_buffer(
	              NULL,
	              buffer,
	              0,
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

#if defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT )
#if defined( WINAPI ) && ( WINVER <= 0x0500 )

/* Tests the libcfile_GetOverlappedResult function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_libcfile_GetOverlappedResult(
     void )
{
	BOOL result = FALSE;

	/* Test error cases
	 */
	result = libcfile_GetOverlappedResult(
	          NULL,
	          NULL,
	          NULL,
	          0 );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 FALSE );

	return( 1 );

on_error:
	return( 0 );
}

/* Tests the libcfile_ReadFile function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_libcfile_ReadFile(
     void )
{
	BOOL result = FALSE;

	/* Test error cases
	 */
	result = libcfile_ReadFile(
	          NULL,
	          NULL,
	          0,
	          NULL,
	          NULL );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 FALSE );

	return( 1 );

on_error:
	return( 0 );
}

#endif /* defined( WINAPI ) && ( WINVER <= 0x0500 ) */

#if defined( WINAPI )

/* TODO: add test for libcfile_internal_file_read_buffer_at_offset_with_error_code */

#endif /* defined( WINAPI ) */

#endif /* defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) */

/* Tests the libcfile_file_read_buffer_with_error_code function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_read_buffer_with_error_code(
     libcfile_file_t *file )
{
	uint8_t buffer[ 4 ];

	libcerror_error_t *error     = NULL;
	libcfile_file_t *closed_file = NULL;
	ssize_t read_count           = 0;
	uint32_t error_code          = 0;
	int result                   = 0;

	read_count = libcfile_file_read_buffer_with_error_code(
	              file,
	              buffer,
	              0,
	              &error_code,
	              &error );

	CFILE_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 0 );

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

/* Tests the libcfile_file_is_open function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_is_open(
     libcfile_file_t *file )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

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

/* Tests the libcfile_file_get_size function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_file_get_size(
     libcfile_file_t *file )
{
	libcerror_error_t *error = NULL;
	size64_t size            = 0;
	int result               = 0;

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

#if defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) && defined( WINAPI ) && ( WINVER <= 0x0500 )

	CFILE_TEST_RUN(
	 "libcfile_CloseHandle",
	 cfile_test_libcfile_CloseHandle );

#endif /* defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) && defined( WINAPI ) && ( WINVER <= 0x0500 ) */

	CFILE_TEST_RUN(
	 "libcfile_file_initialize",
	 cfile_test_file_initialize );

	CFILE_TEST_RUN(
	 "libcfile_file_free",
	 cfile_test_file_free );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
#if defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) && defined( WINAPI ) && ( WINVER <= 0x0500 )

		CFILE_TEST_RUN(
		 "libcfile_CreateFileA",
		 cfile_test_libcfile_CreateFileA );

#endif /* defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) && defined( WINAPI ) && ( WINVER <= 0x0500 ) */

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_open",
		 cfile_test_file_open,
		 source );

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_open_with_error_code",
		 cfile_test_file_open_with_error_code,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

#if defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) && defined( WINAPI ) && ( WINVER <= 0x0500 )

		CFILE_TEST_RUN(
		 "libcfile_CreateFileW",
		 cfile_test_libcfile_CreateFileW );

#endif /* defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) && defined( WINAPI ) && ( WINVER <= 0x0500 ) */

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_open_wide",
		 cfile_test_file_open_wide,
		 source );

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_open_wide_with_error_code",
		 cfile_test_file_open_wide_with_error_code,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBCFILE_HAVE_BFIO )

		/* TODO add test for libcfile_file_open_file_io_handle */

#endif /* defined( LIBCFILE_HAVE_BFIO ) */

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

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_seek_offset",
		 cfile_test_file_seek_offset,
		 file );

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_read_buffer",
		 cfile_test_file_read_buffer,
		 file );

#if defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT )
#if defined( WINAPI ) && ( WINVER <= 0x0500 )

		CFILE_TEST_RUN(
		 "libcfile_GetOverlappedResult",
		 cfile_test_libcfile_GetOverlappedResult );

		CFILE_TEST_RUN(
		 "libcfile_ReadFile",
		 cfile_test_libcfile_ReadFile );

#endif /* defined( WINAPI ) && ( WINVER <= 0x0500 ) */

#if defined( WINAPI )

		/* TODO: add test for libcfile_internal_file_read_buffer_at_offset_with_error_code */

#endif /* defined( WINAPI ) */
#endif /* defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) */

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_read_buffer_with_error_code",
		 cfile_test_file_read_buffer_with_error_code,
		 file );

		/* TODO: add test for libcfile_file_write_buffer */
		/* TODO: add test for libcfile_file_write_buffer_with_error_code */
		/* TODO: add test for libcfile_file_resize */

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_is_open",
		 cfile_test_file_is_open,
		 file );

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_get_offset",
		 cfile_test_file_get_offset,
		 file );

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_get_size",
		 cfile_test_file_get_size,
		 file );

		CFILE_TEST_RUN_WITH_ARGS(
		 "libcfile_file_is_device",
		 cfile_test_file_is_device,
		 file );

		/* TODO: add test for libcfile_file_io_control_read */
		/* TODO: add test for libcfile_file_io_control_read_with_error_code */
		/* TODO: add test for libcfile_file_set_access_behavior */
		/* TODO: add test for libcfile_file_set_block_size */

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

