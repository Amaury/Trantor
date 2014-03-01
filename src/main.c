#include <stdio.h>
#include <stdbool.h>
#include "utils/hashmap.h"
#include "utils/utils.h"
#include "node.h"

extern int yyparse();
extern FILE *yyin;
extern stack_t *root_statements;

int main(int argc, char **argv) {
	bool given_file = false;

	if (argc > 1) {
		given_file = true;
		yyin = fopen(argv[1], "r");
	}
	yyparse();
	if (given_file)
		fclose(yyin);
	print_stack(root_statements, 0);
	return 0;
}
