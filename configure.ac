# Process this file with autoconf to produce a configure script.
# TODO: Unknown whether 2.64 works; was a bit of a milestone release, though
AC_PREREQ([2.64])
# TODO: required versions for automake, libtool?

AC_INIT([liblightgrep], [0.0], [BUG-REPORT-ADDRESS])

# Set the default C and C++ compilation flags to -O3, not -g -O2
# Do this immediately after AC_INIT, as other macros might invoke
# AC_PROG_CC or AC_PROG_CXX and stomp our defaults.
: ${CFLAGS="-O3"}
: ${CXXFLAGS="-O3"}

AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([src/lib/vm.cpp])
AC_CONFIG_HEADERS([config.h])

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
# FIXME: icu-config from ICU cross-compiled with mingw wants libicuuc.dll,
# which won't exist if ICU was compiled static only, so we temporarily add
# --noverify until we figure out what to do about this.
ICU_CONFIG='icu-config --noverify'
AX_CHECK_ICU(1.48)

# FIMXE: ICU produces some bullshit flags we don't want, don't want
# duplicated, or don't want with clang. There's got to be a better
# way of removing flags/removing duplicate flags than using sed.
ICU_CXXFLAGS=`echo "$ICU_CXXFLAGS" | sed 's/-O2 -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2//'`
ICU_CXXFLAGS=`echo "$ICU_CXXFLAGS" | sed 's/-W -Wall -ansi -pedantic//'`
ICU_LIBS=`echo "$ICU_LIBS" | sed 's/-licui18n//'`

#
# ICU_CXXFLAGS we don't want anywhere:
#   -ansi
#
# ICU_CXXFLAGS which conflict with ones we might set:
#   -O2
#   -g
#
# ICU_CXXFLAGS which duplicate ours:
#   -pedantic
#   -W
#   -Wall
#   -pipe
#
# ICU_CXXFLAGS which cause clang to freak out on Fedora 18:
#   -Wp,-D_FORTIFY_SOURCE=2
#
#
# ICU_LIBS which are wrong on Mac OS X, Windows:
#   -pthread
#
# ICU_LIBS which are wrong everywhere:
#   -licui18n
#

#
# Boost headers
#
if test "x$with_boost" = "xno"; then
  AC_MSG_ERROR([--without-boost specified, but Boost is mandatory.])
else
  case "$host" in
  *-*-mingw*)
    # AX_BOOST_BASE doesn't find the Boost libs for mingw, we help it out
    if test "$with_boost_libdir" = ""; then
      with_boost_libdir="/usr/${host}/sys-root/mingw/lib"
      AC_MSG_WARN([--with-boost-libdir not set. We are guessing ${with_boost_libdir}.])
    fi
    ;;
  esac

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
  [AS_HELP_STRING([--with-scope=ARG],
    [use Scope headers from the specified location])],
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

# TODO: thread flags
case "$host" in
*-*-mingw*)
  ICU_LIBS=`echo "$ICU_LIBS" | sed 's/-lpthread//g'`
  CPFLAGS+=' -mthreads'
  ;;
*-apple-darwin)
  ;;
*)
  CPPFLAGS+=' -pthread'
  ;;
esac

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
