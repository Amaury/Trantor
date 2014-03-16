#ifndef __VM_H__
#define __VM_H__

#include "utils/buffstr.h"
#include "utils/hashmap.h"
#include "utils/stack.h"
#include "utils/hashstack.h"

/**
 * Virtual machine structure.
 * @field	globals		Global symbols table.
 * @field	ast		Abstract syntax tree.
 * @field	bytecode	Buffer of executable bytecode.
 */
typedef struct {
	hashmap_t *globals;
	stack_t *ast;
	buffstr_t *bytecode;
} vm_t;

/**
 * Creates a virtual machine.
 * @param	ast	Pointer to the base AST nodes.
 * @return	Pointer to the created VM.
 */
vm_t *new_vm(stack_t *ast);

/** Interprets the AST code. */
void vm_exec(vm_t *vm);

#endif // __VM_H__
