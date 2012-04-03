/*
 * The extern definition
 * This header should be included in header files that export or import
 * library functions
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

#if !defined( _LIBCFILE_EXTERN_H )
#define _LIBCFILE_EXTERN_H

/* To export functions from the libcfile DLL define LIBCFILE_DLL_EXPORT
 * To import functions from the libcfile DLL define LIBCFILE_DLL_IMPORT
 * Otherwise use default extern statement
 */
#if defined( LIBCFILE_DLL_EXPORT )
#define LIBCFILE_EXTERN __declspec(dllexport)

#elif defined( LIBCFILE_DLL_IMPORT )
#define LIBCFILE_EXTERN extern __declspec(dllimport)

#else
#define LIBCFILE_EXTERN extern

#endif

#endif
