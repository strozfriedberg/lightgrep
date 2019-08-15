Liblightgrep Build Steps
========================

Quick Start
-----------
The following build steps might actually work:

1. git clone --recursive git://github.com/LightboxTech/liblightgrep.git
2. cd liblightgrep
3. autoreconf -fi
4. ./configure
5. make -j4
6. sudo make install


Platforms
---------
Liblightgrep can build on Linux, MacOS X, and Windows. It should be noted that Windows builds are a huge pain in the keister; stock up on beer and nachos (Windows builds are _easier_ with a Linux-hosted cross compiler). MacOS X can also be finicky.


Tooling
-------
You'll need the following:

1. GNU Autotools and Make
2. GNU Bison
3. GCC 4.6+ or Clang 3.1+

liblightgrep requires pretty good (but not great) C++11 support. Visual Studio isn't quite there yet, but liblightgrep could probably be hammered into shape if needed. Why would you do that when you could just use your Linux distro's MinGW cross-compiler?

If you plan on building liblightgrep frequently, we highly recommend installing and using Tridge's excellent ccache.


Dependencies
------------
Basic:
 - Boost headers (1.49+)
 - ICU (1.48+)

Unit tests:
 - Boost::asio
 - Boost::program_options
 - Boost::system
 - Scope (a git submodule)

Liblightgrep uses the Boost project extensively. The lightgrep library itself depends on several header-only Boost libraries. The unit test suite, however, also relies on the system  and program_options libraries having been built and available. These libraries must be built with the same compiler as liblightgrep. Boost 1.48 is known not to work in various configurations due to problems in Boost Thread.

Liblightgrep uses the awesome ICU libraries to do the gruntwork for Unicode regexp features and the wide array of supported encodings. We only use ICU's C API, so chances are high that liblightgrep will work with your system's default version of ICU, even if a different compiler was used. However, ICU may be transitioning away from the C API, so this flexibility may change in the future.


Unit Tests
----------
If you've installed the other Boost libraries, you can run "make check" to build and execute the unit tests. Note that one source file may take several minutes to compile.

Example:

<code><pre>
$ make check
make  test/test
make[1]: Entering directory '/mnt/raid/jon/data/code/liblightgrep'
make[1]: Leaving directory '/mnt/raid/jon/data/code/liblightgrep'
make  check-TESTS
make[1]: Entering directory '/mnt/raid/jon/data/code/liblightgrep'
OK (2992 tests)
PASS: test/test
1 test passed
make[1]: Leaving directory '/mnt/raid/jon/data/code/liblightgrep'
</pre></code>

Installation
------------
By default, make install will place liblightgrep.(a|so) into /usr/local/lib and the lightgrep headers into /usr/local/include/lightgrep. You can specify a different base directory other than /usr/local with the configure script.
