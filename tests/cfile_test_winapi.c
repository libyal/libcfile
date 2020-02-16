/*
 * Library WINAPI fallback functions test program
 *
 * Copyright (C) 2008-2020, Joachim Metz <joachim.metz@gmail.com>
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "cfile_test_libcfile.h"
#include "cfile_test_macros.h"
#include "cfile_test_unused.h"

#include "../libcfile/libcfile_winapi.h"

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

	CFILE_TEST_ASSERT_EQUAL_INTPTR(
	 "result",
	 (intptr_t) result,
	 (intptr_t) INVALID_HANDLE_VALUE );

	return( 1 );

on_error:
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

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

	CFILE_TEST_ASSERT_EQUAL_INTPTR(
	 "result",
	 (intptr_t) result,
	 (intptr_t) INVALID_HANDLE_VALUE );

	return( 1 );

on_error:
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libcfile_GetOverlappedResult function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_libcfile_GetOverlappedResult(
     void )
{
	OVERLAPPED overlapped;

	DWORD read_count = 0;
	BOOL result      = FALSE;

	/* Test error cases
	 */
	result = libcfile_GetOverlappedResult(
	          NULL,
	          &overlapped,
	          &read_count,
	          FALSE );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 FALSE );

	result = libcfile_GetOverlappedResult(
	          (HANDLE) 0x12345678,
	          NULL,
	          &read_count,
	          FALSE );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 FALSE );

	result = libcfile_GetOverlappedResult(
	          (HANDLE) 0x12345678,
	          &overlapped,
	          NULL,
	          FALSE );

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
	uint8_t buffer[ 32 ];

	DWORD read_count = 0;
	BOOL result      = FALSE;

	/* Test error cases
	 */
	result = libcfile_ReadFile(
	          NULL,
	          (VOID *) buffer,
	          32,
	          &read_count,
	          NULL );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 FALSE );

	result = libcfile_ReadFile(
	          (HANDLE) 0x12345678,
	          NULL,
	          32,
	          &read_count,
	          NULL );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 FALSE );

	result = libcfile_ReadFile(
	          (HANDLE) 0x12345678,
	          (VOID *) buffer,
	          32,
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

/* Tests the libcfile_WriteFile function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_libcfile_WriteFile(
     void )
{
	uint8_t buffer[ 32 ];

	DWORD write_count = 0;
	BOOL result       = FALSE;

	/* Test error cases
	 */
	result = libcfile_WriteFile(
	          NULL,
	          (VOID *) buffer,
	          32,
	          &write_count,
	          NULL );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 FALSE );

	result = libcfile_WriteFile(
	          (HANDLE) 0x12345678,
	          NULL,
	          32,
	          &write_count,
	          NULL );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 FALSE );

	result = libcfile_WriteFile(
	          (HANDLE) 0x12345678,
	          (VOID *) buffer,
	          32,
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

/* Tests the libcfile_SetEndOfFile function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_libcfile_SetEndOfFile(
     void )
{
	BOOL result = FALSE;

	/* Test error cases
	 */
	result = libcfile_SetEndOfFile(
	          NULL );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 FALSE );

	return( 1 );

on_error:
	return( 0 );
}

/* Tests the libcfile_SetFilePointerEx function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_libcfile_SetFilePointerEx(
     void )
{
	LARGE_INTEGER distance_to_move_large_integer;
	LARGE_INTEGER new_file_pointer_large_integer;

	BOOL result = FALSE;

	/* Test error cases
	 */
#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
	distance_to_move_large_integer.QuadPart = 0;
#else
	distance_to_move_large_integer.LowPart  = 0;
	distance_to_move_large_integer.HighPart = 0;
#endif

	result = libcfile_SetFilePointerEx(
	          NULL,
	          distance_to_move_large_integer,
	          &new_file_pointer_large_integer,
	          FILE_BEGIN );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 FALSE );

	result = libcfile_SetFilePointerEx(
	          (HANDLE) 0x12345678,
	          distance_to_move_large_integer,
	          NULL,
	          FILE_BEGIN );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 FALSE );

	return( 1 );

on_error:
	return( 0 );
}

/* Tests the libcfile_GetFileSizeEx function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_libcfile_GetFileSizeEx(
     void )
{
	LARGE_INTEGER file_size_large_integer;

	BOOL result = FALSE;

	/* Test error cases
	 */
	result = libcfile_GetFileSizeEx(
	          NULL,
	          &file_size_large_integer );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 FALSE );

	result = libcfile_GetFileSizeEx(
	          (HANDLE) 0x12345678,
	          NULL );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 FALSE );

	return( 1 );

on_error:
	return( 0 );
}

/* Tests the libcfile_GetFileType function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_libcfile_GetFileType(
     void )
{
	LARGE_INTEGER file_size_large_integer;

	DWORD result = FILE_TYPE_UNKNOWN;

	/* Test error cases
	 */
	result = libcfile_GetFileType(
	          NULL );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 FILE_TYPE_UNKNOWN );

	return( 1 );

on_error:
	return( 0 );
}

/* Tests the libcfile_GetFileAttributesA function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_libcfile_GetFileAttributesA(
     void )
{
	DWORD result = 0;

	/* Test error cases
	 */
	result = libcfile_GetFileAttributesA(
	          NULL );

	CFILE_TEST_ASSERT_EQUAL_UINT32(
	 "result",
	 (uint32_t) result,
	 (uint32_t) INVALID_FILE_ATTRIBUTES );

	return( 1 );

on_error:
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libcfile_GetFileAttributesW function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_libcfile_GetFileAttributesW(
     void )
{
	DWORD result = 0;

	/* Test error cases
	 */
	result = libcfile_GetFileAttributesW(
	          NULL );

	CFILE_TEST_ASSERT_EQUAL_UINT32(
	 "result",
	 (uint32_t) result,
	 (uint32_t) INVALID_FILE_ATTRIBUTES );

	return( 1 );

on_error:
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libcfile_DeleteFileA function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_libcfile_DeleteFileA(
     void )
{
	BOOL result = FALSE;

	/* Test error cases
	 */
	result = libcfile_DeleteFileA(
	          NULL );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 FALSE );

	return( 1 );

on_error:
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libcfile_DeleteFileW function
 * Returns 1 if successful or 0 if not
 */
int cfile_test_libcfile_DeleteFileW(
     void )
{
	BOOL result = FALSE;

	/* Test error cases
	 */
	result = libcfile_DeleteFileW(
	          NULL );

	CFILE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 FALSE );

	return( 1 );

on_error:
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#endif /* defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) && defined( WINAPI ) && ( WINVER <= 0x0500 ) */

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

#if defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) && defined( WINAPI ) && ( WINVER <= 0x0500 )

	CFILE_TEST_RUN(
	 "libcfile_CloseHandle",
	 cfile_test_libcfile_CloseHandle );

	CFILE_TEST_RUN(
	 "libcfile_CreateFileA",
	 cfile_test_libcfile_CreateFileA );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	CFILE_TEST_RUN(
	 "libcfile_CreateFileW",
	 cfile_test_libcfile_CreateFileW );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

	CFILE_TEST_RUN(
	 "libcfile_GetOverlappedResult",
	 cfile_test_libcfile_GetOverlappedResult );

	CFILE_TEST_RUN(
	 "libcfile_ReadFile",
	 cfile_test_libcfile_ReadFile );

	CFILE_TEST_RUN(
	 "libcfile_WriteFile",
	 cfile_test_libcfile_WriteFile );

	CFILE_TEST_RUN(
	 "libcfile_SetFilePointerEx",
	 cfile_test_libcfile_SetFilePointerEx );

	CFILE_TEST_RUN(
	 "libcfile_SetEndOfFile",
	 cfile_test_libcfile_SetEndOfFile );

	CFILE_TEST_RUN(
	 "libcfile_GetFileSizeEx",
	 cfile_test_libcfile_GetFileSizeEx );

	CFILE_TEST_RUN(
	 "libcfile_GetFileType",
	 cfile_test_libcfile_GetFileType );

	CFILE_TEST_RUN(
	 "libcfile_GetFileAttributesA",
	 cfile_test_libcfile_GetFileAttributesA );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	CFILE_TEST_RUN(
	 "libcfile_GetFileAttributesW",
	 cfile_test_libcfile_GetFileAttributesW );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

	CFILE_TEST_RUN(
	 "libcfile_DeleteFileA",
	 cfile_test_libcfile_DeleteFileA );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	CFILE_TEST_RUN(
	 "libcfile_DeleteFileW",
	 cfile_test_libcfile_DeleteFileW );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#endif /* defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) && defined( WINAPI ) && ( WINVER <= 0x0500 ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) && defined( WINAPI ) && ( WINVER <= 0x0500 )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBCFILE_DLL_IMPORT ) && defined( WINAPI ) && ( WINVER <= 0x0500 ) */
}

