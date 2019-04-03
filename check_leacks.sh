#!/bin/bash

valgrind --leak-check=full cmake-build-debug/src/compiler/aul lex_tests/test_c.c  test_c.bin
