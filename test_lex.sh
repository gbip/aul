#/bin/bash
flex -o src/lex.yy.c src/lex.l 
gcc -o test_lex src/lex.yy.c -lfl
