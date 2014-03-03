#include <stdio.h>
#include "salvor-bytecode.h"
#include "daneel-vm.h"
#include "yugo-ast.h"

// private methods
void _bytecode_generate(vm_t *daneel, node_t *node);
void _bytecode_node_boolean(vm_t *daneel, node_t *node);
void _bytecode_node_number(vm_t *daneel, node_t *node);
void _bytecode_node_string(vm_t *daneel, node_t *node);
void _bytecode_node_statement(vm_t *daneel, node_t *node);
void _bytecode_node_expression(vm_t *daneel, node_t *node);
void _bytecode_node_identifier(vm_t *daneel, node_t *node);
void _bytecode_node_assignment(vm_t *daneel, node_t *node);
void _bytecode_node_operation(vm_t *daneel, node_t *node);
void _bytecode_node_comparison(vm_t *daneel, node_t *node);
void _bytecode_node_condition(vm_t *daneel, node_t *node);
void _bytecode_node_while(vm_t *daneel, node_t *node);
void _bytecode_node_funcdef(vm_t *daneel, node_t *node);
void _bytecode_node_funccall(vm_t *daneel, node_t *node);
void _bytecode_node_class(vm_t *daneel, node_t *node);
void _bytecode_node_return(vm_t *daneel, node_t *node);
void _bytecode_node_break(vm_t *daneel, node_t *node);
void _bytecode_node_continue(vm_t *daneel, node_t *node);
void _bytecode_node_methcall(vm_t *daneel, node_t *node);
// array of code
struct {
	node_type_t type;
	void (*f)(vm_t *daneel, node_t *node);
} _bytecode_generators[] = {
	{N_BOOLEAN, _bytecode_node_boolean},
	{N_NUMBER, _bytecode_node_number},
	{N_STRING, _bytecode_node_string},
	{N_STATEMENT, _bytecode_node_statement},
	{N_EXPRESSION, _bytecode_node_expression},
	{N_IDENTIFIER, _bytecode_node_identifier},
	{N_ASSIGNMENT, _bytecode_node_assignment},
	{N_OPERATION, _bytecode_node_operation},
	{N_COMPARISON, _bytecode_node_comparison},
	{N_CONDITION, _bytecode_node_condition},
	{N_WHILE, _bytecode_node_while},
	{N_FUNC_DEF, _bytecode_node_funcdef},
	{N_FUNC_CALL, _bytecode_node_funccall},
	{N_CLASS, _bytecode_node_class},
	{N_RETURN, _bytecode_node_return},
	{N_BREAK, _bytecode_node_break},
	{N_CONTINUE, _bytecode_node_continue},
	{N_METH_CALL, _bytecode_node_methcall}
};

// Generates bytecode stream from a list of statements.
void bytecode_generator(vm_t *daneel, stack_t *statements) {
	unsigned char c = (unsigned char)OP_NOOP;
	size_t stmt_offset;

	buffstr_append(daneel->plan, &c, 1);
	for (stmt_offset = 0; stmt_offset < statements->count; ++stmt_offset) {
		node_t *node = stack_get(statements, stmt_offset);
		_bytecode_generate(daneel, node);
	}
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
void _bytecode_generate(vm_t *daneel, node_t *node) {
	void (*f)(vm_t *daneel, node_t *node);

	f = _bytecode_generators[(int)node->type].f;
	f(daneel, node);
}
void _bytecode_node_boolean(vm_t *daneel, node_t *node) {
	unsigned char c = (unsigned char)OP_NOOP;

	buffstr_append(daneel->plan, &c, 1);
}
void _bytecode_node_number(vm_t *daneel, node_t *node) {
}
void _bytecode_node_string(vm_t *daneel, node_t *node) {
}
void _bytecode_node_statement(vm_t *daneel, node_t *node) {
}
void _bytecode_node_expression(vm_t *daneel, node_t *node) {
}
void _bytecode_node_identifier(vm_t *daneel, node_t *node) {
}
void _bytecode_node_assignment(vm_t *daneel, node_t *node) {
}
void _bytecode_node_operation(vm_t *daneel, node_t *node) {
}
void _bytecode_node_comparison(vm_t *daneel, node_t *node) {
}
void _bytecode_node_condition(vm_t *daneel, node_t *node) {
}
void _bytecode_node_while(vm_t *daneel, node_t *node) {
}
void _bytecode_node_funcdef(vm_t *daneel, node_t *node) {
}
void _bytecode_node_funccall(vm_t *daneel, node_t *node) {
}
void _bytecode_node_class(vm_t *daneel, node_t *node) {
}
void _bytecode_node_return(vm_t *daneel, node_t *node) {
}
void _bytecode_node_break(vm_t *daneel, node_t *node) {
}
void _bytecode_node_continue(vm_t *daneel, node_t *node) {
}
void _bytecode_node_methcall(vm_t *daneel, node_t *node) {
}
