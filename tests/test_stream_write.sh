#!/bin/bash
#
# Library stream write testing script
#
# Copyright (C) 2008-2016, Joachim Metz <joachim.metz@gmail.com>
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

EXIT_SUCCESS=0;
EXIT_FAILURE=1;
EXIT_IGNORE=77;

test_stream_write()
{ 
	FILENAME=$1;
	FILE_SIZE=$2;

	TMPDIR="tmp$$";

	rm -rf ${TMPDIR};
	mkdir ${TMPDIR};

	${TEST_RUNNER} ${TMPDIR} ./${TEST_STREAM_WRITE} "${TMPDIR}/${FILENAME}" ${FILE_SIZE};

	RESULT=$?;

	rm -rf ${TMPDIR};

	return ${RESULT};
}

TEST_STREAM_WRITE="cfile_test_stream_write";

if ! test -x ${TEST_STREAM_WRITE};
then
	TEST_STREAM_WRITE="cfile_test_stream_write.exe";
fi

if ! test -x ${TEST_STREAM_WRITE};
then
	echo "Missing executable: ${TEST_STREAM_WRITE}";

	exit ${EXIT_FAILURE};
fi

TEST_RUNNER="tests/test_runner.sh";

if ! test -x ${TEST_RUNNER};
then
        TEST_RUNNER="./test_runner.sh";
fi

if ! test -x ${TEST_RUNNER};
then
        echo "Missing test runner: ${TEST_RUNNER}";

        exit ${EXIT_FAILURE};
fi

echo "Testing write";

if ! test_stream_write "test1" 0;
then
	echo "";

	exit ${EXIT_FAILURE};
fi

if ! test_stream_write "test2" 100000;
then
	echo "";

	exit ${EXIT_FAILURE};
fi

echo "";

exit ${EXIT_SUCCESS};

