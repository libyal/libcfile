#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libcfile/.libs/libcfile.1.dylib && test -f ./pycfile/.libs/pycfile.so;
then
	install_name_tool -change /usr/local/lib/libcfile.1.dylib ${PWD}/libcfile/.libs/libcfile.1.dylib ./pycfile/.libs/pycfile.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

