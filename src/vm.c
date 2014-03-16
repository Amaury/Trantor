#include <stdio.h>
#include "utils/utils.h"
#include "vm.h"
#include "ast.h"

// private functions
void _vm_init_globals(vm_t *vm);

// Creates a virtual machine.
vm_t *new_vm(stack_t *ast) {
	vm_t *vm;

	vm = tmalloc(sizeof(vm_t));
	vm->ast = ast;
	vm->globals = new_hashmap();
	vm->bytecode = new_buffstr(4096);
	_vm_init_globals(vm);
	return (vm);
}

// Interprets the AST code.
void vm_exec(vm_t *vm) {
	size_t offset;
	node_t *node;
	hashstack_t *ctx_stack;

	ctx_stack = new_hashstack();
	printf("\n\n------------------------\nEXEC\n-----------------\n\n");
	for (offset = 0; offset < vm->ast->count; ++offset) {
		node = stack_get(vm->ast, offset);
		print_node(node, 0);
	}
}

/* ********** PRIVATE FUNCTIONS *********** */
/**
 * Initialize global variables.
 * @param	vm	Pointer to the VM.
 */
void _vm_init_globals(vm_t *vm) {
	
}
