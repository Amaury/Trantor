#ifndef __DANEEL_H__
#define __DANEEL_H__

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

#endif // __DANEEL_H__
