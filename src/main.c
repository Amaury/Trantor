#include <stdio.h>
#include <stdbool.h>
#include "hashmap.h"
#include "utils.h"
#include "node.h"

extern int yyparse();
extern FILE *yyin;
extern stack_t *root_instructions;

bool show_pair(char *key, long int hashval, void *data, void *privdata);
bool show_pair(char *key, long int hashval, void *data, void *privdata) {
	printf("- '%s' => '%s'\n", key, (char*)data);
	return (true);
}

int main(int argc, char **argv) {
	bool given_file = false;

	if (argc > 1) {
		given_file = true;
		yyin = fopen(argv[1], "r");
	}
	yyparse();
	if (given_file)
		fclose(yyin);
	print_stack(root_instructions, 0);
	return 0;
}
