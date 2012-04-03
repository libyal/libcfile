/*
 * File functions
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

#if !defined( _LIBCFILE_INTERNAL_FILE_H )
#define _LIBCFILE_INTERNAL_FILE_H

#include <common.h>
#include <types.h>

#include "libcfile_extern.h"
#include "libcfile_libcerror.h"
#include "libcfile_libcstring.h"
#include "libcfile_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libcfile_internal_file libcfile_internal_file_t;

struct libcfile_internal_file
{
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	HANDLE handle;
#else
	int descriptor;
#endif
};

LIBCFILE_EXTERN \
int libcfile_file_initialize(
     libcfile_file_t **file,
     libcerror_error_t **error );

LIBCFILE_EXTERN \
int libcfile_file_free(
     libcfile_file_t **file,
     libcerror_error_t **error );

LIBCFILE_EXTERN \
int libcfile_file_open(
     libcfile_file_t *file,
     const libcstring_system_character_t *filename,
     int access_flags,
     libcerror_error_t **error );

LIBCFILE_EXTERN \
int libcfile_file_close(
     libcfile_file_t *file,
     libcerror_error_t **error );

LIBCFILE_EXTERN \
ssize_t libcfile_file_read(
         libcfile_file_t *file,
         uint8_t *buffer,
         size_t size,
         libcerror_error_t **error );

LIBCFILE_EXTERN \
ssize_t libcfile_file_write(
         libcfile_file_t *file,
         uint8_t *buffer,
         size_t size,
         libcerror_error_t **error );

LIBCFILE_EXTERN \
off64_t libcfile_file_seek_offset(
         libcfile_file_t *file,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

LIBCFILE_EXTERN \
int libcfile_file_resize(
     libcfile_file_t *file,
     size64_t size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

