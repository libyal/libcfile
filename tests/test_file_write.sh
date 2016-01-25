#!/bin/bash
# Library write testing script
#
# Version: 20160125

EXIT_SUCCESS=0;
EXIT_FAILURE=1;
EXIT_IGNORE=77;

TEST_PREFIX="cfile";
TEST_EXECUTABLE="${TEST_PREFIX}_test_file_write";

test_write()
{ 
	FILENAME=$1;
	FILE_SIZE=$2;

	TMPDIR="tmp$$";

	rm -rf ${TMPDIR};
	mkdir ${TMPDIR};

	${TEST_RUNNER} ${TMPDIR} ./${TEST_WRITE} "${TMPDIR}/${FILENAME}" ${FILE_SIZE};

	RESULT=$?;

	rm -rf ${TMPDIR};

	return ${RESULT};
}

TEST_WRITE="./${TEST_EXECUTABLE}";

if ! test -x ${TEST_WRITE};
then
	TEST_WRITE="${TEST_EXECUTABLE}.exe";
fi

if ! test -x ${TEST_WRITE};
then
	echo "Missing executable: ${TEST_WRITE}";

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

if ! test_write "test1" 0;
then
	echo "";

	exit ${EXIT_FAILURE};
fi

if ! test_write "test2" 100000;
then
	echo "";

	exit ${EXIT_FAILURE};
fi

echo "";

exit ${EXIT_SUCCESS};

