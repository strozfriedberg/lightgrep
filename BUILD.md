Lightgrep Build Steps
========================

Quick Start
-----------
The following build steps might actually work:

1. git clone --recursive https://github.com/strozfriedberg/lightgrep.git
2. cd lightgrep
3. autoreconf -fi
4. ./configure
5. make -j4
6. sudo make install


Platforms
---------
Lightgrep can build on Linux, MacOS X, and Windows. It should be noted that Windows builds are a huge pain in the keister; stock up on beer and nachos (Windows builds are _easier_ with a Linux-hosted cross compiler). MacOS X can also be finicky.


Tooling
-------
You'll need the following:

1. GNU Autotools and Make
2. GNU Bison
3. GNU Libtool
4. GCC or Clang with C++17 support
5. pkg-config

lightgrep requires C++17 support. Visual Studio isn't quite there yet, but lightgrep could probably be hammered into shape if needed. Why would you do that when you could just use your Linux distro's MinGW cross-compiler?

If you plan on building lightgrep frequently, we highly recommend installing and using Tridge's excellent ccache.


Dependencies
------------
Basic:
 - Boost headers >= 1.49
 - Boost::program_options
 - ICU >= 1.48

Unit tests:
 - Boost::asio
 - [Catch2](https://github.com/catchorg/Catch2) >= 3.0.1

These libraries must be built with the same compiler as lightgrep.

Lightgrep uses the awesome ICU libraries to do the gruntwork for Unicode regexp features and the wide array of supported encodings. We only use ICU's C API, so chances are high that lightgrep will work with your system's default version of ICU, even if a different compiler was used. However, ICU may be transitioning away from the C API, so this flexibility may change in the future.

Catch2 requires cmake to build it. We build Catch2 as follows ourselves:
```
cmake -Bbuild -H. -DCMAKE_INSTALL_PREFIX=$INSTALL -DCMAKE_INSTALL_LIBDIR=lib -DPKGCONFIG_INSTALL_DIR=$INSTALL/lib/pkgconfig
cmake --build build/
cmake --install build
```
where `$INSTALL` is the base directory where we want to install it. (You could build Catch2 differently, so long as lightgrep can find it.)


Unit Tests
----------
If you've installed Catch2 and Boost::asio, you can run "make check" to build and execute the unit tests. Note that one source file may take several minutes to compile.

Example (of running the tests manually):

<code><pre>
$ test/test

===============================================================================
All tests passed (89026670 assertions in 5475 test cases)

$
</pre></code>


Installation
------------
By default, make install will place liblightgrep.(a|so) into /usr/local/lib and the lightgrep headers into /usr/local/include/lightgrep. You can specify a different base directory other than /usr/local with the configure script.
