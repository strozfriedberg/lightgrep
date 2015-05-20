liblightgrep
============

not the worst forensics regexp engine

About
-----
Lightgrep is a new regular expression engine, designed specifically for digital forensics. Why another regexp engine?

Lightgrep:
 * searches for many patterns simultaneously
 * searches binary data as a stream, not as discrete lines of text
 * searches for patterns in many different encodings; give it dirty data, lightgrep don't care
 * never, ever, ever, never, never looks at a byte twice or backs up in your input

Lightgrep is still pretty new and doesn't have all the regexp features you might be used to. But it has enough features to be more than a toy, and what is supported is well-tested.

liblightgrep is copyright (c) 2010-2015, Stroz Friedberg, LLC. liblightgrep is available under version 3 of the GNU Public License. See [COPYING](COPYING) for details.

Technical Info
--------------
Lightgrep is implemented in portable C++11 but exposes a concise C API. The core of the API is defined in [include/lightgrep/api.h](./include/lightgrep/api.h). You can see a small example program at [c_example/main.c](./c_example/main.c).

Lightgrep depends on a number of [Boost](http://www.boost.org/) libraries and also on [ICU](http://www.icu-project.org). Currently you will need gcc 4.6+ or clang 3.1 to compile the libraries.

Install
-------
See the [BUILD.md file](BUILD.md) for installation instructions.
