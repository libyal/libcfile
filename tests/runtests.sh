#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libcfile/.libs/libcfile.1.dylib && test -f ./pycfile/.libs/pycfile.so
then
	install_name_tool -change /usr/local/lib/libcfile.1.dylib ${PWD}/libcfile/.libs/libcfile.1.dylib ./pycfile/.libs/pycfile.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

