/*
 * Functions for testing
 *
 * Copyright (C) 2008-2023, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _CFILE_TEST_FUNCTIONS_H )
#define _CFILE_TEST_FUNCTIONS_H

#include <common.h>
#include <types.h>

#include "cfile_test_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

int cfile_test_get_narrow_source(
     const system_character_t *source,
     char *narrow_string,
     size_t narrow_string_size,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

int cfile_test_get_wide_source(
     const system_character_t *source,
     wchar_t *wide_string,
     size_t wide_string_size,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

int cfile_test_get_temporary_filename(
     char *temporary_filename,
     size_t temporary_filename_size,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

int cfile_test_get_temporary_filename_wide(
     wchar_t *temporary_filename,
     size_t temporary_filename_size,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _CFILE_TEST_FUNCTIONS_H ) */

