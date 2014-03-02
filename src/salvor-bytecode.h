#ifndef __SALVOR_H__
#define __SALVOR_H__

#include "utils/stack.h"
#include "utils/buffstr.h"

/**
 * Generates bytecode stream from a list of statements.
 * @param	buf		Pointer to a buffered string.
 * @param	statements	A list of statements.
 * @return	The resulting bytecode stream.
 */
void bytecode_generator(buffstr_t *buf, stack_t *statements);

/*
 * Show bytecode value.
 * @param	buf	Pointer to the bytecode stream.
 */
void print_bytecode(buffstr_t *buf);

#endif // __SALVOR_H__
