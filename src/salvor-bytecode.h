#ifndef __SALVOR_BYTECODE_H__
#define __SALVOR_BYTECODE_H__

#include "utils/stack.h"
#include "utils/buffstr.h"
#include "daneel-vm.h"

/** List of opcodes. */
typedef enum {
	OP_NOOP = 0,	// do nothing
	OP_PUSH,	// push data on the stack
	OP_DISCARD,	// pop from the stack
	OP_ADD,		// addition
	OP_SUB,		// substraction
	OP_MUL,		// multiplication
	OP_DIV,		// division
	OP_MOD,		// modulus
	OP_BOOL_AND,	// &&
	OP_BOOL_OR,	// ||
	OP_BOOL_NOT,	// !
	OP_EQUAL,	// ==
	OP_IDENTICAL,	// ===
	OP_NEQUAL,	// !=
	OP_NIDENTICAL,	// !==
	OP_ASSIGN,	// =
	OP_RETURN,	// return()
	OP_EXIT,	// exit()
	OP_JMP,		// unconditional jump
	OP_JMPF,	// jump if false
	OP_TARGET,	// jumping target
	OP_FUNCCALL,	// call a function
	OP_END
} opcode_t;

/**
 * Generates bytecode stream from a list of statements.
 * @param	daneel		Pointer to the VM.
 * @param	statements	A list of statements.
 * @return	The resulting bytecode stream.
 */
void bytecode_generator(vm_t *daneel, stack_t *statements);

/*
 * Show bytecode value.
 * @param	buf	Pointer to the bytecode stream.
 */
void print_bytecode(buffstr_t *buf);

#endif // __SALVOR_BYTECODE_H__
