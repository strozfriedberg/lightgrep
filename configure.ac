# Process this file with autoconf to produce a configure script.
# TODO: Unknown whether 2.64 works; was a bit of a milestone release, though
AC_PREREQ([2.64])
# TODO: required versions for automake, libtool?

AC_INIT([liblightgrep], [0.0], [BUG-REPORT-ADDRESS])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([src/lib/vm.cpp])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([subdir-objects])
LT_INIT

#
# common
#

# set the default compilation flags to -O3, not -g -O2
: ${CFLAGS="-O3"}
: ${CXXFLAGS="-O3"}

AC_PROG_CC
AC_PROG_CXX

AM_PROG_CC_C_O

AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])

AC_CHECK_HEADERS([stddef.h])

AC_PROG_INSTALL

#
# regex grammar
#
AX_PROG_BISON

# libintl.h would be necessary if we used Bison's i18n setup
#AC_CHECK_HEADERS([libintl.h])

#
# ICU
#
AX_CHECK_ICU(1.48)

#
# Boost headers
#
if test "x$with_boost" = "xno"; then
  AC_MSG_ERROR([--without-boost specified, but Boost is mandatory.])
else
  AX_BOOST_BASE([1.49.0],
    [],
    [AC_MSG_ERROR([Failed to find usable Boost headers.])])
fi

#
# tests
#

# Boost libs used by tests
AX_BOOST_PROGRAM_OPTIONS
AX_BOOST_SYSTEM
AX_BOOST_THREAD

# Scope test framework
AC_ARG_WITH([scope],
  [AS_HELP_STRING([--with-scope], [])],
  [SCOPE_CPPFLAGS="-I$withval"],
  [SCOPE_CPPFLAGS="-Ivendors/scope"])

if test "x$with_scope" != "xno"; then
  # test Scope without adding its path to CPPFLAGS generally
  CPPFLAGS_saved="$CPPFLAGS"
  CPPFLAGS="$SCOPE_CPPFLAGS"
  export CPPFLAGS

  AC_CHECK_HEADERS([scope/test.h],[scope_ok="yes"])

  CPPFLAGS="$CPPFLAGS_saved"

  if test "x$scope_ok" = "xyes"; then
    AC_DEFINE(HAVE_SCOPE,1,[Define to 1 if Scope test framework is available.])
    AC_SUBST([SCOPE_CPPFLAGS])
  fi
fi

# Tell the user why not if he won't be able to compile the tests
if test "x$ax_cv_boost_program_options" != "xyes" || \
   test "x$ax_cv_boost_system" != "xyes" || \
   test "x$ax_cv_boost_thread" != "xyes" || \
   test "x$scope_ok" != "xyes"; then
  AC_MSG_WARN([])
  AC_MSG_WARN([You will be unable to compile and run the tests because:])
  AC_MSG_WARN([])
  if test "x$ax_cv_boost_program_options" != "xyes"; then
    AC_MSG_WARN([  * boost::program_options is unavailable])
  fi
  if test "x$ax_cv_boost_system" != "xyes"; then
    AC_MSG_WARN([  * boost::system is unavailable])
  fi
  if test "x$ax_cv_boost_thread" != "xyes"; then
    AC_MSG_WARN([  * boost::thread is unavailable])
  fi
  if test "x$scope_ok" != "xyes"; then
    AC_MSG_WARN([  * Scope test framework is unavailable])
  fi
  AC_MSG_WARN([])
fi

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
