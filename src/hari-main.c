#include <stdio.h>
#include <stdbool.h>
#include "utils/hashmap.h"
#include "utils/utils.h"
#include "utils/buffstr.h"
#include "yugo-ast.h"
#include "salvor-bytecode.h"

/* External definitions, see preem-grammar.y file. */
extern int yyparse();
extern FILE *yyin;
extern stack_t *root_statements;

/** Main function. */
int main(int argc, char **argv) {
	bool given_file = false;
	vm_t *vm;

	// parsing
	if (argc > 1) {
		given_file = true;
		yyin = fopen(argv[1], "r");
	}
	yyparse();
	if (given_file)
		fclose(yyin);
	print_stack(root_statements, 0);
	// VM creation
	vm = new_vm();
	// bytecode generation
	bytecode_generator(vm, root_statements);
	print_bytecode(vm->bytecode);
	return (0);
}
