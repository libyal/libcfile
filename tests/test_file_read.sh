#!/bin/bash
#
# Cross-platform C file functions library file read testing script
#
# Copyright (c) 2008-2013, Joachim Metz <joachim.metz@gmail.com>
#
# Refer to AUTHORS for acknowledgements.
#
# This software is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this software.  If not, see <http://www.gnu.org/licenses/>.
#

EXIT_SUCCESS=0;
EXIT_FAILURE=1;
EXIT_IGNORE=77;

INPUT="input";
TMP="tmp";

test_file_read()
{ 
	echo "Testing read of input:" $*;

	./${CFILE_TEST_FILE_READ} $*;

	RESULT=$?;

	echo "";

	return ${RESULT};
}

CFILE_TEST_FILE_READ="cfile_test_file_read";

if ! test -x ${CFILE_TEST_FILE_READ};
then
	CFILE_TEST_FILE_READ="cfile_test_file_read.exe";
fi

if ! test -x ${CFILE_TEST_FILE_READ};
then
	echo "Missing executable: ${CFILE_TEST_FILE_READ}";

	exit ${EXIT_FAILURE};
fi

if ! test -d ${INPUT};
then
	echo "No input directory found, to test read create input directory and place test files in directory.";

	exit ${EXIT_IGNORE};
fi

for FILENAME in ${INPUT}/*;
do
	if ! test_file_read ${FILENAME};
	then
		exit ${EXIT_FAILURE};
	fi
done

exit ${EXIT_SUCCESS};

