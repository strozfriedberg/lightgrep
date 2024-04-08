lightgrep
============

not the worst forensics regexp engine

About
-----
Lightgrep is a regular expression engine, designed specifically for digital forensics. Why another regexp engine?

Lightgrep:
 * searches for many patterns simultaneously
 * searches binary data as a stream, not as discrete lines of text
 * searches for patterns in many different encodings; give it dirty data, lightgrep don't care
 * never, ever, ever, never, never looks at a byte twice or backs up in your input

Lightgrep is an [automata-based engine](https://en.wikipedia.org/wiki/Finite-state_machine) and doesn't have all the regexp features you might be used to. However, it has proved very useful in digital investigations and is well-tested.

Lightgrep has both a command-line program for conducting searches against files and a C library, liblightgrep, for using in programs and scripts. The command-line program can search binary and text. The library has a C API and has bindings for both Python and Java. 

Lightgrep is copyright (c) 2010-2024, Stroz Friedberg, LLC. Lightgrep is available under version 3 of the GNU Public License. See [COPYING](COPYING) for details.

lightgrep command-line
----------------------
The lightgrep command-line program searches files and provides some helpful information concerning provided patterns.

### `lightgrep --help`

The `--help` flag will tell lightgrep to report on all its command-line switches:
```
lightgrep 1.5.0
Copyright (c) 2010-2024, Stroz Friedberg, LLC
Built Apr  8 2024
Usage: lightgrep [OPTION]... PATTERN_FILE [FILE]...
       lightgrep [OPTION]... [-p PATTERN | -k FILE]... [FILE]...

Command selection:
  -c [ --command ] CMD (=search)        command to perform [search|graph|prog|s
                                        amp|validate|analyze]
  --help                                display this help message
  --list-encodings                      list known encodings
  -V [ --version ]                      print version information and exit

Pattern selection and interpretation:
  -k [ --keywords ] FILE                path to keywords file
  -p [ --pattern ] PATTERN              a keyword on the command-line
  -e [ --encoding ] ENCODING (=ASCII)   encoding to use (e.g., ASCII, UTF-8)
  -i [ --ignore-case ]                  ignore case distinctions
  -F [ --fixed-strings ]                interpret patterns as fixed strings

Input and output:
  -o [ --output ] FILE (=-)             output file (stdout default)
  -a [ --arg-file ] FILE                read input paths from file
  -r [ --recursive ]                    traverse directories recursively
  --histogram-file FILE                 output file for histogram
  -H [ --with-filename ]                print the filename for each match
  -h [ --no-filename ]                  suppress the filename for each match
  -A [ --after-context ] NUM            print NUM lines of trailing context
  -B [ --before-context ] NUM           print NUM lines of leading context
  -C [ --context ] NUM                  print NUM lines of context
  --group-separator SEP (=--)           use SEP as the group separator
  --no-output                           do not output hits (good for profiling)
  --block-size BYTES (=8388608)         block size to use for buffering, in
                                        bytes
  --mmap                                memory-map input file(s)

Miscellaneous:
  --determinize-depth NUM (=4294967295) determinze NFA to NUM depth
  --binary                              output program as binary
  --program-file FILE                   read search program from file
  --verbose                             enable verbose output
```


Technical Info
--------------
Lightgrep is implemented in portable C++17 but exposes a concise C API. The core of the API is defined in [include/lightgrep/api.h](./include/lightgrep/api.h). You can see a small example program at [c_example/main.c](./c_example/main.c).

Lightgrep depends on a number of [Boost](http://www.boost.org/) libraries and also on [ICU](http://www.icu-project.org).

Install
-------
See the [BUILD.md file](BUILD.md) for installation instructions.
