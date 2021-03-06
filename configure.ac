#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([Cuttlefish], [0.1.experimental], [pivanov@foobar.ninja])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_SRCDIR([src/main.cc])
AC_CONFIG_HEADERS([config.h])
# M4 macros specific to this project.
AC_CONFIG_MACRO_DIR([m4-project])

# Init Automake.
AM_INIT_AUTOMAKE([1.15 subdir-objects readme-alpha no-dist no-dist-gzip -Wall])

# Add debug option.
AX_CHECK_ENABLE_DEBUG([no], [DEBUG])
AX_CHECK_ENABLE_PEDANTIC([no])

# Checks for programs.
AC_PROG_CC([clang gcc])
AC_PROG_CXX([clang++ c++ g++])
AC_PROG_CPP([clang gcc])
AC_PROG_INSTALL

# Enable PCH.
AX_PRECOMPILED_HEADERS([std.h])

# Checks for languages.
AC_LANG([C++])

# C++ checks.
AX_CXX_COMPILE_STDCXX_17([noext], [mandatory])

dnl # Checks for header files.
dnl AC_CHECK_HEADERS([gsl/gsl gsl/gsl_algorithm gsl/gsl_assert gsl/gsl_byte gsl/gsl_util gsl/multi_span gsl/span gsl/string_span],
dnl                           [],
dnl                           [AC_MSG_ERROR([GSL support headers missing.])
dnl ])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for libraries.
AX_CHECK_GL()

AX_BOOST_BASE([1.73],
        [],
        [AC_MSG_ERROR([Minimal Boost library requirments not met.])
])
# Header only as of 1.69
# AX_BOOST_SYSTEM
AX_BOOST_FILESYSTEM
AX_BOOST_DATE_TIME
AX_BOOST_CHRONO
AX_BOOST_LOG
AX_BOOST_THREAD
AX_BOOST_REGEX
dnl At this point, use the shared Boost libraries.
dnl TODO Use static linking later on.
AC_DEFINE([BOOST_ALL_DYN_LINK], [1], ["Boost dynamic library link flag"])

dnl Package checks.

dnl Check for SDL
AM_PATH_SDL2(2.0.4,
    :,
    AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!])
)
CFLAGS="$CFLAGS $SDL_CFLAGS"
CXXFLAGS="$CXXFLAGS $SDL_CFLAGS"
LIBS="$LIBS $SDL_LIBS"

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
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

 -- GL
 GL_CFLAGS: ${GL_CFLAGS}
 GL_LIBS: ${GL_LIBS}

 -- Boost
 BOOST_CPPFLAGS: ${BOOST_CPPFLAGS}
 BOOST_LDFLAGS: ${BOOST_LDFLAGS}

 -- SDL2
 SDL_CFLAGS: ${SDL_CFLAGS}
 SDL_LIBS: ${SDL_LIBS}

 -- Linker
 LDFLAGS: ${LDFLAGS}
 LIBOBJS: ${LIBOBJS}
 LIBS: ${LIBS}
 LTLIBOBJS: ${LTLIBOBJS}

 Now type 'make @<:@<target>@:>@'
   where the optional <target> is:
     all                - build all binaries

--------------------------------------------------"
