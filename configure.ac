#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([Cuttlefish], [0.1.experimental], [pivanov@foobar.ninja])
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

# Checks for header files.
AC_CHECK_HEADERS([gsl/gsl gsl/gsl_algorithm gsl/gsl_assert gsl/gsl_byte gsl/gsl_util gsl/multi_span gsl/span gsl/string_span],
        [],
        [AC_MSG_ERROR([GSL support headers missing.])
])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for libraries.
AX_CHECK_GL()

AX_BOOST_BASE([1.63],
        [],
        [AC_MSG_ERROR([Minimal Boost library requirments not met.])
])
AX_BOOST_SYSTEM
AX_BOOST_FILESYSTEM
AX_BOOST_DATE_TIME
AX_BOOST_CHRONO
AX_BOOST_LOG
AX_BOOST_THREAD

dnl Check for SDL
AM_PATH_SDL2(2.0.4,
    :,
    AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!])
)
CFLAGS="$CFLAGS $SDL_CFLAGS"
CXXFLAGS="$CXXFLAGS $SDL_CFLAGS"
LIBS="$LIBS $SDL_LIBS"

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
