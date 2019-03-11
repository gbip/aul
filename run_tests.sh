#!/bin/bash
mkdir tests
cd tests
cmake ..
./aul ../lex_tests/test_c.c
