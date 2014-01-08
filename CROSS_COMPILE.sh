#!/bin/bash -e

#
# fetch and build Boost for 64-bit Windows
#
[ -f boost_1_53_0.tar.bz2 ] || wget 'https://downloads.sourceforge.net/project/boost/boost/1.53.0/boost_1_53_0.tar.bz2'
tar xvf boost_1_53_0.tar.bz2
pushd boost_1_53_0
cat >> ./tools/build/v2/user-config.jam << EOF
using gcc : : x86_64-w64-mingw32-g++ ;
EOF
patch -p0 <../boost-mingw.patch
./bootstrap.sh
./bjam --stagedir=../vendors --with-program_options --with-system --with-thread --with-filesystem link=static runtime-link=static variant=release threading=multi toolset=gcc target-os=windows address-model=64 define=BOOST_USE_WINDOWS_H define=BOOST_THREAD_USE_LIB -s BOOST_NO_RVALUE_REFERENCES stage
popd
