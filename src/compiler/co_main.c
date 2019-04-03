#include "co_ir.h"
#include "gen/lex.yy.h"
#include "gen/syntax.h"
#include <fcntl.h>
#include <stdio.h>

void yyerror(char* mess) {
	printf("Line %d: %s \nFound \"%s\"\n", yylineno, mess, yytext);
}

int main(int argc, char** argv) {
	/* to remove */
	if(argc != 3) {
		printf("Usage : %s <file> <output>\n", argv[0]);
		return 1;
	}
	printf("Building %s ...\n", argv[1]);
	void* file = fopen(argv[1], "r");
	if(file == NULL) {
		printf("File does not exist");
		return 1;
	}
	yyin = file;
	int error = yyparse();
	fclose(yyin);
	if(error) {
		printf("Compilation failed\n");
		return 1;
	} else {
		print_ast(get_ast());
		printf("AST built, building intermediate representation tree ...\n");
		ir_body* irt = ir_build_tree(get_ast());
		printf("===== Generated asm code : =====\n\n\n");
		ir_print_debug(irt);
		ir_write_to_file(argv[2], irt);
		printf("\nFree AST and IRT...\n");
		free_ast(get_ast());
		free_ir(irt);
		return 0;
	}
}