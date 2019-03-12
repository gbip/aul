#!/bin/bash
mkdir tests
cd tests
cmake ..
make aul
./aul ../lex_tests/test_c.c
