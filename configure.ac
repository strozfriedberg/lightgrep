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
AX_APPEND_COMPILE_FLAGS([-std=c1x -W -Wall -Wextra -pedantic -pipe -O3], [LG_CFLAGS])

AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])
AX_APPEND_COMPILE_FLAGS([-W -Wall -Wextra -Wnon-virtual-dtor -pedantic -pipe -O3], [LG_CXXFLAGS])

AC_PROG_INSTALL

# FIXME: mingw defaults to -g -O2, along with a bunch of other flags which
# we want to keep.
case "$host" in
*-*-mingw*)
  LG_REMOVE_FLAGS([CFLAGS], ['-O2'])
  LG_REMOVE_FLAGS([CXXFLAGS], ['-O2'])
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
# Fat or thin shared library?
#

AC_ARG_ENABLE([shared-fat],
  [AS_HELP_STRING([--enable-shared-fat],
    [statically link liblightgrep to its dependencies (MinGW only)])])

if test "x$enable_shared_fat" = "xyes"; then
  case "$host" in
  *-*-mingw*)
    if test "x$enable_shared" != "xyes"; then
      AC_MSG_ERROR([--enable-shared-fat requires --enable-shared.])
    fi
    echo "Enabling fat shared lib. Your shared liblightgrep is so fat, it will contain all of its dependencies."
    ;;
  *)
    AC_MSG_ERROR([--enable-shared-fat requires building with MinGW.])
    ;;
  esac
fi

#
# ICU
#

PKG_CHECK_MODULES([ICU], [icu-uc])

ICU_CPPFLAGS="$ICU_CFLAGS"
ICU_CFLAGS=""

AX_APPEND_COMPILE_FLAGS([ \
  -DU_USING_ICU_NAMESPACE=0 \
  -DU_CHARSET_IS_UTF8=1 \
  -DUNISTR_FROM_CHAR_EXPLICIT=explicit \
  -DUNSTR_FROM_STRING_EXPLICIT=explicit \
], [ICU_CPPFLAGS])

if test "x$enable_shared" != "xyes" -o "x$enable_shared_fat" = "xyes"; then
  AX_APPEND_COMPILE_FLAGS([-DU_STATIC_IMPLEMENTATION], [ICU_CPPFLAGS])
fi

AC_SUBST([ICU_CPPFLAGS])

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

# Use std::thread if we can, otherwise use boost::thread.
AS_ECHO_N("checking for std::thread... ")
CPPFLAGS_saved="$CPPFLAGS"
CPPFLAGS="-std=c++11"
AC_TRY_COMPILE([#include <thread>],
               [std::thread t;],
               [have_std_thread="yes"], [have_std_thread="no"])
CPPFLAGS="$CPPFLAGS_saved"
AS_ECHO($have_std_thread)

if test "x$have_std_thread" = "xyes"; then
  AC_DEFINE(HAVE_STD_THREAD,1,[Define to 1 if std::thread is available.])
else
  AX_BOOST_CHRONO
  AX_BOOST_THREAD
fi

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

  AC_CHECK_HEADER([scope/test.h],[scope_ok="yes"])

  CPPFLAGS="$CPPFLAGS_saved"

  if test "x$scope_ok" = "xyes"; then
    AC_DEFINE(HAVE_SCOPE,1,[Define to 1 if Scope test framework is available.])
    AC_SUBST([SCOPE_CPPFLAGS])
  fi
fi

# Tell the user why not if he won't be able to compile the tests
if test "x$ax_cv_boost_program_options" != "xyes" || \
   test "x$ax_cv_boost_system" != "xyes" || \
   test "x$scope_ok" != "xyes" || \
   ( \
      test "x$have_std_thread" != "xyes" && \
      ( \
        test "x$ax_cv_boost_thread" != "xyes" || \
        test "x$ax_cv_boost_chrono" != "xyes" \
      ) \
   ) ; then
  AC_MSG_WARN([])
  AC_MSG_WARN([You will be unable to compile and run the tests because:])
  AC_MSG_WARN([])
  if test "x$ax_cv_boost_program_options" != "xyes"; then
    AC_MSG_WARN([  * boost::program_options is unavailable])
  fi
  if test "x$ax_cv_boost_system" != "xyes"; then
    AC_MSG_WARN([  * boost::system is unavailable])
  fi
  if test "x$have_std_thread" != "xyes" && \
    ( \
      test "x$ax_cv_boost_thread" != "xyes" || \
      test "x$ax_cv_boost_chrono" != "xyes" \
    ) ; then
    AC_MSG_WARN([  * neither std::thread nor boost::thread and boost::chrono are available])
  fi
  if test "x$scope_ok" != "xyes"; then
    AC_MSG_WARN([  * Scope test framework is unavailable])
  fi
  AC_MSG_WARN([])
fi

case "$host" in
*-*-mingw*)
  # Boost ASIO needs ws2_32 and mswsock on Windows
  BOOST_ASIO_LIB="-lws2_32 -lmswsock"
  AC_SUBST([BOOST_ASIO_LIB])

  # FIXME: wrong boost_system lib gets detected!
  BOOST_SYSTEM_LIB=`echo "$BOOST_SYSTEM_LIB" | sed 's/.dll/-mt/'`
  ;;
esac

#
# Threading
# 
case "$host" in
*-*-mingw*)
  AX_APPEND_COMPILE_FLAGS([-mthreads], [LG_CPPLAGS])
  AX_APPEND_LINK_FLAGS([-mthreads], [LG_LDFLAGS])
  ;;
*-apple-darwin*)
  ;;
*)
  AX_APPEND_COMPILE_FLAGS([-pthread], [LG_CPPFLAGS])
  AX_APPEND_LINK_FLAGS([-pthread], [LG_LDFLAGS])
esac

AC_SUBST([LG_CPPFLAGS])
AC_SUBST([LG_CFLAGS])
AC_SUBST([LG_CXXFLAGS])
AC_SUBST([LG_LDFLAGS])

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

  case "$host" in
  i686-*-mingw*)
    # FIXME: Really? This looks like it's just asking for trouble...
    AX_APPEND_LINK_FLAGS([-Wl,--allow-multiple-definition], [LG_LIB_LDFLAGS])
    ;;
  esac
else
  CXXLD="$CXX"
  CCLD="$CC"

  case "$host" in
  *-*-mingw*)
    # -no-undefined is a libtool flag; adding it with AX_APPEND_LINK_FLAGS
    # will fail because that tries flags with LD. So don't do that.
    AX_APPEND_FLAG([-no-undefined], [LG_LIB_LDFLAGS])
    LG_LIB_LDFLAGS="$LG_LIB_LDFLAGS -Wl,--output-def -Wl,src/lib/.libs/$PACKAGE.def"
    ;;
  esac
fi

AM_CONDITIONAL([BUILD_DLL], [test "x$enable_shared" = "xyes" && echo "$host" | grep -q mingw])

AC_SUBST([CXXLD])
AC_SUBST([CCLD])

AC_SUBST([LG_LIB_LDFLAGS])

#
# Cleanup flags
#

# TODO: libtre has a nice display we can steal
AC_MSG_NOTICE([ICU_CPPFLAGS: $ICU_CPPFLAGS])
AC_MSG_NOTICE([ICU_CFLAGS:   $ICU_CFLAGS])
AC_MSG_NOTICE([ICU_CXXFLAGS: $ICU_CXXFLAGS])
AC_MSG_NOTICE([ICU_LIBS:     $ICU_LIBS])

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

# Force static linking of dependencies for our fat DLL.
if test "x$enable_shared_fat" = "xyes"; then
  # NB: This is likely to be fragile. It works only because the current
  # version of libtool doesn't alter whole_archive_flag_spec and happens
  # to put it in the right place in the linking command for our DLL.
  sed -i '/^whole_archive_flag_spec=/s/"$/ \\${wl}-static"/' libtool
  echo 'Adjusted libtool for building fat DLL'
fi
