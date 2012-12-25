#!/bin/sh
# Script to generate ./configure using the autotools
#
# Version: 20121222

EXIT_SUCCESS=0;
EXIT_FAILURE=1;

ACLOCAL="/usr/bin/aclocal";
AUTOCONF="/usr/bin/autoconf";
AUTOMAKE="/usr/bin/automake";
AUTOPOINT="/usr/bin/autopoint";
LIBTOOLIZE="/usr/bin/libtoolize";

if [ ! -x "${ACLOCAL}" ];
then
	echo "Unable to find: aclocal";

	echo ${EXIT_FAILURE};
fi

if [ ! -x "${AUTOCONF}" ];
then
	echo "Unable to find: autoconf";

	echo ${EXIT_FAILURE};
fi

if [ ! -x "${AUTOMAKE}" ];
then
	echo "Unable to find: automake";

	echo ${EXIT_FAILURE};
fi

if [ ! -x "${AUTOPOINT}" ];
then
	echo "Unable to find: autopoint";

	echo ${EXIT_FAILURE};
fi

if [ ! -x "${LIBTOOLIZE}" ];
then
	echo "Unable to find: libtoolize";

	echo ${EXIT_FAILURE};
fi

${AUTOPOINT} --force
${ACLOCAL} --force -I m4
${LIBTOOLIZE} --force
${AUTOCONF} --force
${AUTOMAKE} --force --add-missing

exit ${EXIT_SUCCESS};

