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

### Searching

To search a file, use `$ lightgrep keywords.txt <PATH_TO_FILE>`. By default lightgrep will report any search hits as tab-delimited data to stdout, in six columns: <PATH_TO_FILE> \t Starting offset \t Ending offset \t Keyword index \t Keyword \t Encoding.

![Example of `lightgrep pytest/keys/----10.txt pytest/corpora/norvig1mb.txt`](documentation/gifs/lightgrep_search.gif)

For convenience a single keyword can be provided with the `-p <keyword>` option.

#### Encodings and Unicode

Lightgrep always searches its input as binary. Patterns are parsed as Unicode and then transformed to binary according to the selected encodings. Lightgrep will search for all forms of a given pattern and report the encoding for each search hit. By default, Lightgrep will search in US-ASCII, matching only 7-bit ASCII characters.

Multiple encodings may be specified by repeating the `-e/--encoding` flag with different encodings as arguments. Lightgrep uses the [ICU libraries](https://icu.unicode.org/) both for handling Unicode names and properties used in patterns and for handling how patterns are represented in binary for specified encodings. For English searches, `-e UTF-8 -e UTF-16LE` are good options to use, as UTF-8 is a superset of US-ASCII and both encodings provide full Unicode compatibility and are widely in use on contemporary operating systems. For non-English searches, however, users may want to specify additional single-byte [encodings/code pages](https://en.wikipedia.org/wiki/Code_page), e.g., cp1251.

The Unicode standard changes over time and the ICU libraries are updated to suit. Depending how lightgrep was built and which version of the ICU libraries were used, lightgrep may not be up-to-date with the latest Unicode standard. To get a list of which encodings Lightgrep understands, use `lightgrep --list-encodings` (the list will be long, so you may want to pipe to `less` or redirect to a file). Please note that encodings often have a "canonical" name and several alternate names.

Technical Info
--------------
Lightgrep is implemented in portable C++17 but exposes a concise C API. The core of the API is defined in [include/lightgrep/api.h](./include/lightgrep/api.h). You can see a small example program at [c_example/main.c](./c_example/main.c).

Lightgrep depends on a number of [Boost](http://www.boost.org/) libraries and also on [ICU](http://www.icu-project.org).

Install
-------
See the [BUILD.md file](BUILD.md) for installation instructions.
