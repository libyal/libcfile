/*
 * Support functions
 *
 * Copyright (c) 2008-2012, Joachim Metz <jbmetz@users.sourceforge.net>
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
#include <types.h>

#if defined( HAVE_SYS_STAT_H ) || defined( WINAPI )
#include <sys/stat.h>
#endif

#if defined( HAVE_ERRNO_H ) || defined( WINAPI )
#include <errno.h>
#endif

#include "libcfile_definitions.h"
#include "libcfile_libcerror.h"
#include "libcfile_libcstring.h"
#include "libcfile_support.h"

#if !defined( HAVE_LOCAL_LIBCFILE )

/* Returns the library version as a string
 */
const char *libcfile_get_version(
             void )
{
	return( (const char *) LIBCFILE_VERSION_STRING );
}

#endif /* !defined( HAVE_LOCAL_LIBCFILE ) */

#if defined( WINAPI ) && ( WINVER >= 0x0500 ) && !defined( USE_CRT_FUNCTIONS )

/* Determines if a file exists
 * This function uses the WINAPI functions for Windows 2000 or later
 * Returns 1 if the file exists, 0 if not or -1 on error
 */
int libcfile_file_exists(
     const libcstring_system_character_t *filename,
     libcerror_error_t **error )
{
	static char *function = "libcfile_file_exists";
	int result            = 1;
	DWORD error_code      = 0;
	DWORD file_attributes = 0;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	/* Must use GetFileAttributesW here because filename is a 
	 * wide character string and GetFileAttributes is dependent
	 * on UNICODE directives
	 */
	file_attributes = GetFileAttributesW(
	                   (LPCWSTR) filename );
#else
	/* Must use GetFileAttributesA here because filename is a 
	 * narrow character string and GetFileAttributes is dependent
	 * on UNICODE directives
	 */
	file_attributes = GetFileAttributesA(
	                   (LPCSTR) filename );
#endif
	if( file_attributes == INVALID_FILE_ATTRIBUTES )
	{
		error_code = GetLastError();

		switch( error_code )
		{
			case ERROR_ACCESS_DENIED:
				result = 1;

				break;

			case ERROR_FILE_NOT_FOUND:
			case ERROR_PATH_NOT_FOUND:
				result = 0;

				break;

			default:
				libcerror_system_set_error(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_GENERIC,
				 error_code,
				 "%s: unable to determine attributes of file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				return( -1 );
		}
	}
	return( result );
}

#elif defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )

/* Determines if a file exists
 * This function uses the WINAPI functions for Windows NT4 or earlier
 * Returns 1 if the file exists, 0 if not or -1 on error
 */
int libcfile_file_exists(
     const libcstring_system_character_t *filename,
     libcerror_error_t **error )
{
	HANDLE file_handle    = INVALID_HANDLE_VALUE;
	static char *function = "libcfile_file_exists";
	int result            = 1;
	DWORD error_code      = 0;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	/* Must use CreateFileW here because filename is a 
	 * wide character string and CreateFile is dependent
	 * on UNICODE directives
	 */
	file_handle = CreateFileW(
	               (LPCWSTR) filename,
	               GENERIC_READ,
	               FILE_SHARE_READ,
	               NULL,
	               OPEN_EXISTING,
	               FILE_ATTRIBUTE_NORMAL,
	               NULL );
#else
	/* Must use CreateFileA here because filename is a 
	 * narrow character string and CreateFile is dependent
	 * on UNICODE directives
	 */
	file_handle = CreateFileA(
	               (LPCSTR) filename,
	               GENERIC_READ,
	               FILE_SHARE_READ,
	               NULL,
	               OPEN_EXISTING,
	               FILE_ATTRIBUTE_NORMAL,
	               NULL );
#endif
	if( file_handle == INVALID_HANDLE_VALUE )
	{
		error_code = GetLastError();

		switch( error_code )
		{
			case ERROR_ACCESS_DENIED:
				result = 1;

				break;

			case ERROR_FILE_NOT_FOUND:
			case ERROR_PATH_NOT_FOUND:
				result = 0;

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

				return( -1 );
		}
	}
	else
	{
		if( CloseHandle(
		     file_handle ) == 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close file: %s.",
			 function,
			 filename );

			return( -1 );
		}
		file_handle = INVALID_HANDLE_VALUE;
	}
	return( result );
}

#elif defined( HAVE_STAT ) && !defined( WINAPI )

/* Determines if a file exists
 * This function uses the POSIX stat function or equivalent
 * Returns 1 if the file exists, 0 if not or -1 on error
 */
int libcfile_file_exists(
     const libcstring_system_character_t *filename,
     libcerror_error_t **error )
{
	struct stat file_statistics;

	static char *function = "libcfile_file_exists";
	int result            = 0;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
#error Missing wide character stat function
#endif
	result = stat(
	          (char *) filename,
	          &file_statistics );

	if( result != 0 )
	{
		switch( errno )
		{
			case EACCES:
				result = 1;

				break;

			case ENOENT:
				result = 0;

				break;

			default:
				libcerror_system_set_error(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_GENERIC,
				 errno,
				 "%s: unable to stat file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				return( -1 );
		}
	}
	else
	{
		result = 1;
	}
	return( result );
}

#elif ( defined( HAVE_OPEN ) && defined( HAVE_CLOSE ) ) || defined( WINAPI )

/* Determines if a file exists
 * This function uses the file open and close functions
 * Returns 1 if the file exists, 0 if not or -1 on error
 */
int libcfile_file_exists(
     const libcstring_system_character_t *filename,
     libcerror_error_t **error )
{
	static char *function = "libcfile_file_exists";
	int file_descriptor   = -1;
	int result            = 1;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
#if defined( _MSC_VER )
	if( _wsopen_s(
	     &file_descriptor,
	     (wchar_t *) filename,
	     _O_RDONLY | _O_BINARY,
	     _SH_DENYWR,
	     0 ) != 0 )
	{
		file_descriptor = -1;
	}
#elif defined( WINAPI )
	file_descriptor = _wsopen(
	                   (wchar_t *) filename,
	                   _O_RDONLY | _O_BINARY,
	                   0 );
#else
#error Missing wide character open function
#endif

#else
#if defined( _MSC_VER )
	if( _sopen_s(
	     &file_descriptor,
	     (char *) filename,
	     _O_RDONLY | _O_BINARY,
	     _SH_DENYWR,
	     0 ) != 0 )
	{
		file_descriptor = -1;
	}
#elif defined( WINAPI )
	file_descriptor = _sopen(
	                   (char *) filename,
	                   _O_RDONLY | _O_BINARY,
	                   0 );
#else
	file_descriptor = open(
	                   (char *) filename,
	                   O_RDONLY,
	                   0644 );
#endif
#endif
	if( file_descriptor == -1 )
	{
		switch( errno )
		{
			case EACCES:
				result = 1;

				break;

			case ENOENT:
				result = 0;

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

				return( -1 );
		}
	}
	else
	{
#if defined( WINAPI )
		if( _close(
		     file_descriptor ) != 0 )
#else
		if( close(
		     file_descriptor ) != 0 )
#endif
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close file: %s.",
			 function,
			 filename );

			return( -1 );
		}
		file_descriptor = -1;
	}
	return( result );
}

#else
#error Missing file exists function
#endif

