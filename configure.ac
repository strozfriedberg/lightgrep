# Process this file with autoconf to produce a configure script.
# TODO: 2.69 is likely not the least minimum autoconf which would work for us
AC_PREREQ([2.69])
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
AC_CHECK_HEADERS([libintl.h malloc.h])

# TODO: check that we're using these properly
AC_FUNC_ALLOCA
AC_FUNC_MALLOC

#
# dependent libs
#

# ICU checks
AX_CHECK_ICU(1.48)
#AC_CHECK_HEADERS([unicode/uchar.h unicode/uset.h unicode/ucnv.h unicode/ustring.h])
#PKG_PROG_PKG_CONFIG
#PKG_CHECK_MODULES([ICU], [icu-uc >= 48])

# FIXME: --disable-boost should be impossible
AX_BOOST_BASE([1.49.0])

#
# tests
#
AC_ARG_ENABLE([tests],
  [AS_HELP_STRING([--enable-tests], [build the test framework])],
  [enable_tests=$enableval],
  [enable_tests=yes])

if test "x${enable_tests}" = "xyes"; then
  # FIXME: disabling these should be impossible if tests are enabled
  AX_BOOST_PROGRAM_OPTIONS
  AX_BOOST_THREAD
  AX_BOOST_SYSTEM

  # FIXME: disabling scope should be impossible if tests are enabled 
  AC_ARG_WITH([scope],
    [AS_HELP_STRING([--with-scope], [])],
    [SCOPE_CPPFLAGS="-I$withval"],
    [SCOPE_CPPFLAGS="-Ivendors/scope"])
  # FIXME: check that scope is actually there and usable
  #AC_CHECK_HEADERS([scope/test.h], [], [], [-I])
  AC_SUBST([SCOPE_CPPFLAGS])
fi

AC_OUTPUT
