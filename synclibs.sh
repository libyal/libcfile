#!/bin/sh
# Script that synchronizes the local library dependencies
#
# Version: 20121224

GIT_URL_PREFIX="https://code.google.com/p"
LOCAL_LIBS="libcerror libclocale libcnotify libuna";

OLDIFS=$IFS;
IFS=" ";

for LOCAL_LIB in ${LOCAL_LIBS};
do
	git clone ${GIT_URL_PREFIX}/${LOCAL_LIB}/ ${LOCAL_LIB}-$$;

	if [ -d ${LOCAL_LIB}-$$ ];
	then
		LOCAL_LIB_UPPER=`echo "${LOCAL_LIB}" | tr "[a-z]" "[A-Z]"`;
		LOCAL_LIB_VERSION=`grep -A 2 AC_INIT ${LOCAL_LIB}-$$/configure.ac | tail -n 1 | sed 's/^\s*\[\([0-9]*\)\],\s*$/\1/'`;

		rm -rf ${LOCAL_LIB};
		mkdir ${LOCAL_LIB};

		if [ -d ${LOCAL_LIB} ];
		then
			cp ${LOCAL_LIB}-$$/${LOCAL_LIB}/*.[ch] ${LOCAL_LIB};

			cp ${LOCAL_LIB}-$$/${LOCAL_LIB}/Makefile.am ${LOCAL_LIB}/Makefile.am;
			sed "1i if HAVE_LOCAL_${LOCAL_LIB_UPPER}" -i ${LOCAL_LIB}/Makefile.am;
			sed "s/lib_LTLIBRARIES/noinst_LTLIBRARIES/" -i ${LOCAL_LIB}/Makefile.am;
			sed "/${LOCAL_LIB}.c/ { d }" -i ${LOCAL_LIB}/Makefile.am;
			sed "s/${LOCAL_LIB}_la_LDFLAGS = .*$/endif/" -i ${LOCAL_LIB}/Makefile.am;
			sed "/EXTRA_DIST = / { N; N; N; N; d }" -i ${LOCAL_LIB}/Makefile.am;
			sed "/distclean: clean/ { n; N; d }" -i ${LOCAL_LIB}/Makefile.am;
			rm -f ${LOCAL_LIB}/${LOCAL_LIB}.c;

			cp ${LOCAL_LIB}-$$/${LOCAL_LIB}/${LOCAL_LIB}_definitions.h.in ${LOCAL_LIB}/${LOCAL_LIB}_definitions.h;
			sed 's/@VERSION@/${LOCAL_LIB_VERSION}/' -i ${LOCAL_LIB}/${LOCAL_LIB}_definitions.h;
		fi
		rm -rf ${LOCAL_LIB}-$$;
	fi
done

IFS=$OLDIFS;

