# Process this file with autoconf to produce a configure script.
# TODO: Unknown whether 2.64 works; was a bit of a milestone release, though
AC_PREREQ([2.64])
# TODO: required versions for automake, libtool?

AC_INIT([lightgrep], [0.0], [BUG-REPORT-ADDRESS])

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
AC_CONFIG_SRCDIR([src/cmd/main.cpp])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([foreign subdir-objects])
LT_INIT

#
# common
#
AC_PROG_CXX
AM_PROG_CC_C_O

AC_LANG([C++])

# Get the C++11 flag, but don't append it to CPPFLAGS
CXXFLAGS_saved="$CXXFLAGS"
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])
CXX11_FLAG=`echo $CXXFLAGS | sed -e 's/.* //'`
CXXFLAGS="$CXXFLAGS_saved"

AX_APPEND_COMPILE_FLAGS([-W -Wall -Wextra -Wnon-virtual-dtor -pedantic -pipe -O3 $CXX11_FLAG], [LG_CXXFLAGS])

AC_PROG_INSTALL

# FIXME: mingw defaults to -g -O2, along with a bunch of other flags which
# we want to keep.
case "$host" in
*-*-mingw*)
  LG_REMOVE_FLAGS([CXXFLAGS], ['-O2'])
  ;;
esac

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
  *) ICU_CONFIG+='/' ;;
  esac

  # Check that icu-config exists
  if test ! -f "$ICU_CONFIG/icu-config"; then
    AC_MSG_ERROR([Path "${ICU_CONFIG}icu-config" does not exist])
  fi
fi

# FIXME: icu-config from ICU cross-compiled with mingw wants libicuuc.dll,
# which won't exist if ICU was compiled static only, so we temporarily add
# --noverify until we figure out what to do about this.
ICU_CONFIG+='icu-config --noverify'

AC_MSG_WARN([Disregard the next few lines where ICU_* are printed.])
AC_MSG_WARN([They're all wrong but we fix them up before using them.])
AX_CHECK_ICU(1.48)

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
  duff_icu_compile_flags+=' -Wp,-D_FORTIFY_SOURCE=2'
fi

LG_REMOVE_FLAGS([ICU_CFLAGS],   [$duff_icu_compile_flags])
LG_REMOVE_FLAGS([ICU_CXXFLAGS], [$duff_icu_compile_flags])

#
# liblightgrep
#

# FIXME: Is this the right way to set static linking for autoconf tests?
if test "x$enable_shared" != "xyes"; then
  LDFLAGS+=' -static'
fi

AC_CHECK_HEADER([lightgrep/api.h],
  [],
  [AC_MSG_ERROR([liblightgrep C API headers not found.])])

AC_CHECK_LIB([lightgrep], [lg_create_pattern],
  [LG_LIB="-llightgrep"],
  [AC_MSG_ERROR([liblightgrep not found.])],
  [$ICU_LIBS]
)

AC_SUBST([LG_LIB])

AC_ARG_WITH([liblightgrep],
  [AS_HELP_STRING([--with-liblightgrep-headers=ARG],
    [use liblightgrep headers from the specified location])],
  [LG_CPPFLAGS+=" -I$withval"],
  [LG_CPPFLAGS+=" -Ivendors/liblightgrep/include"])

if test "x$with_liblightgrep_headers" = "xno"; then
  AC_MSG_ERROR([--without-liblightgrep-headers specified, but liblightgrep headers are mandatory.])
fi

# The header preprocessor check needs -std=c++11; we temporarily provide it.
CPPFLAGS_saved="$CPPFLAGS"
CPPFLAGS+=" $CXX11_FLAG $LG_CPPFLAGS"
export CPPFLAGS

AC_CHECK_HEADER([basic.h],
  [],
  [AC_MSG_ERROR([liblightgrep internal headers not found.])])

CPPFLAGS="$CPPFLAGS_saved"

#
# Boost
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

# FIXME: doesn't always find -mt version of boost libs,
# e.g. for filesystem and system
AX_BOOST_FILESYSTEM
if test "x$ax_cv_boost_filesystem" != "xyes"; then
  AC_MSG_ERROR([Failed to find Boost filesystem library.])
fi

AX_BOOST_CHRONO
if test "x$ax_cv_boost_chrono" != "xyes"; then
  AC_MSG_ERROR([Failed to find Boost chrono library.])
fi

AX_BOOST_PROGRAM_OPTIONS
if test "x$ax_cv_boost_program_options" != "xyes"; then
  AC_MSG_ERROR([Failed to find Boost program_options library.])
fi

AX_BOOST_SYSTEM
if test "x$ax_cv_boost_system" != "xyes"; then
  AC_MSG_ERROR([Failed to find Boost system library.])
fi

AX_BOOST_THREAD
if test "x$ax_cv_boost_thread" != "xyes"; then
  AC_MSG_ERROR([Failed to find Boost thread library.])
fi

case "$host" in
*-*-mingw*)
  # Boost ASIO needs ws2_32 and mswsock on Windows
  BOOST_ASIO_LIB="-lws2_32 -lmswsock"
  AC_SUBST([BOOST_ASIO_LIB])

  # FIXME: wrong boost_system lib gets detected!
  BOOST_SYSTEM_LIB=`echo "$BOOST_SYSTEM_LIB" | sed 's/.dll/-mt/'`
  # FIXME: wrong boost_filesystem lib gets detected!
  BOOST_FILESYSTEM_LIB=`echo "$BOOST_FILESYSTEM_LIB" | sed 's/.dll/-mt/'`
  ;;
esac

if test "x$enable_shared" != "xyes"; then
  AX_APPEND_FLAG([-DBOOST_THREAD_USE_LIB], [BOOST_CPPFLAGS])
fi

#
# tests
#

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
if test "x$scope_ok" != "xyes"; then
  AC_MSG_WARN([])
  AC_MSG_WARN([You will be unable to compile and run the tests because:])
  AC_MSG_WARN([])
  if test "x$scope_ok" != "xyes"; then
    AC_MSG_WARN([  * Scope test framework is unavailable])
  fi
  AC_MSG_WARN([])
fi

#
# Threading
# 
case "$host" in
*-*-mingw*)
  AX_APPEND_FLAG([-mthreads], [LG_CPPLAGS])
  AX_APPEND_LINK_FLAGS([-mthreads], [LG_LDFLAGS])
  ;;
*-apple-darwin*)
  ;;
*)
  AX_APPEND_FLAG([-pthread], [LG_CPPFLAGS])
  AX_APPEND_LINK_FLAGS([-pthread], [LG_LDFLAGS])
esac

AC_SUBST([LG_CPPFLAGS])
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
  AX_APPEND_COMPILE_FLAGS([-stdlib=libc++], [STDCXX_CXXFLAGS])
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
AC_SUBST([STDCXX_CXXFLAGS])

# FIXME: Is this really the right way to do this?!
# Build dynamically-linked executables if we build dynamic libs
if test "x$enable_shared" != "xyes"; then
  CXXLD="$CXX -all-static"

  case "$host" in
  i686-*-mingw*)
    # FIXME: Really? This looks like it's just asking for trouble...
    AX_APPEND_LINK_FLAGS([-Wl,--allow-multiple-definition], [LDFLAGS])
    ;;
  esac
else
  CXXLD="$CXX"
fi

AC_SUBST([CXXLD])

#
# Customer name
#
AC_ARG_WITH([customer],
  [AS_HELP_STRING([--with-customer=ARG], [set the customer name])],
  [
    escaped_customer=`echo "$withval" | sed -e 's/,/\\\\x2C/g'`
    AC_DEFINE_UNQUOTED([LIGHTGREP_CUSTOMER],
      [$escaped_customer],[Name of the customer.])
    AC_MSG_NOTICE([customer is "$with_customer"])
  ]
  [AC_MSG_NOTICE([no customer specified])])

# FIXME: temporarily suspended flag deduplication until we figure out
# how to do it without stomping on the user variables
#
# Cleanup flags
#
#AX_APPEND_COMPILE_FLAGS([$ICU_CPPFLAGS $BOOST_CPPFLAGS], [CPPFLAGS])
#AX_APPEND_COMPILE_FLAGS([$ICU_CXXFLAGS $BOOST_CXXFLAGS], [CXXFLAGS])

#LG_UNIQ_FLAGS([CPPFLAGS])
#LG_UNIQ_FLAGS([CXXFLAGS])


# TODO: libtre has a nice display we can steal
AC_MSG_NOTICE([ICU_CPPFLAGS: $ICU_CPPFLAGS])
AC_MSG_NOTICE([ICU_CXXFLAGS: $ICU_CXXFLAGS])

AC_MSG_NOTICE([BOOST_CPPFLAGS: $BOOST_CPPFLAGS])
AC_MSG_NOTICE([BOOST_CXXFLAGS: $BOOST_CXXFLAGS])

AC_MSG_NOTICE([CXX:      $CXX])
AC_MSG_NOTICE([CPPFLAGS: $CPPFLAGS])
AC_MSG_NOTICE([CXXFLAGS: $CXXFLAGS])
AC_MSG_NOTICE([LIBS:     $LIBS])
AC_MSG_NOTICE([LDFLAGS:  $LDFLAGS])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
