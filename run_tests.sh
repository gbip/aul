#!/bin/bash
mkdir tests
cd tests
export CC=/usr/bin/clang
cmake ..
make aul
./aul ../lex_tests/test_c.c
