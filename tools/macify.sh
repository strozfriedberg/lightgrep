#!/bin/sh

# Package a MacOS X build so that it works on other Macs.
# 
# By default, Mach executables include absolute paths to shared libraries they depend on.
# This is obviously stupid. The solution is to use "@loader_path" and rejigger the
# executable _and_ the libraries to state their dependencies relative to @loader_path.
# @loader_path works both with an executable and with a requesting library (as opposed
# to @executable_path). Modern versions of MacOS X also support @rpath, but I couldn't
# get this to work, sadly.
#
# Obviously, this script will only work on my Mac. But it's at least a repeatable process.

BUILDDIR=./mac_build

LIBCPP=libstdc++.6.dylib
LIBGCC=libgcc_s.1.dylib
LIBLG=liblightgrep.dylib

LIBCPPPATH=/Users/jon/my_gcc/lib/$LIBCPP
LIBGCCPATH=/Users/jon/my_gcc/lib/$LIBGCC
LIBLGPATH=bin/src/lib/$LIBLG

if [ $BUILDDIR ]
then
  rm -Rf $BUILDDIR
fi

mkdir $BUILDDIR
cp lightgrep.exe $BUILDDIR/lightgrep
cp $LIBCPPPATH $BUILDDIR/
cp $LIBGCCPATH $BUILDDIR/
cp $LIBLGPATH $BUILDDIR/

cd $BUILDDIR

install_name_tool -id @loader_path/$LIBGCC $LIBGCC

install_name_tool -id @loader_path/$LIBCPP $LIBCPP
install_name_tool -change $LIBGCCPATH @loader_path/$LIBGCC $LIBCPP

install_name_tool -id @loader_path/$LIBLG $LIBLG
install_name_tool -change $LIBGCCPATH @loader_path/$LIBGCC $LIBLG
install_name_tool -change $LIBCPPPATH @loader_path/$LIBCPP $LIBLG

install_name_tool -change $LIBCPPPATH @loader_path/$LIBCPP lightgrep
install_name_tool -change $LIBGCCPATH @loader_path/$LIBGCC lightgrep
install_name_tool -change $LIBLGPATH @loader_path/$LIBLG lightgrep
