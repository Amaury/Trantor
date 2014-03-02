#include <stdio.h>
#include "salvor-bytecode.h"
#include "daneel-vm.h"
#include "yugo-node.h"

// private methods
void _bytecode_generate(buffstr_t *buf, node_t *node);

// Generates bytecode stream from a list of statements.
void bytecode_generator(buffstr_t *buf, stack_t *statements) {
	unsigned char c = (unsigned char)OP_NOOP;

	buffstr_append(buf, &c, 1);
}

// show bytecode value
void print_bytecode(buffstr_t *buf) {
	size_t i;

	for (i = 0; i < buf->used; ++i) {
		printf("%02x\n", buf->s[i]);
	}
}

/* ********* PRIVATE METHODS ******* */
/**
 * Generates bytecode stream from an AST node.
 * @param	buf	Pointer to a buffered string.
 * @param	node	Pointer to an AST node.
 */
void _bytecode_generate(buffstr_t *buf, node_t *node) {
	
}
