/*
 * File functions
 *
 * Copyright (c) 2008-2013, Joachim Metz <joachim.metz@gmail.com>
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
#include <memory.h>
#include <types.h>

#if defined( HAVE_SYS_STAT_H ) || defined( WINAPI )
#include <sys/stat.h>
#endif

#if defined( HAVE_ERRNO_H ) || defined( WINAPI )
#include <errno.h>
#endif

#if defined( HAVE_FCNTL_H ) || defined( WINAPI )
#include <fcntl.h>
#endif

#if defined( WINAPI )
#include <io.h>
#endif

#if defined( WINAPI ) && !defined( __CYGWIN__ )
#include <share.h>
#endif

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#if defined( HAVE_GLIB_H )
#include <glib.h>
#include <glib/gstdio.h>
#endif

#include "libcfile_definitions.h"
#include "libcfile_file.h"
#include "libcfile_libcerror.h"
#include "libcfile_libclocale.h"
#include "libcfile_libcstring.h"
#include "libcfile_libuna.h"
#include "libcfile_types.h"

/* Initializes the file
 * Returns 1 if successful or -1 on error
 */
int libcfile_file_initialize(
     libcfile_file_t **file,
     libcerror_error_t **error )
{
	libcfile_internal_file_t *internal_file = NULL;
	static char *function                   = "libcfile_file_initialize";

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
	if( *file != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file value already set.",
		 function );

		return( -1 );
	}
	internal_file = memory_allocate_structure(
		         libcfile_internal_file_t );

	if( internal_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_file,
	     0,
	     sizeof( libcfile_internal_file_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file.",
		 function );

		goto on_error;
	}
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	internal_file->handle = INVALID_HANDLE_VALUE;
#else
	internal_file->descriptor = -1;
#endif
	*file = (libcfile_file_t *) internal_file;

	return( 1 );

on_error:
	if( internal_file != NULL )
	{
		memory_free(
		 internal_file );
	}
	return( -1 );
}

/* Frees the file including elements
 * Returns 1 if successful or -1 on error
 */
int libcfile_file_free(
     libcfile_file_t **file,
     libcerror_error_t **error )
{
	libcfile_internal_file_t *internal_file = NULL;
	static char *function                   = "libcfile_file_free";
	int result                              = 1;

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
	if( *file != NULL )
	{
		internal_file = (libcfile_internal_file_t *) *file;

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
		if( internal_file->handle != INVALID_HANDLE_VALUE )
#else
		if( internal_file->descriptor != -1 )
#endif
		{
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
		}
		*file = NULL;

		memory_free(
		 internal_file );
	}
	return( result );
}

#if defined( WINAPI ) && ( WINVER > 0x0500 ) && !defined( USE_CRT_FUNCTIONS )

/* Opens a file
 * This function uses the WINAPI function for Windows XP or later
 * Returns 1 if successful or -1 on error
 */
int libcfile_file_open(
     libcfile_file_t *file,
     const char *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libcfile_internal_file_t *internal_file = NULL;
	static char *function                   = "libcfile_file_open";
	DWORD error_code                        = 0;
	DWORD file_io_access_flags              = 0;
	DWORD file_io_creation_flags            = 0;
	DWORD file_io_shared_flags              = 0;

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
	internal_file = (libcfile_internal_file_t *) file;

	if( internal_file->handle != INVALID_HANDLE_VALUE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - handle value already set.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBCFILE_ACCESS_FLAG_READ ) != 0 )
	 && ( ( access_flags & LIBCFILE_ACCESS_FLAG_WRITE ) != 0 ) )
	{
		file_io_access_flags   = GENERIC_WRITE | GENERIC_READ;
		file_io_creation_flags = OPEN_ALWAYS;
		file_io_shared_flags   = FILE_SHARE_READ;
	}
	else if( ( access_flags & LIBCFILE_ACCESS_FLAG_READ ) != 0 )
	{
		file_io_access_flags   = GENERIC_READ;
		file_io_creation_flags = OPEN_EXISTING;
		file_io_shared_flags   = FILE_SHARE_READ;
	}
	else if( ( access_flags & LIBCFILE_ACCESS_FLAG_WRITE ) != 0 )
	{
		file_io_access_flags   = GENERIC_WRITE;
		file_io_creation_flags = OPEN_ALWAYS;
		file_io_shared_flags   = 0;
	}
	else
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags: 0x%02x.",
		 function,
		 access_flags );

		return( -1 );
	}
	if( ( ( access_flags & LIBCFILE_ACCESS_FLAG_WRITE ) != 0 )
	 && ( ( access_flags & LIBCFILE_ACCESS_FLAG_TRUNCATE ) != 0 ) )
	{
		file_io_creation_flags = CREATE_ALWAYS;
	}
	internal_file->handle = CreateFileA(
	                         (LPCSTR) filename,
	                         file_io_access_flags,
	                         file_io_shared_flags,
	                         NULL,
	                         file_io_creation_flags,
	                         FILE_ATTRIBUTE_NORMAL,
	                         NULL );

	if( internal_file->handle == INVALID_HANDLE_VALUE )
	{
		error_code = GetLastError();

		switch( error_code )
		{
			case ERROR_ACCESS_DENIED:
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_ACCESS_DENIED,
				 "%s: access denied to file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;

			case ERROR_FILE_NOT_FOUND:
			case ERROR_PATH_NOT_FOUND:
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_INVALID_RESOURCE,
				 "%s: no such file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;

			default:
				libcerror_system_set_error(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_OPEN_FAILED,
				 error_code,
				 "%s: unable to open file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;
		}
		return( -1 );
	}
	return( 1 );
}

#elif defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )

/* TODO */
#error WINAPI file open function for Windows 2000 or earlier NOT implemented yet

#elif defined( WINAPI ) && defined( USE_CRT_FUNCTIONS ) && defined( _MSC_VER )

/* Opens a file
 * This function uses the Visual Studio C runtime library function
 * Returns 1 if successful or -1 on error
 */
int libcfile_file_open(
     libcfile_file_t *file,
     const char *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libcfile_internal_file_t *internal_file = NULL;
	static char *function                   = "libcfile_file_open";
	int file_io_permission_flags            = 0;
	int file_io_flags                       = 0;
	int file_io_shared_flags                = 0;

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
	internal_file = (libcfile_internal_file_t *) file;

	if( ( ( access_flags & LIBCFILE_ACCESS_FLAG_READ ) != 0 )
	 && ( ( access_flags & LIBCFILE_ACCESS_FLAG_WRITE ) != 0 ) )
	{
		file_io_flags            = _O_RDWR | _O_CREAT;
		file_io_permission_flags = _S_IREAD | _S_IWRITE;
		file_io_shared_flags     = _SH_DENYWR;
	}
	else if( ( access_flags & LIBCFILE_ACCESS_FLAG_READ ) != 0 )
	{
		file_io_flags        = _O_RDONLY;
		file_io_shared_flags = _SH_DENYWR;
	}
	else if( ( access_flags & LIBCFILE_ACCESS_FLAG_WRITE ) != 0 )
	{
		file_io_flags            = _O_WRONLY | _O_CREAT;
		file_io_permission_flags = _S_IREAD | _S_IWRITE;
		file_io_shared_flags     = _SH_DENYRW;
	}
	else
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags: 0x%02x.",
		 function,
		 access_flags );

		return( -1 );
	}
	if( ( ( access_flags & LIBCFILE_ACCESS_FLAG_WRITE ) != 0 )
	 && ( ( access_flags & LIBCFILE_ACCESS_FLAG_TRUNCATE ) != 0 ) )
	{
		file_io_flags |= _O_TRUNC;
	}
	if( _sopen_s(
	     &( internal_file->descriptor ),
	     (char *) filename,
	     file_io_flags | _O_BINARY,
	     file_io_shared_flags,
	     file_io_permission_flags ) != 0 )
	{
		switch( errno )
		{
			case EACCES:
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_ACCESS_DENIED,
				 "%s: access denied to file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;

			case ENOENT:
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_INVALID_RESOURCE,
				 "%s: no such file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;

			default:
				libcerror_system_set_error(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_OPEN_FAILED,
				 errno,
				 "%s: unable to open file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;
		}
		return( -1 );
	}
	if( internal_file->descriptor == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: invalid descriptor: %d returned.",
		 function,
		 internal_file->descriptor );

		return( -1 );
	}
	return( 1 );
}

#elif defined( HAVE_OPEN ) || defined( WINAPI )

/* Opens a file
 * This function uses the POSIX open function or equivalent
 * Returns 1 if successful or -1 on error
 */
int libcfile_file_open(
     libcfile_file_t *file,
     const char *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libcfile_internal_file_t *internal_file = NULL;
	static char *function                   = "libcfile_file_open";
	int file_io_flags                       = 0;

#if defined( WINAPI )
	int file_io_permission_flags            = 0;
	int file_io_flags                       = 0;
#endif

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
	internal_file = (libcfile_internal_file_t *) file;

	if( ( ( access_flags & LIBCFILE_ACCESS_FLAG_READ ) != 0 )
	 && ( ( access_flags & LIBCFILE_ACCESS_FLAG_WRITE ) != 0 ) )
	{
#if defined( WINAPI )
		file_io_flags            = _O_RDWR | _O_CREAT;
		file_io_permission_flags = _S_IREAD | _S_IWRITE;
#else
		file_io_flags            = O_RDWR | O_CREAT;
#endif
	}
	else if( ( access_flags & LIBCFILE_ACCESS_FLAG_READ ) != 0 )
	{
#if defined( WINAPI )
		file_io_flags = _O_RDONLY;
#else
		file_io_flags = O_RDONLY;
#endif
	}
	else if( ( access_flags & LIBCFILE_ACCESS_FLAG_WRITE ) != 0 )
	{
#if defined( WINAPI )
		file_io_flags            = _O_WRONLY | _O_CREAT;
		file_io_permission_flags = _S_IREAD | _S_IWRITE;
#else
		file_io_flags            = O_WRONLY | O_CREAT;
#endif
	}
	else
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags: 0x%02x.",
		 function,
		 access_flags );

		return( -1 );
	}
	if( ( ( access_flags & LIBCFILE_ACCESS_FLAG_WRITE ) != 0 )
	 && ( ( access_flags & LIBCFILE_ACCESS_FLAG_TRUNCATE ) != 0 ) )
	{
#if defined( WINAPI )
		file_io_flags |= _O_TRUNC;
#else
		file_io_flags |= O_TRUNC;
#endif
	}
#if defined( WINAPI )
	internal_file->descriptor = _sopen(
	                             filename,
	                             file_io_flags | _O_BINARY,
	                             file_io_permission_flags );
#elif defined( HAVE_GLIB_H )
	internal_file->descriptor = g_open(
	                             filename,
	                             file_io_flags,
	                             0644 );
#else
	internal_file->descriptor = open(
	                             filename,
	                             file_io_flags,
	                             0644 );
#endif
	if( internal_file->descriptor == -1 )
	{
		switch( errno )
		{
			case EACCES:
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_ACCESS_DENIED,
				 "%s: access denied to file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;

			case ENOENT:
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_INVALID_RESOURCE,
				 "%s: no such file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;

			default:
				libcerror_system_set_error(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_OPEN_FAILED,
				 errno,
				 "%s: unable to open file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;
		}
		return( -1 );
	}
	return( 1 );
}

#else
#error Missing file open function
#endif

#if defined( HAVE_WIDE_CHARACTER_TYPE )

#if defined( WINAPI ) && ( WINVER > 0x0500 ) && !defined( USE_CRT_FUNCTIONS )

/* Opens a file
 * This function uses the WINAPI function for Windows XP or later
 * Returns 1 if successful or -1 on error
 */
int libcfile_file_open_wide(
     libcfile_file_t *file,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libcfile_internal_file_t *internal_file = NULL;
	static char *function                   = "libcfile_file_open_wide";
	DWORD error_code                        = 0;
	DWORD file_io_access_flags              = 0;
	DWORD file_io_creation_flags            = 0;
	DWORD file_io_shared_flags              = 0;

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
	internal_file = (libcfile_internal_file_t *) file;

	if( internal_file->handle != INVALID_HANDLE_VALUE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - handle value already set.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBCFILE_ACCESS_FLAG_READ ) != 0 )
	 && ( ( access_flags & LIBCFILE_ACCESS_FLAG_WRITE ) != 0 ) )
	{
		file_io_access_flags   = GENERIC_WRITE | GENERIC_READ;
		file_io_creation_flags = OPEN_ALWAYS;
		file_io_shared_flags   = FILE_SHARE_READ;
	}
	else if( ( access_flags & LIBCFILE_ACCESS_FLAG_READ ) != 0 )
	{
		file_io_access_flags   = GENERIC_READ;
		file_io_creation_flags = OPEN_EXISTING;
		file_io_shared_flags   = FILE_SHARE_READ;
	}
	else if( ( access_flags & LIBCFILE_ACCESS_FLAG_WRITE ) != 0 )
	{
		file_io_access_flags   = GENERIC_WRITE;
		file_io_creation_flags = OPEN_ALWAYS;
		file_io_shared_flags   = 0;
	}
	else
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags: 0x%02x.",
		 function,
		 access_flags );

		return( -1 );
	}
	if( ( ( access_flags & LIBCFILE_ACCESS_FLAG_WRITE ) != 0 )
	 && ( ( access_flags & LIBCFILE_ACCESS_FLAG_TRUNCATE ) != 0 ) )
	{
		file_io_creation_flags = CREATE_ALWAYS;
	}
	internal_file->handle = CreateFileW(
	                         (LPCWSTR) filename,
	                         file_io_access_flags,
	                         file_io_shared_flags,
	                         NULL,
	                         file_io_creation_flags,
	                         FILE_ATTRIBUTE_NORMAL,
	                         NULL );

	if( internal_file->handle == INVALID_HANDLE_VALUE )
	{
		error_code = GetLastError();

		switch( error_code )
		{
			case ERROR_ACCESS_DENIED:
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_ACCESS_DENIED,
				 "%s: access denied to file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;

			case ERROR_FILE_NOT_FOUND:
			case ERROR_PATH_NOT_FOUND:
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_INVALID_RESOURCE,
				 "%s: no such file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;

			default:
				libcerror_system_set_error(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_OPEN_FAILED,
				 error_code,
				 "%s: unable to open file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;
		}
		return( -1 );
	}
	return( 1 );
}

#elif defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )

/* TODO */
#error WINAPI file open function for Windows 2000 or earlier NOT implemented yet

#elif defined( WINAPI ) && defined( USE_CRT_FUNCTIONS ) && defined( _MSC_VER )

/* Opens a file
 * This function uses the Visual Studio C runtime library function
 * Returns 1 if successful or -1 on error
 */
int libcfile_file_open_wide(
     libcfile_file_t *file,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libcfile_internal_file_t *internal_file = NULL;
	static char *function                   = "libcfile_file_open_wide";
	int file_io_permission_flags            = 0;
	int file_io_flags                       = 0;
	int file_io_shared_flags                = 0;

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
	internal_file = (libcfile_internal_file_t *) file;

	if( ( ( access_flags & LIBCFILE_ACCESS_FLAG_READ ) != 0 )
	 && ( ( access_flags & LIBCFILE_ACCESS_FLAG_WRITE ) != 0 ) )
	{
		file_io_flags            = _O_RDWR | _O_CREAT;
		file_io_permission_flags = _S_IREAD | _S_IWRITE;
		file_io_shared_flags     = _SH_DENYWR;
	}
	else if( ( access_flags & LIBCFILE_ACCESS_FLAG_READ ) != 0 )
	{
		file_io_flags        = _O_RDONLY;
		file_io_shared_flags = _SH_DENYWR;
	}
	else if( ( access_flags & LIBCFILE_ACCESS_FLAG_WRITE ) != 0 )
	{
		file_io_flags            = _O_WRONLY | _O_CREAT;
		file_io_permission_flags = _S_IREAD | _S_IWRITE;
		file_io_shared_flags     = _SH_DENYRW;
	}
	else
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags: 0x%02x.",
		 function,
		 access_flags );

		return( -1 );
	}
	if( ( ( access_flags & LIBCFILE_ACCESS_FLAG_WRITE ) != 0 )
	 && ( ( access_flags & LIBCFILE_ACCESS_FLAG_TRUNCATE ) != 0 ) )
	{
		file_io_flags |= _O_TRUNC;
	}
	if( _wsopen_s(
	     &( internal_file->descriptor ),
	     (wchar_t *) filename,
	     file_io_flags | _O_BINARY,
	     file_io_shared_flags,
	     file_io_permission_flags ) != 0 )
	{
		switch( errno )
		{
			case EACCES:
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_ACCESS_DENIED,
				 "%s: access denied to file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;

			case ENOENT:
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_INVALID_RESOURCE,
				 "%s: no such file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;

			default:
				libcerror_system_set_error(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_OPEN_FAILED,
				 errno,
				 "%s: unable to open file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;
		}
		return( -1 );
	}
	if( internal_file->descriptor == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: invalid descriptor: %d returned.",
		 function,
		 internal_file->descriptor );

		return( -1 );
	}
	return( 1 );
}

#elif defined( HAVE_OPEN ) || defined( WINAPI )

/* Opens a file
 * This function uses the POSIX open function or equivalent
 * Returns 1 if successful or -1 on error
 */
int libcfile_file_open_wide(
     libcfile_file_t *file,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libcfile_internal_file_t *internal_file = NULL;
	static char *function                   = "libcfile_file_open_wide";
	int file_io_flags                       = 0;
	int result                              = 0;

#if defined( WINAPI )
	int file_io_permission_flags            = 0;
	int file_io_flags                       = 0;
#else
	char *narrow_filename                   = NULL;
	size_t filename_size                    = 0;
	size_t narrow_filename_size             = 0;
#endif

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
	internal_file = (libcfile_internal_file_t *) file;

	if( ( ( access_flags & LIBCFILE_ACCESS_FLAG_READ ) != 0 )
	 && ( ( access_flags & LIBCFILE_ACCESS_FLAG_WRITE ) != 0 ) )
	{
#if defined( WINAPI )
		file_io_flags            = _O_RDWR | _O_CREAT;
		file_io_permission_flags = _S_IREAD | _S_IWRITE;
#else
		file_io_flags            = O_RDWR | O_CREAT;
#endif
	}
	else if( ( access_flags & LIBCFILE_ACCESS_FLAG_READ ) != 0 )
	{
#if defined( WINAPI )
		file_io_flags = _O_RDONLY;
#else
		file_io_flags = O_RDONLY;
#endif
	}
	else if( ( access_flags & LIBCFILE_ACCESS_FLAG_WRITE ) != 0 )
	{
#if defined( WINAPI )
		file_io_flags            = _O_WRONLY | _O_CREAT;
		file_io_permission_flags = _S_IREAD | _S_IWRITE;
#else
		file_io_flags            = O_WRONLY | O_CREAT;
#endif
	}
	else
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags: 0x%02x.",
		 function,
		 access_flags );

		return( -1 );
	}
	if( ( ( access_flags & LIBCFILE_ACCESS_FLAG_WRITE ) != 0 )
	 && ( ( access_flags & LIBCFILE_ACCESS_FLAG_TRUNCATE ) != 0 ) )
	{
#if defined( WINAPI )
		file_io_flags |= _O_TRUNC;
#else
		file_io_flags |= O_TRUNC;
#endif
	}
#if defined( WINAPI )
	internal_file->descriptor = _wsopen(
	                             (wchar_t *) filename,
	                             file_io_flags | _O_BINARY,
	                             file_io_permission_flags );
#else
	filename_size = 1 + libcstring_wide_string_length(
	                     filename );

	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) filename,
		          filename_size,
		          &narrow_filename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) filename,
		          filename_size,
		          &narrow_filename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) filename,
		          filename_size,
		          libclocale_codepage,
		          &narrow_filename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) filename,
		          filename_size,
		          libclocale_codepage,
		          &narrow_filename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine narrow character filename size.",
		 function );

		return( -1 );
	}
	narrow_filename = libcstring_narrow_string_allocate(
	                   narrow_filename_size );

	if( narrow_filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create narrow character filename.",
		 function );

		return( -1 );
	}
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_copy_from_utf32(
		          (libuna_utf8_character_t *) narrow_filename,
		          narrow_filename_size,
		          (libuna_utf32_character_t *) filename,
		          filename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_copy_from_utf16(
		          (libuna_utf8_character_t *) narrow_filename,
		          narrow_filename_size,
		          (libuna_utf16_character_t *) filename,
		          filename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_copy_from_utf32(
		          (uint8_t *) narrow_filename,
		          narrow_filename_size,
		          libclocale_codepage,
		          (libuna_utf32_character_t *) filename,
		          filename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_copy_from_utf16(
		          (uint8_t *) narrow_filename,
		          narrow_filename_size,
		          libclocale_codepage,
		          (libuna_utf16_character_t *) filename,
		          filename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set narrow character filename.",
		 function );

		memory_free(
		 narrow_filename );

		return( -1 );
	}
#if defined( HAVE_GLIB_H )
	internal_file->descriptor = g_open(
	                             narrow_filename,
	                             file_io_flags,
	                             0644 );
#else
	internal_file->descriptor = open(
	                             narrow_filename,
	                             file_io_flags,
	                             0644 );
#endif

	memory_free(
	 narrow_filename );

#endif /* defined( WINAPI ) */

	if( internal_file->descriptor == -1 )
	{
		switch( errno )
		{
			case EACCES:
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_ACCESS_DENIED,
				 "%s: access denied to file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;

			case ENOENT:
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_INVALID_RESOURCE,
				 "%s: no such file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;

			default:
				libcerror_system_set_error(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_OPEN_FAILED,
				 errno,
				 "%s: unable to open file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;
		}
		return( -1 );
	}
	return( 1 );
}

#else
#error Missing file open wide function
#endif

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( WINAPI ) && ( WINVER >= 0x0500 ) && !defined( USE_CRT_FUNCTIONS )

/* Closes the file
 * This function uses the WINAPI function for Windows 2000 or later
 * Returns 0 if successful or -1 on error
 */
int libcfile_file_close(
     libcfile_file_t *file,
     libcerror_error_t **error )
{
	libcfile_internal_file_t *internal_file = NULL;
	static char *function                   = "libcfile_file_close";
	DWORD error_code                        = 0;

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
	internal_file = (libcfile_internal_file_t *) file;

	if( internal_file->handle == INVALID_HANDLE_VALUE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing handle.",
		 function );

		return( -1 );
	}
	if( CloseHandle(
	     internal_file->handle ) == 0 )
	{
		error_code = GetLastError();

		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 error_code,
		 "%s: unable to close file.",
		 function );

		return( -1 );
	}
	internal_file->handle = INVALID_HANDLE_VALUE;

	return( 0 );
}

#elif defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )

/* TODO */
#error WINAPI file open function for Windows NT4 or earlier NOT implemented yet

#elif defined( HAVE_CLOSE ) || defined( WINAPI )

/* Closes the file
 * This function uses the POSIX close function or equivalent
 * Returns 0 if successful or -1 on error
 */
int libcfile_file_close(
     libcfile_file_t *file,
     libcerror_error_t **error )
{
	libcfile_internal_file_t *internal_file = NULL;
	static char *function                   = "libcfile_file_close";

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
	internal_file = (libcfile_internal_file_t *) file;

	if( internal_file->descriptor == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing descriptor.",
		 function );

		return( -1 );
	}
#if defined( WINAPI )
	if( _close(
	     internal_file->descriptor ) != 0 )
#else
	if( close(
	     internal_file->descriptor ) != 0 )
#endif
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 errno,
		 "%s: unable to close file.",
		 function );

		return( -1 );
	}
	internal_file->descriptor = -1;

	return( 0 );
}

#else
#error Missing file close function
#endif

#if defined( WINAPI ) && ( WINVER > 0x0500 ) && !defined( USE_CRT_FUNCTIONS )

/* Reads a buffer from the file
 * This function uses the WINAPI function for Windows XP or later
 * Returns the number of bytes read if successful, or -1 on error
 */
ssize_t libcfile_file_read_buffer(
         libcfile_file_t *file,
         uint8_t *buffer,
         size_t size,
         libcerror_error_t **error )
{
	libcfile_internal_file_t *internal_file = NULL;
	static char *function                   = "libcfile_file_read_buffer";
	ssize_t read_count                      = 0;
	DWORD error_code                        = 0;

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
	internal_file = (libcfile_internal_file_t *) file;

	if( internal_file->handle == INVALID_HANDLE_VALUE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing handle.",
		 function );

		return( -1 );
	}
	if( buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer.",
		 function );

		return( -1 );
	}
#if UINT32_MAX < SSIZE_MAX
	if( size > (size_t) UINT32_MAX )
#else
	if( size > (size_t) SSIZE_MAX )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ReadFile(
	     internal_file->handle,
	     buffer,
	     (DWORD) size,
	     (LPDWORD) &read_count,
	     NULL ) == 0 )
	{
		error_code = GetLastError();

		switch( error_code )
		{
			case ERROR_HANDLE_EOF:
				break;

			default:
				libcerror_system_set_error(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 error_code,
				 "%s: unable to read from file.",
				 function );

				break;
		}
		return( -1 );
	}
	if( read_count < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: invalid read count: %" PRIzd " returned.",
		 function,
		 read_count );

		return( -1 );
	}
	return( read_count );
}

#elif defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )

/* TODO */
#error WINAPI file read function for Windows 2000 or earlier NOT implemented yet

#elif defined( HAVE_READ ) || defined( WINAPI )

/* Reads a buffer from the file
 * This function uses the POSIX read function or equivalent
 * Returns the number of bytes read if successful, or -1 on error
 */
ssize_t libcfile_file_read_buffer(
         libcfile_file_t *file,
         uint8_t *buffer,
         size_t size,
         libcerror_error_t **error )
{
	libcfile_internal_file_t *internal_file = NULL;
	static char *function                   = "libcfile_file_read_buffer";
	ssize_t read_count                      = 0;

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
	internal_file = (libcfile_internal_file_t *) file;

	if( internal_file->descriptor == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing descriptor.",
		 function );

		return( -1 );
	}
	if( buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer.",
		 function );

		return( -1 );
	}
#if UINT_MAX < SSIZE_MAX
	if( size > (size_t) UINT_MAX )
#else
	if( size > (size_t) SSIZE_MAX )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( WINAPI )
	read_count = _read(
	              internal_file->descriptor,
	              (void *) buffer,
	              (unsigned int) size );
#else
	read_count = read(
	              internal_file->descriptor,
	              (void *) buffer,
	              size );
#endif

	if( read_count < 0 )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 errno,
		 "%s: unable to read from file.",
		 function );

		return( -1 );
	}
	return( read_count );
}

#else
#error Missing file read function
#endif

#if defined( WINAPI ) && ( WINVER > 0x0500 ) && !defined( USE_CRT_FUNCTIONS )

/* Writes a buffer to the file
 * This function uses the WINAPI function for Windows XP or later
 * Returns the number of bytes written if successful, or -1 on error
 */
ssize_t libcfile_file_write_buffer(
         libcfile_file_t *file,
         const uint8_t *buffer,
         size_t size,
         libcerror_error_t **error )
{
	libcfile_internal_file_t *internal_file = NULL;
	static char *function                   = "libcfile_file_write_buffer";
	ssize_t write_count                     = 0;
	DWORD error_code                        = 0;

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
	internal_file = (libcfile_internal_file_t *) file;

	if( internal_file->handle == INVALID_HANDLE_VALUE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing handle.",
		 function );

		return( -1 );
	}
	if( buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer.",
		 function );

		return( -1 );
	}
#if UINT32_MAX < SSIZE_MAX
	if( size > (size_t) UINT32_MAX )
#else
	if( size > (size_t) SSIZE_MAX )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( WriteFile(
	     internal_file->handle,
	     buffer,
	     (DWORD) size,
	     (LPDWORD) &write_count,
	     NULL ) == 0 )
	{
		error_code = GetLastError();

		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_WRITE_FAILED,
		 error_code,
		 "%s: unable to write to file.",
		 function );

		return( -1 );
	}
	if( write_count < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_WRITE_FAILED,
		 "%s: invalid write count: %" PRIzd " returned.",
		 function,
		 write_count );

		return( -1 );
	}
	return( write_count );
}

#elif defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )

/* TODO */
#error WINAPI file write function for Windows 2000 or earlier NOT implemented yet

#elif defined( HAVE_WRITE ) || defined( WINAPI )

/* Writes a buffer to the file
 * This function uses the POSIX write function or equivalent
 * Returns the number of bytes written if successful, or -1 on error
 */
ssize_t libcfile_file_write_buffer(
         libcfile_file_t *file,
         const uint8_t *buffer,
         size_t size,
         libcerror_error_t **error )
{
	libcfile_internal_file_t *internal_file = NULL;
	static char *function                   = "libcfile_file_write_buffer";
	ssize_t write_count                     = 0;

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
	internal_file = (libcfile_internal_file_t *) file;

	if( internal_file->descriptor == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing descriptor.",
		 function );

		return( -1 );
	}
	if( buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer.",
		 function );

		return( -1 );
	}
#if UINT_MAX < SSIZE_MAX
	if( size > (size_t) UINT_MAX )
#else
	if( size > (size_t) SSIZE_MAX )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( WINAPI )
	write_count = _write(
	               internal_file->descriptor,
	               (void *) buffer,
	               (unsigned int) size );
#else
	write_count = write(
	               internal_file->descriptor,
	               (void *) buffer,
	               size );
#endif

	if( write_count < 0 )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_WRITE_FAILED,
		 errno,
		 "%s: unable to write to file.",
		 function );

		return( -1 );
	}
	return( write_count );
}

#else
#error Missing file write function
#endif

#if defined( WINAPI ) && ( WINVER <= 0x0500 ) && !defined( USE_CRT_FUNCTIONS )

#if !defined( INVALID_SET_FILE_POINTER )
#define INVALID_SET_FILE_POINTER	((LONG) -1)
#endif

/* Cross Windows safe version of SetFilePointerEx
 * Returns TRUE if successful or FALSE on error
 */
BOOL libcfile_SetFilePointerEx(
      HANDLE file_handle,
      LARGE_INTEGER distance_to_move_large_integer,
      LARGE_INTEGER *new_file_pointer_large_integer,
      DWORD move_method )
{
	FARPROC function                 = NULL;
	HMODULE library_handle           = NULL;
	LONG distance_to_move_lower_long = 0;
	LONG distance_to_move_upper_long = 0;
	DWORD error_number               = 0;
	BOOL result                      = FALSE;

	if( file_handle == NULL )
	{
		return( FALSE );
	}
	if( new_file_pointer_large_integer == NULL )
	{
		return( FALSE );
	}
	library_handle = LoadLibrary(
	                  _LIBCSTRING_SYSTEM_STRING( "kernel32.dll" ) );

	if( library_handle == NULL )
	{
		return( FALSE );
	}
	function = GetProcAddress(
		    library_handle,
		    (LPCSTR) "SetFilePointerEx" );

	if( function != NULL )
	{
		result = function(
			  file_handle,
			  distance_to_move_large_integer,
			  new_file_pointer_large_integer,
			  move_method );
	}
	else
	{
#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x520
		distance_to_move_lower_long = distance_to_move_large_integer.QuadPart & 0xffffffffUL;
		distance_to_move_upper_long = distance_to_move_large_integer.QuadPart >> 32;
#else
		distance_to_move_lower_long = distance_to_move_large_integer.LowPart;
		distance_to_move_upper_long = distance_to_move_large_integer.HighPart;
#endif

/* TODO make sure SetFilePointer is WINAPI version safe ? Officially first supported in Windows XP */
		distance_to_move_lower_long = SetFilePointer(
					       file_handle,
					       distance_to_move_lower_long,
					       &distance_to_move_upper_long,
					       move_method );

		error_number = GetLastError();

		if( ( distance_to_move_lower_long == (LONG) INVALID_SET_FILE_POINTER )
		 && ( error_number != NO_ERROR ) )
		{
		}
		else
		{
#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x520
			new_file_pointer_large_integer->QuadPart   = distance_to_move_upper_long;
			new_file_pointer_large_integer->QuadPart <<= 32;
			new_file_pointer_large_integer->QuadPart  += distance_to_move_lower_long;
#else
			new_file_pointer_large_integer->HighPart = distance_to_move_upper_long;
			new_file_pointer_large_integer->LowPart  = distance_to_move_lower_long;
#endif

			result = TRUE;
		}
	}
	/* This call should be after using the function
	 * in most cases kernel32.dll will still be available after free
	 */
	if( FreeLibrary(
	     library_handle ) != TRUE )
	{
		result = FALSE;
	}
	return( result );
}

#endif

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )

/* Seeks a certain offset within the file
 * This function uses the WINAPI function for Windows XP (0x0501) or later
 * or tries to dynamically call the function for Windows 2000 (0x0500) or earlier
 * Returns the offset if the seek is successful or -1 on error
 */
off64_t libcfile_file_seek_offset(
         libcfile_file_t *file,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	libcfile_internal_file_t *internal_file = NULL;
	static char *function                   = "libcfile_file_seek_offset";
	LARGE_INTEGER large_integer_offset      = LIBCFILE_LARGE_INTEGER_ZERO;
	DWORD error_code                        = 0;
	DWORD move_method                       = 0;

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
	internal_file = (libcfile_internal_file_t *) file;

	if( internal_file->handle == INVALID_HANDLE_VALUE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing handle.",
		 function );

		return( -1 );
	}
	if( offset > (off64_t) INT64_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid offset value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( whence != SEEK_CUR )
	 && ( whence != SEEK_END )
	 && ( whence != SEEK_SET ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported whence.",
		 function );

		return( -1 );
	}
	if( whence == SEEK_SET )
	{
		move_method = FILE_BEGIN;
	}
	else if( whence == SEEK_CUR )
	{
		move_method = FILE_CURRENT;
	}
	else if( whence == SEEK_END )
	{
		move_method = FILE_END;
	}
#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
	large_integer_offset.QuadPart = (LONGLONG) offset;
#else
	large_integer_offset.LowPart  = (DWORD) ( 0x0ffffffffUL & offset );
	large_integer_offset.HighPart = (LONG) ( offset >> 32 );
#endif

#if ( WINVER <= 0x0500 )
	if( libcfile_SetFilePointerEx(
	     internal_file->handle,
	     large_integer_offset,
	     &large_integer_offset,
	     move_method ) == 0 )
#else
	if( SetFilePointerEx(
	     internal_file->handle,
	     large_integer_offset,
	     &large_integer_offset,
	     move_method ) == 0 )
#endif
	{
		error_code = GetLastError();

		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 error_code,
		 "%s: unable to seek offset in file.",
		 function );

		return( -1 );
	}
#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
	offset = (off64_t) large_integer_offset.QuadPart;
#else
	offset = ( (off64_t) large_integer_offset.HighPart << 32 ) + large_integer_offset.LowPart;
#endif

	if( offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: invalid offset: %" PRIi64 " returned.",
		 function,
		 offset );

		return( -1 );
	}
	return( offset );
}

#elif defined( HAVE_LSEEK ) || defined( WINAPI )

/* Seeks a certain offset within the file
 * This function uses the POSIX lseek function or equivalent
 * Returns the offset if the seek is successful or -1 on error
 */
off64_t libcfile_file_seek_offset(
         libcfile_file_t *file,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	libcfile_internal_file_t *internal_file = NULL;
	static char *function                   = "libcfile_file_seek_offset";

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
	internal_file = (libcfile_internal_file_t *) file;

	if( internal_file->descriptor == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing descriptor.",
		 function );

		return( -1 );
	}
	if( offset > (off64_t) INT64_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid offset value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( whence != SEEK_CUR )
	 && ( whence != SEEK_END )
	 && ( whence != SEEK_SET ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported whence.",
		 function );

		return( -1 );
	}
#if defined( WINAPI )
	offset = _lseeki64(
	          internal_file->descriptor,
	          offset,
	          whence );
#else
	offset = lseek(
	          internal_file->descriptor,
	          (off_t) offset,
	          whence );
#endif
	if( offset < 0 )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 errno,
		 "%s: unable to seek offset in file.",
		 function );

		return( -1 );
	}
	return( offset );
}

#else
#error Missing file lseek function
#endif

#if defined( WINAPI ) && ( WINVER <= 0x0500 ) && !defined( USE_CRT_FUNCTIONS )

/* Cross Windows safe version of SetEndOfFile
 * Returns TRUE if successful or FALSE on error
 */
BOOL libcfile_SetEndOfFile(
      HANDLE file_handle )
{
	FARPROC function       = NULL;
	HMODULE library_handle = NULL;
	BOOL result            = FALSE;

	if( file_handle == NULL )
	{
		return( FALSE );
	}
	library_handle = LoadLibrary(
	                  _LIBCSTRING_SYSTEM_STRING( "kernel32.dll" ) );

	if( library_handle == NULL )
	{
		return( FALSE );
	}
	function = GetProcAddress(
		    library_handle,
		    (LPCSTR) "SetEndOfFile" );

	if( function != NULL )
	{
		result = function(
			  file_handle );
	}
	/* This call should be after using the function
	 * in most cases kernel32.dll will still be available after free
	 */
	if( FreeLibrary(
	     library_handle ) != TRUE )
	{
		result = FALSE;
	}
	return( result );
}

#endif

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )

/* Resizes the file
 * This function uses the WINAPI function for Windows XP (0x0501) or later
 * or tries to dynamically call the function for Windows 2000 (0x0500) or earlier
 * Returns 1 if successful or -1 on error
 */
int libcfile_file_resize(
     libcfile_file_t *file,
     size64_t size,
     libcerror_error_t **error )
{
	libcfile_internal_file_t *internal_file = NULL;
	static char *function                   = "libcfile_file_resize";
	off64_t offset                          = 0;
	LARGE_INTEGER large_integer_offset      = LIBCFILE_LARGE_INTEGER_ZERO;
	DWORD error_code                        = 0;

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
	internal_file = (libcfile_internal_file_t *) file;

	if( internal_file->handle == INVALID_HANDLE_VALUE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing handle.",
		 function );

		return( -1 );
	}
	if( size > (size64_t) INT64_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
	large_integer_offset.QuadPart = (LONGLONG) size;
#else
	large_integer_offset.LowPart  = (DWORD) ( 0x0ffffffffUL & size );
	large_integer_offset.HighPart = (LONG) ( size >> 32 );
#endif

#if ( WINVER <= 0x0500 )
	if( libcfile_SetFilePointerEx(
	     internal_file->handle,
	     large_integer_offset,
	     &large_integer_offset,
	     FILE_BEGIN ) == 0 )
#else
	if( SetFilePointerEx(
	     internal_file->handle,
	     large_integer_offset,
	     &large_integer_offset,
	     FILE_BEGIN ) == 0 )
#endif
	{
		error_code = GetLastError();

		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 error_code,
		 "%s: unable to seek offset in file.",
		 function );

		return( -1 );
	}
#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
	offset = (off64_t) large_integer_offset.QuadPart;
#else
	offset = ( (off64_t) large_integer_offset.HighPart << 32 ) + large_integer_offset.LowPart;
#endif

	if( offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: invalid offset: %" PRIi64 " returned.",
		 function,
		 offset );

		return( -1 );
	}
#if ( WINVER <= 0x0500 )
	if( libcfile_SetEndOfFile(
	     internal_file->handle ) == 0 )
#else
	if( SetEndOfFile(
	     internal_file->handle ) == 0 )
#endif
	{
		error_code = GetLastError();

		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 error_code,
		 "%s: unable to resize file.",
		 function );

		return( -1 );
	}
	return( 1 );
}

#elif defined( HAVE_FTRUNCATE ) || defined( WINAPI )

/* Resizes the file
 * This function uses the POSIX truncate function or equivalent
 * Returns 1 if successful or -1 on error
 */
int libcfile_file_resize(
     libcfile_file_t *file,
     size64_t size,
     libcerror_error_t **error )
{
	libcfile_internal_file_t *internal_file = NULL;
	static char *function                   = "libcfile_file_resize";

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
	internal_file = (libcfile_internal_file_t *) file;

	if( internal_file->descriptor == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing descriptor.",
		 function );

		return( -1 );
	}
	if( size > (size64_t) INT64_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( WINAPI )
	if( _chsize(
	     internal_file->descriptor,
	     size ) != 0 )
#else
	if( ftruncate(
	     internal_file->descriptor,
	     size ) != 0 )
#endif
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_GENERIC,
		 errno,
		 "%s: unable to resize file.",
		 function );

		return( -1 );
	}
	return( 1 );
}

#else
#error Missing file truncate function
#endif

/* Checks if the file is open
 * Returns 1 if open, 0 if not or -1 on error
 */
int libcfile_file_is_open(
     libcfile_file_t *file,
     libcerror_error_t **error )
{
	libcfile_internal_file_t *internal_file = NULL;
	static char *function                   = "libcfile_file_is_open";

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
	internal_file = (libcfile_internal_file_t *) file;

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	if( internal_file->handle == INVALID_HANDLE_VALUE )
#else
	if( internal_file->descriptor == -1 )
#endif
	{
		return( 0 );
	}
	return( 1 );
}

#if defined( WINAPI ) && ( WINVER <= 0x0500 ) && !defined( USE_CRT_FUNCTIONS )

/* Cross Windows safe version of GetFileSizeEx
 * Returns TRUE if successful or FALSE on error
 */
BOOL libcfile_GetFileSizeEx(
      HANDLE file_handle,
      LARGE_INTEGER *file_size_large_integer )
{
	FARPROC function            = NULL;
	HMODULE library_handle      = NULL;
	DWORD error_number          = 0;
	DWORD file_size_upper_dword = 0;
	DWORD file_size_lower_dword = 0;
	BOOL result                 = FALSE;

	if( file_handle == NULL )
	{
		return( FALSE );
	}
	if( file_size_large_integer == NULL )
	{
		return( FALSE );
	}
	library_handle = LoadLibrary(
	                  _LIBCSTRING_SYSTEM_STRING( "kernel32.dll" ) );

	if( library_handle == NULL )
	{
		return( FALSE );
	}
	function = GetProcAddress(
		    library_handle,
		    (LPCSTR) "GetFileSizeEx" );

	if( function != NULL )
	{
		result = function(
			  file_handle,
			  file_size_large_integer );
	}
	else
	{
/* TODO make sure GetFileSize is WINAPI version safe ? Officially first supported in Windows XP */
		file_size_lower_dword = GetFileSize(
		                         file_handle,
		                         &file_size_upper_dword );

		error_number = GetLastError();

		if( ( file_size_lower_dword == INVALID_FILE_SIZE )
		 && ( error_number != NO_ERROR ) )
		{
		}
		else
		{
#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x520
			file_size_large_integer->QuadPart   = file_size_upper_dword;
			file_size_large_integer->QuadPart <<= 32;
			file_size_large_integer->QuadPart  += file_size_lower_dword;
#else
			file_size_large_integer->HighPart = file_size_upper_dword;
			file_size_large_integer->LowPart  = file_size_lower_dword;
#endif

			result = TRUE;
		}
	}
	/* This call should be after using the function
	 * in most cases kernel32.dll will still be available after free
	 */
	if( FreeLibrary(
	     library_handle ) != TRUE )
	{
		result = FALSE;
	}
	return( result );
}

#endif

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )

/* Retrieves the current offset in the file
 * This function uses the WINAPI function for Windows XP (0x0501) or later
 * or tries to dynamically call the function for Windows 2000 (0x0500) or earlier
 * Returns 1 if successful or -1 on error
 */
int libcfile_file_get_offset(
     libcfile_file_t *file,
     off64_t *offset,
     libcerror_error_t **error )
{
	libcfile_internal_file_t *internal_file = NULL;
	static char *function                   = "libcfile_file_get_offset";
	LARGE_INTEGER large_integer_offset      = LIBCFILE_LARGE_INTEGER_ZERO;
	DWORD error_code                        = 0;

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
	internal_file = (libcfile_internal_file_t *) file;

	if( internal_file->handle == INVALID_HANDLE_VALUE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing handle.",
		 function );

		return( -1 );
	}
	if( offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset.",
		 function );

		return( -1 );
	}
#if ( WINVER <= 0x0500 )
	if( libcfile_SetFilePointerEx(
	     internal_file->handle,
	     large_integer_offset,
	     &large_integer_offset,
	     FILE_CURRENT ) == 0 )
#else
	if( SetFilePointerEx(
	     internal_file->handle,
	     large_integer_offset,
	     &large_integer_offset,
	     FILE_CURRENT ) == 0 )
#endif
	{
		error_code = GetLastError();

		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 error_code,
		 "%s: unable to seek offset in file.",
		 function );

		return( -1 );
	}
#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
	*offset = (off64_t) large_integer_offset.QuadPart;
#else
	*offset = ( (off64_t) large_integer_offset.HighPart << 32 ) + large_integer_offset.LowPart;
#endif

	if( *offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: invalid offset: %" PRIi64 " returned.",
		 function,
		 *offset );

		return( -1 );
	}
	return( 1 );
}

#elif defined( HAVE_LSEEK ) || defined( WINAPI )

/* Retrieves the current offset in the file
 * This function uses the POSIX lseek function or equivalent
 * Returns 1 if successful or -1 on error
 */
int libcfile_file_get_offset(
     libcfile_file_t *file,
     off64_t *offset,
     libcerror_error_t **error )
{
	libcfile_internal_file_t *internal_file = NULL;
	static char *function                   = "libcfile_file_get_offset";

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
	internal_file = (libcfile_internal_file_t *) file;

	if( internal_file->descriptor == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing descriptor.",
		 function );

		return( -1 );
	}
	if( offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset.",
		 function );

		return( -1 );
	}
#if defined( WINAPI )
	*offset = _lseeki64(
	           internal_file->descriptor,
	           0,
	           SEEK_CUR );
#else
	*offset = lseek(
	           internal_file->descriptor,
	           0,
	           SEEK_CUR );
#endif
	if( *offset < 0 )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 errno,
		 "%s: unable to seek offset in file.",
		 function );

		return( -1 );
	}
	return( 1 );
}

#else
#error Missing file lseek function
#endif

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )

/* Retrieves the size of the file
 * This function uses the WINAPI function for Windows XP (0x0501) or later
 * or tries to dynamically call the function for Windows 2000 (0x0500) or earlier
 * Returns 1 if successful or -1 on error
 */
int libcfile_file_get_size(
     libcfile_file_t *file,
     size64_t *size,
     libcerror_error_t **error )
{
	libcfile_internal_file_t *internal_file = NULL;
	static char *function                   = "libcfile_file_get_size";
	LARGE_INTEGER large_integer_size        = LIBCFILE_LARGE_INTEGER_ZERO;

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
	internal_file = (libcfile_internal_file_t *) file;

	if( internal_file->handle == INVALID_HANDLE_VALUE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing handle.",
		 function );

		return( -1 );
	}
	if( size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid size.",
		 function );

		return( -1 );
	}
/* TODO implement device support ? */
#if ( WINVER <= 0x0500 )
	if( libcfile_GetFileSizeEx(
	     internal_file->handle,
	     &large_integer_size ) == 0 )
#else
	if( GetFileSizeEx(
	     internal_file->handle,
	     &large_integer_size ) == 0 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file size.",
		 function );

		return( -1 );
	}
#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x520
	*size = (size64_t) large_integer_size.QuadPart;
#else
	*size = ( (size64_t) large_integer_size.HighPart << 32 ) + large_integer_size.LowPart;
#endif
	return( 1 );
}

#elif defined( HAVE_FSTAT ) || defined( WINAPI )

/* Retrieves the size of the file
 * This function uses the POSIX fstat function or equivalent
 * Returns 1 if successful or -1 on error
 */
int libcfile_file_get_size(
     libcfile_file_t *file,
     size64_t *size,
     libcerror_error_t **error )
{
#if defined( _MSC_VER )
	struct __stat64 file_statistics;
#elif defined( __BORLANDC__ )
	struct stati64 file_statistics;
#else
	struct stat file_statistics;
#endif

	libcfile_internal_file_t *internal_file = NULL;
	static char *function                   = "libcfile_file_get_size";
	size_t file_statistics_size             = 0;

#if defined( S_ISBLK ) && defined( S_ISCHR )
	off64_t current_offset                  = 0;
	off64_t offset                          = 0;
#endif

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
	internal_file = (libcfile_internal_file_t *) file;

	if( internal_file->descriptor == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing descriptor.",
		 function );

		return( -1 );
	}
	if( size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid size.",
		 function );

		return( -1 );
	}
#if defined( _MSC_VER )
	file_statistics_size = sizeof( struct __stat64 );
#elif defined( __BORLANDC__ )
	file_statistics_size = sizeof( struct stati64 );
#else
	file_statistics_size = sizeof( struct stat );
#endif

	if( memory_set(
	     &file_statistics,
	     0,
	     file_statistics_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file statistics.",
		 function );

		return( -1 );
	}
#if defined( _MSC_VER )
	if( _fstat64(
	     internal_file->descriptor,
	     &file_statistics ) != 0 )
#elif defined( __BORLANDC__ )
	if( _fstati64(
	     internal_file->descriptor,
	     &file_statistics ) != 0 )
#else
	if( fstat(
	     internal_file->descriptor,
	     &file_statistics ) != 0 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file statistics.",
		 function );

		return( -1 );
	}
/* TODO implement device support ? */
/* TODO does not work on Mac OS X or WINAPI */
#if defined( S_ISBLK ) && defined( S_ISCHR )
	if( S_ISBLK( file_statistics.st_mode )
	 || S_ISCHR( file_statistics.st_mode ) )
	{
		if( libcfile_file_get_offset(
		     file,
		     &current_offset,
		     error ) != 1  )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve current offset.",
			 function );

			return( -1 );
		}
		/* If the file is a device try to seek the end of the file
		 */
		offset = libcfile_file_seek_offset(
		          file,
		          0,
		          SEEK_END,
		          error );

		if( offset == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to seek end of file.",
			 function );

			return( -1 );
		}
		*size = (size64_t) offset;

		offset = libcfile_file_seek_offset(
		          file,
		          current_offset,
		          SEEK_SET,
		          error );

		if( offset == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to seek offset: %" PRIi64 ".",
			 function,
			 current_offset );

			return( -1 );
		}
	}
	else
#endif
	{
		*size = (size64_t) file_statistics.st_size;
	}
	return( 1 );
}

#else
#error Missing file get size function
#endif

