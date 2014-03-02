#include <stdio.h>
#include <stdbool.h>
#include "utils/hashmap.h"
#include "utils/utils.h"
#include "utils/buffstr.h"
#include "yugo-node.h"
#include "salvor-bytecode.h"

extern int yyparse();
extern FILE *yyin;
extern stack_t *root_statements;

int main(int argc, char **argv) {
	bool given_file = false;
	buffstr_t *bytecode;

	// parsing
	if (argc > 1) {
		given_file = true;
		yyin = fopen(argv[1], "r");
	}
	yyparse();
	if (given_file)
		fclose(yyin);
	print_stack(root_statements, 0);
	// bytecode generation
	bytecode = new_buffstr(4096);
	bytecode_generator(bytecode, root_statements);
	print_bytecode(bytecode);
	return 0;
}
