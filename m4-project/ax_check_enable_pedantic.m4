# SYNOPSIS
#
#   AX_CHECK_ENABLE_PEDANTIC([yes|no])
#
# DESCRIPTION
#
#   Check for the presence of an --enable-pedantic option to configure, with
#   the specified default value used when the option is not present. Return
#   the value in the variable $ax_enable_pedantic.
#
#   Specifying 'yes' adds '-Wall -pedantic -pedantic-errors' to the compilation
#   flags for the C and C++ languages.
#
#   Should be invoked prior to any AC_PROG_* compiler checks.
#
# LICENSE
#
#   Copyright (c) 2014 Plamen Ivanov <qnq6666@gmail.com>
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved.

AC_DEFUN([AX_CHECK_ENABLE_PEDANTIC],[
    m4_define(ax_enable_pedantic_default, [m4_tolower(m4_normalize(ifelse([$1],,[no],[$1])))])

    AC_MSG_CHECKING(whether to enable pedantic mode)

    AC_ARG_ENABLE(pedantic,
        [AS_HELP_STRING([--enable-pedantic]@<:@=ax_enable_pedantic_default@:>@,
                        [enable rigorous compile for C/C++]
                        [all warnings and uses of features outside the given standard])],
        [],
        [enable_pedantic=ax_enable_pedantic_default]
    )
    if test "x$enable_pedantic" = "xyes"; then
        AC_MSG_RESULT(yes)
        CFLAGS="${CFLAGS} -Wall -pedantic -pedantic-errors"
        CXXFLAGS="${CXXFLAGS} -Wall -pedantic -pedantic-errors"
    else
        AC_MSG_RESULT(no)
    fi
    ax_enable_pedantic=$enable_pedantic
])