# Process this file with autoconf to produce a configure script.
# TODO: Unknown whether 2.64 works; was a bit of a milestone release, though
AC_PREREQ([2.64])
# TODO: required versions for automake, libtool?

AC_INIT([liblightgrep], [1.3.0], [joel@lightboxtechnologies.com])

# Set the default C and C++ compilation flags to nothing.
# Do this immediately after AC_INIT, as other macros might invoke
# AC_PROG_CC or AC_PROG_CXX and stomp our defaults.
: ${CFLAGS=''}
: ${CXXFLAGS=''}

## FIXME: Argh, there appears to be no way to distinguish between the
## flags set by mingw64-configure and ones set by the user...
#AC_MSG_NOTICE([Default CPPFLAGS: $CPPFLAGS])
#AC_MSG_NOTICE([Default CFLAGS:   $CFLAGS])
#AC_MSG_NOTICE([Default CXXFLAGS: $CXXFLAGS])
#AC_MSG_NOTICE([Default LDFLAGS:  $LDFLAGS])

AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([src/lib/vm.cpp])
AC_CONFIG_HEADERS([config.h])

#AM_INIT_AUTOMAKE([1.12 foreign serial-tests subdir-objects])
AM_INIT_AUTOMAKE([foreign subdir-objects])
LT_INIT

#
# common
#
AC_PROG_CC
AC_PROG_CXX
AM_PROG_CC_C_O

AC_LANG([C])
AX_APPEND_COMPILE_FLAGS([-std=c1x -W -Wall -Wextra -pedantic -pipe -O3], [CFLAGS])

AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])
AX_APPEND_COMPILE_FLAGS([-W -Wall -Wextra -Wnon-virtual-dtor -pedantic -pipe -O3], [CXXFLAGS])

AC_PROG_INSTALL

# FIXME: mingw defaults to -g -O2, along with a bunch of other flags which
# we want to keep.
case "$host" in
*-*-mingw*)
  LG_REMOVE_FLAGS([CFLAGS], ['-g -O2'])
  LG_REMOVE_FLAGS([CXXFLAGS], ['-g -O2'])
  ;;
esac

#
# regex grammar
# check bison is installed and print its version
#
AX_PROG_BISON([printf "bison version is... " && bison --version | head -n 1])

# libintl.h would be necessary if we used Bison's i18n setup
#AC_CHECK_HEADERS([libintl.h])

#
# ICU
#

# Get the path to icu-config, if we want to use ICU other than the system one.
AC_ARG_WITH([icu],
  [AS_HELP_STRING([--with-icu=ARG],
    [use icu-config from the specified location])],
  [ICU_CONFIG="$withval"],
  [ICU_CONFIG=""])

if test -z "$ICU_CONFIG"; then
  AC_MSG_NOTICE([No path given for --with-icu, using icu-config from your PATH.])
else
  if test "x$ICU_CONFIG" = "xyes"; then
    AC_MSG_WARN([ICU_CONFIG = 'yes'. Did you forget to specify an argument for --with-icu?])
  fi

  # Add a trailing slash if we don't have one
  case "$ICU_CONFIG" in
  */) ;;
  *) ICU_CONFIG="${ICU_CONFIG}/" ;;
  esac

  # Check that icu-config exists
  if test ! -f "$ICU_CONFIG/icu-config"; then
    AC_MSG_ERROR([Path "${ICU_CONFIG}icu-config" does not exist])
  fi
fi

# FIXME: icu-config from ICU cross-compiled with mingw wants libicuuc.dll,
# which won't exist if ICU was compiled static only, so we temporarily add
# --noverify until we figure out what to do about this.
ICU_CONFIG="${ICU_CONFIG}icu-config --noverify"

AC_MSG_WARN([Disregard the next few lines where ICU_* are printed.])
AC_MSG_WARN([They're all wrong but we fix them up before using them.])
AX_CHECK_ICU(1.48)
echo 'found ICU' `icu-config --version`

# ICU_LIBS which are wrong on Windows (and we handle ourselves):
#   -lpthread
#
# ICU_LIBS which are wrong for static Windows builds:
#   -licuuc   -> -lsicuuc
#   -licudata -> -lsicudt
#
# ICU_LIBS which are wrong everywhere:
#   -licui18n
#
LG_REMOVE_FLAGS([ICU_LIBS], ['-licui18n -lpthread'])

# FIXME: On Windows, static ICU libs have names different from dynamic ones.
# This is problematic, because which should be linked against is known only
# when we know if we're statically or dynamically linking.
case "$host" in
*-*-mingw*)
  LG_REPLACE_FLAG([ICU_LIBS], [-licuuc],   [-lsicuuc])
  LG_REPLACE_FLAG([ICU_LIBS], [-licudata], [-lsicudt])
  ;;
esac

# ICU_C(XX)FLAGS we don't want anywhere:
#   -ansi -std=c99
#
# ICU_C(XX)FLAGS which conflict with ones we might set:
#   -O2 -O3 -g -pthread -mthreads
#
duff_icu_compile_flags='-ansi -g -O2 -O3 -std=c99 -pthread -mthreads'
if test x"$CXX" = "xclang++" ; then
  # These cause clang to freak out on Fedora 18
  duff_icu_compile_flags="$duff_icu_compile_flags -Wp,-D_FORTIFY_SOURCE=2"
fi

LG_REMOVE_FLAGS([ICU_CFLAGS],   [$duff_icu_compile_flags])
LG_REMOVE_FLAGS([ICU_CXXFLAGS], [$duff_icu_compile_flags])

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
      AC_MSG_NOTICE([--with-boost-libdir not set. We are guessing ${with_boost_libdir}.])
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
  if test "x$scope_ok" != "xyes"; then
    AC_MSG_WARN([  * Scope test framework is unavailable])
  fi
  AC_MSG_WARN([])
fi

# Boost ASIO needs ws2_32 and mswsock on Windows
case "$host" in
*-*-mingw*)
  BOOST_ASIO_LIB="-lws2_32 -lmswsock"
  AC_SUBST([BOOST_ASIO_LIB])
  ;;
esac

#
# Threading
# 
case "$host" in
*-*-mingw*)
  AX_APPEND_FLAG([-mthreads], [CPPLAGS])
  AX_APPEND_LINK_FLAGS([-mthreads], [LDFLAGS])
  ;;
*-apple-darwin*)
  ;;
*)
  AX_APPEND_FLAG([-pthread], [CPPFLAGS])
  AX_APPEND_LINK_FLAGS([-pthread], [LDFLAGS])
esac

#
# C++ library
#
case "$host" in
*-apple-darwin*)
  echo " ** MacOS X builds are problematic as compilers are in transition."
  echo " ** We presume you're using a recent clang and libc++."
  echo " ** And we recommend only building the library and not unit tests."
  echo " ** If you build the unit tests, you are entering a world of pain."
  AX_APPEND_COMPILE_FLAGS([-stdlib=libc++], [CXXFLAGS])
  # TODO: Actually linking against libc++ will require everything else down
  # the chain to have been linked with libc++, including Boost, ICU, etc.
  # So, don't do this just yet.
  # STDCXX_LIB='-lc++'
  STDCXX_LIB='-lstdc++'
  ;;
*)
  STDCXX_LIB='-lstdc++'
  ;;
esac

AC_SUBST([STDCXX_LIB])

# FIXME: need to add -install_name to LDFLAGS when building a dynamic lib
# for MacOS X.

# FIXME: Is this really the right way to do this?!
# Build dynamically-linked executables if we build dynamic libs
if test "x$enable_shared" != "xyes"; then
  CXXLD="$CXX -all-static"
  CCLD="$CC -all-static"

  AX_APPEND_COMPILE_FLAGS([-DBOOST_THREAD_USE_LIB], [BOOST_CPPFLAGS])

  case "$host" in
  *-*-mingw*)
    # FIXME: wrong boost_system lib gets detected!
    BOOST_SYSTEM_LIB=`echo "$BOOST_SYSTEM_LIB" | sed 's/.dll/-mt/'`
    ;;
  esac

  case "$host" in
  i686-*-mingw*)
    # FIXME: Really? This looks like it's just asking for trouble...
    AX_APPEND_LINK_FLAGS([-Wl,--allow-multiple-definition], [LDFLAGS])
    ;;
  esac
else
  CXXLD="$CXX"
  CCLD="$CC"
fi

AC_SUBST([CXXLD])
AC_SUBST([CCLD])

#
# Cleanup flags
#

# TODO: libtre has a nice display we can steal
AC_MSG_NOTICE([ICU_CPPFLAGS: $ICU_CPPFLAGS])
AC_MSG_NOTICE([ICU_CFLAGS:   $ICU_CFLAGS])
AC_MSG_NOTICE([ICU_CXXFLAGS: $ICU_CXXFLAGS])

AC_MSG_NOTICE([BOOST_CPPFLAGS: $BOOST_CPPFLAGS])
AC_MSG_NOTICE([BOOST_CXXFLAGS: $BOOST_CXXFLAGS])

AC_MSG_NOTICE([CC:       $CC])
AC_MSG_NOTICE([CXX:      $CXX])
AC_MSG_NOTICE([CPPFLAGS: $CPPFLAGS])
AC_MSG_NOTICE([CFLAGS:   $CFLAGS])
AC_MSG_NOTICE([CXXFLAGS: $CXXFLAGS])
AC_MSG_NOTICE([LIBS:     $LIBS])
AC_MSG_NOTICE([LDFLAGS:  $LDFLAGS])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
