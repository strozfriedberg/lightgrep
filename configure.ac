# Process this file with autoconf to produce a configure script.
# TODO: Unknown whether 2.64 works; was a bit of a milestone release, though
AC_PREREQ([2.64])
# TODO: required versions for automake, libtool?

AC_INIT([lightgrep], [1.5.0], [BUG-REPORT-ADDRESS])

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
# metadata
#

case "$host" in
*-*-mingw*)
  LT_LANG([Windows Resource])
  IS_MINGW=yes
  ;;
esac

AM_CONDITIONAL([BUILD_MINGW], [test "x$IS_MINGW" = "xyes"])

# Decompose the version number.
#
# We must do this rather than construct PACKAGE_VERSION from the components
# because AC_INIT rejects anything but a literal for the version number.
PACKAGE_VERSION_MAJOR=`echo "$PACKAGE_VERSION" | cut -d. -f1`
PACKAGE_VERSION_MINOR=`echo "$PACKAGE_VERSION" | cut -d. -f2`
PACKAGE_VERSION_MICRO=`echo "$PACKAGE_VERSION" | cut -d. -f3`

AC_SUBST([PACKAGE_VERSION_MAJOR])
AC_SUBST([PACKAGE_VERSION_MINOR])
AC_SUBST([PACKAGE_VERSION_MICRO])

AC_DEFINE_UNQUOTED(PACKAGE_VERSION_MAJOR, $PACKAGE_VERSION_MAJOR, [Define to the major version of this package.])
AC_DEFINE_UNQUOTED(PACKAGE_VERSION_MINOR, $PACKAGE_VERSION_MINOR, [Define to the minor version of this package.])
AC_DEFINE_UNQUOTED(PACKAGE_VERSION_MICRO, $PACKAGE_VERSION_MICRO, [Define to the micro version of this package.])

PACKAGE_YEAR=`date +%Y`

AC_SUBST([PACKAGE_YEAR])
AC_DEFINE_UNQUOTED(PACKAGE_YEAR, $PACKAGE_YEAR, [Define to the current year.])

PACKAGE_COMPANY="Stroz Friedberg, LLC"

AC_SUBST([PACKAGE_COMPANY])
AC_DEFINE_UNQUOTED(PACKAGE_COMPANY, "$PACKAGE_COMPANY", [Define to the owner of this package.])

PACKAGE_DESCRIPTION="not the worst forensics regexp engine"
AC_SUBST([PACKAGE_DESCRIPTION])
AC_DEFINE_UNQUOTED(PACKAGE_DESCRIPTION, "$PACKAGE_DESCRIPTION", [Define to the description of this package.])

#
# common
#

AC_PROG_CC
AC_PROG_CXX
AM_PROG_CC_C_O
AC_PROG_INSTALL

PKG_PROG_PKG_CONFIG
AS_IF([test "x$enable_shared" != "xyes"], [PKG_CONFIG="$PKG_CONFIG --static"])

AC_LANG([C])
AX_APPEND_COMPILE_FLAGS([-std=c11 -W -Wall -Wextra -pedantic -pipe], [LG_CFLAGS])

AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_17([noext], [mandatory])
AX_APPEND_COMPILE_FLAGS([-W -Wall -Wextra -Wnon-virtual-dtor -pedantic -pipe], [LG_CXXFLAGS])

AC_ARG_ENABLE([debug],
  [AS_HELP_STRING([--enable-debug],
    [build in debug mode, with symbols and no optimization])])

AS_IF([test "x$enable_debug" = "xyes"], [OFLAGS='-Og'], [OFLAGS='-O3 -mtune=intel'])

AC_ARG_ENABLE([symbols],
  [AS_HELP_STRING([--enable-symbols],
    [build with debugging symbols])],
  [enable_symbols=yes],
  [enable_symbols=no])

AS_IF([test "x$enable_symbols" != "xno"], [SYMBOLS='-g'], [SYMBOLS=''])

AX_APPEND_COMPILE_FLAGS([$SYMBOLS $OFLAGS], [LG_CFLAGS])
AX_APPEND_COMPILE_FLAGS([$SYMBOLS $OFLAGS], [LG_CXXFLAGS])

PKG_CHECK_MODULES([GPT], [libprofiler], [], [ : ])

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

case "$host" in
*-*-mingw*)
  for i in $ICU_LIBS ; do
    ICU_LDFLAGS+=$(echo $i | grep '^-L')
  done
esac

AC_SUBST([ICU_CPPFLAGS])
AC_SUBST([ICU_LDFLAGS])

#
# Boost
#
if test "x$with_boost" = "xno"; then
  AC_MSG_ERROR([--without-boost specified, but Boost is mandatory.])
else
  case "$host" in
  *-*-mingw*)
    # AX_BOOST_BASE doesn't find Boost for mingw, we help it out
    if test "$with_boost" = ""; then
      with_boost="/usr/${host}/sys-root/mingw"
      AC_MSG_NOTICE([--with-boost not set. We are guessing ${with_boost}.])
    fi
    ;;
  esac

  AX_BOOST_BASE([1.49.0],
    [],
    [AC_MSG_ERROR([Failed to find usable Boost headers.])])
fi

# FIXME: doesn't always find -mt version of boost libs,
# e.g. for filesystem and system
AX_BOOST_PROGRAM_OPTIONS
if test "x$ax_cv_boost_program_options" != "xyes"; then
  AC_MSG_ERROR([Failed to find Boost program_options library.])
fi

AX_BOOST_ASIO
if test "x$ax_cv_boost_asio" != "xyes"; then
  AC_MSG_ERROR([Failed to find Boost asio library.])
fi

case "$host" in
*-*-mingw*)
  # Boost ASIO needs ws2_32 and mswsock on Windows
  BOOST_ASIO_LIB="-lws2_32 -lmswsock"
  AC_SUBST([BOOST_ASIO_LIB])
  ;;
esac

#
# libasan
#
AC_ARG_WITH([asan],
  [AS_HELP_STRING([--with-asan=DIR], [build with libasan])],
  [],
  [with_asan=no])

if test "x$with_asan" != "xno"; then
  ASAN_CFLAGS="-fsanitize=address -fno-omit-frame-pointer"
  ASAN_CXXFLAGS="$ASAN_CFLAGS"
  ASAN_LDFLAGS="$ASAN_CFLAGS"
  AC_SUBST([ASAN_CFLAGS])
  AC_SUBST([ASAN_CXXFLAGS])
  AC_SUBST([ASAN_LDFLAGS])
fi

AC_DEFINE_UNQUOTED(LG_TEST_DATA_DIR, "$srcdir/test/data", [Define to the path to the test data.])

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
    LT_LANG([Windows Resource])
    ;;
  esac
fi

AC_SUBST([CXXLD])
AC_SUBST([CCLD])

AM_CONDITIONAL([BUILD_DLL], [test "x$enable_shared" = "xyes" && echo "$host" | grep -q mingw])

AC_SUBST([LG_LIB_LDFLAGS])

#
# Test Dependencies
#

AX_PKG_CHECK_MODULES([CATCH2], [], [catch2-with-main])

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

# Support for check with valgrind
AX_VALGRIND_DFLT([sgcheck], [off])
AX_VALGRIND_DFLT([helgrind], [off])
AX_VALGRIND_DFLT([drd], [off])
AX_VALGRIND_DFLT([memcheck], [on])
AX_VALGRIND_CHECK

#
# Python bindings
#
AC_ARG_ENABLE([python],
  [AS_HELP_STRING([--enable-python], [build Python bindings])])

AS_IF(
  [test "x$enable_python" = "xyes"],
  [AC_PATH_PROG([PYTHON], [python])]
)

AM_CONDITIONAL([BUILD_PYTHON], [test "x$enable_python" = "xyes"])

#
# Java bindings
#
AC_ARG_ENABLE([java],
  [AS_HELP_STRING([--enable-java], [build Java bindings])])

AS_IF(
  [test "x$enable_java" = "xyes"],
  [
    # calls AC_PATH_PROG using JAVAC; setting it here with AC_PATH_PROG messes
    # up the check, so do this first
    saved_JAVAC="$JAVAC"
    JAVAC=
    AX_JNI_INCLUDE_DIR
    JAVAC="$saved_JAVAC"

    for JNI_INCLUDE_DIR in $JNI_INCLUDE_DIRS; do
      JNI_CPPFLAGS="$JNI_CPPFLAGS -I$JNI_INCLUDE_DIR"
    done

    AC_SUBST([JNI_CPPFLAGS])

    JUNIT_JARS=/usr/share/java/junit.jar:/usr/share/java/hamcrest/hamcrest.jar
    AC_SUBST([JUNIT_JARS])

    AC_PATH_PROG([JAVA], [java])
    AC_PATH_PROG([JAR], [jar])
    AC_PATH_PROG([JAVAC], [javac])
  ]
)

AM_CONDITIONAL([BUILD_JAVA], [test "x$enable_java" = "xyes"])

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

AC_MSG_NOTICE([ASAN_CFLAGS: $ASAN_CFLAGS])
AC_MSG_NOTICE([ASAN_CXXFLAGS: $ASAN_CXXFLAGS])
AC_MSG_NOTICE([ASAN_LDFLAGS: $ASAN_LDFLAGS])

AC_MSG_NOTICE([LG_CFLAGS: $LG_CFLAGS])
AC_MSG_NOTICE([LG_CXXFLAGS: $LG_CXXFLAGS])

AC_MSG_NOTICE([CC:       $CC])
AC_MSG_NOTICE([CXX:      $CXX])
AC_MSG_NOTICE([CPPFLAGS: $CPPFLAGS])
AC_MSG_NOTICE([CFLAGS:   $CFLAGS])
AC_MSG_NOTICE([CXXFLAGS: $CXXFLAGS])
AC_MSG_NOTICE([LDFLAGS:  $LDFLAGS])
AC_MSG_NOTICE([LIBS:     $LIBS])

AC_CONFIG_FILES([Makefile liblightgrep.spec mingw-liblightgrep.spec])
AC_OUTPUT

# Force static linking of dependencies for our fat DLL.
if test "x$enable_shared_fat" = "xyes"; then
  # NB: This is likely to be fragile. It works only because the current
  # version of libtool doesn't alter whole_archive_flag_spec and happens
  # to put it in the right place in the linking command for our DLL.
  sed -i '/^whole_archive_flag_spec=/s/"$/ \\${wl}-static"/' libtool

  # We want NO dependencies for a fat DLL. libgcc_s is a stub for
  # libgcc_s_seh-1.dll. libgcc_eh is the corresponding static lib.
  sed -i '/^postdeps=/s/-lgcc_s/-lgcc_eh/g' libtool

  echo 'Adjusted libtool for building fat DLL'
fi
