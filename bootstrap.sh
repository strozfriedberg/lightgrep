#!/bin/sh

autoreconf -fi

# if you want to build for AddressSanitizer:
# ./configure CXXFLAGS="-g -O0 -fsanitize=address -fno-omit-frame-pointer" LINKFLAGS="-fsanitize=address -fno-omit-frame-pointer"
