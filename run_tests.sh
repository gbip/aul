#!/bin/bash
mkdir tests
cd tests
export CC=/usr/bin/gcc
cmake ..
make aul
./aul ../lex_tests/test_c.c
