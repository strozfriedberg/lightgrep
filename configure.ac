# Process this file with autoconf to produce a configure script.
# TODO: Unknown whether 2.64 works; was a bit of a milestone release, though
AC_PREREQ([2.64])
# TODO: required versions for automake, libtool?

AC_INIT([liblightgrep], [0.0], [BUG-REPORT-ADDRESS])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([src/lib/vm.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

AM_INIT_AUTOMAKE([subdir-objects])
LT_INIT

#
# common
#
AC_PROG_CC
AC_PROG_CXX
AM_PROG_CC_C_O

AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])

AC_CHECK_HEADERS([stddef.h])

# TODO: check debug builds
# don't standardly compile with debug symbols
CFLAGS=`echo "$CFLAGS" | sed s/-g//`
CXXFLAGS=`echo "$CXXFLAGS" | sed s/-g//`

# TODO: check whether this overrides setting CXXFLAGS from command line
# compile with -O3, not -O2
CFLAGS=`echo "$CFLAGS" | sed s/-O2/-O3/`
CXXFLAGS=`echo "$CXXFLAGS" | sed s/-O2/-O3/`

AC_PROG_INSTALL

#
# regex grammar
#
AX_PROG_BISON
AC_CHECK_HEADERS([libintl.h])

#
# ICU
#
AX_CHECK_ICU(1.48)
#AC_CHECK_HEADERS([unicode/uchar.h unicode/uset.h unicode/ucnv.h unicode/ustring.h])

#
# Boost headers
#
# FIXME: --disable-boost should be impossible
AX_BOOST_BASE([1.49.0])

#
# tests
#
AX_BOOST_PROGRAM_OPTIONS
AX_BOOST_SYSTEM
AX_BOOST_THREAD

AC_ARG_WITH([scope],
  [AS_HELP_STRING([--with-scope], [])],
  [SCOPE_CPPFLAGS="-I$withval"],
  [SCOPE_CPPFLAGS="-Ivendors/scope"])
# FIXME: check that scope is actually there and usable
#AC_CHECK_HEADERS([scope/test.h], [], [], [-I])
AC_SUBST([SCOPE_CPPFLAGS])

if test "x$ax_cv_boost_program_options" != "xyes" -o \
        "x$ax_cv_boost_system" != "xyes" -o \
        "x$ax_cv_boost_thread" != "xyes"; then 
  echo
  echo "WARNING: You will not be able to compile and run the tests because:"
  echo
  if test "x$ax_cv_boost_program_options" != "xyes"; then
    echo "  * boost::program_options is unavailable"
  fi
  if test "x$ax_cv_boost_system" != "xyes"; then
    echo "  * boost::system is unavailable"
  fi
  if test "x$ax_cv_boost_thread" != "xyes"; then
    echo "  * boost::thread is unavailable"
  fi
# TODO: add scope check here
  echo
fi

AC_OUTPUT
