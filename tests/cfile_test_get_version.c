/*
 * Library get version test program
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

#include "cfile_test_libcfile.h"
#include "cfile_test_libcstring.h"
#include "cfile_test_macros.h"
#include "cfile_test_unused.h"

/* Tests retrieving the library version
 * Returns 1 if successful or 0 if not
 */
int cfile_test_get_version(
     void )
{
	const char *version_string = NULL;
	int result                 = 0;

	version_string = libcfile_get_version();

	result = libcstring_narrow_string_compare(
	          version_string,
	          LIBCFILE_VERSION_STRING,
	          9 );

	CFILE_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 0 );

	return( 1 );

on_error:
	return( 0 );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
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

	CFILE_TEST_RUN(
	 "libcfile_get_version",
	 cfile_test_get_version() )

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

