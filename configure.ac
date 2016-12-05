#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([Cuttlefish Web Framework], [0.1.alpha2], [qnq6666@gmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])
# M4 macros specific to this project.
AC_CONFIG_MACRO_DIR([m4-project])

# Init Automake.
AM_INIT_AUTOMAKE([1.15 subdir-objects readme-alpha no-dist no-dist-gzip -Wall])

# Add debug option.
AX_CHECK_ENABLE_DEBUG([no], [DEBUG])
AX_CHECK_ENABLE_PEDANTIC([no])

# Checks for programs.
AC_PROG_CXX([clang++ c++ g++ gcc])
AC_PROG_INSTALL

# Enable PCH.
AX_PRECOMPILED_HEADERS([std.hpp])

# Checks for languages.
AC_LANG([C++])

# C++ checks.
AX_CXX_COMPILE_STDCXX_14([noext], [mandatory])

# Checks for libraries.
AX_PTHREAD
AX_BOOST_BASE([1.62],
		[],
		[AC_MSG_ERROR([Minimal Boost library requirments not met.])
])
AX_BOOST_SYSTEM
AX_BOOST_THREAD
AX_BOOST_ASIO
AX_BOOST_DATE_TIME

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT

echo \
"-------------------------------------------------

 ${PACKAGE_NAME} Version ${PACKAGE_VERSION}

 Prefix: '${prefix}'.
 Variables:
 
 ac_top_srcdir= ${ac_top_srcdir}
 
 -- Compiler
 CC: ${CC}
 CXX: ${CXX}
 CPP: ${CPP}
 CFLAGS: ${CFLAGS}
 CPPFLAGS: ${CPPFLAGS}
 CXXFLAGS: ${CXXFLAGS}
 
 -- Precompiled headers
 CFLAGS_PCH: ${CFLAGS_PCH}
 CXXFLAGS_PCH: ${CXXFLAGS_PCH}
 PCH_FILENAME: ${PCH_FILENAME}
 PCH_SOURCE_FILENAME: ${PCH_SOURCE_FILENAME}

 Now type 'make @<:@<target>@:>@'
   where the optional <target> is:
     all                - build all binaries

--------------------------------------------------"
