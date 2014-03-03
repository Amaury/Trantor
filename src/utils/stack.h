#ifndef __STACK_H__
#define __STACK_H__

#include <stdlib.h>

/**
 * Stack structure.
 * @field	count	Number of elements in the stack.
 * @field	size	Size of the stack.
 * @field	buckets	Array of pointers.
 */
typedef struct {
	size_t count;
	size_t size;
	void **buckets;
} stack_t;

/**
 * Create a new stack.
 * @return	A pointer to the new stack.
 */
stack_t *new_stack(void);

/**
 * Add a new element at the end of a stack.
 * @param	stack	Pointer to the stack.
 * @param	data	Pointer to the element.
 */
void stack_add(stack_t *stack, void *data);

/**
 * Insert an element at a given offset in a stack.
 * @param	stack	Pointer to the stack.
 * @param	offset	Position of the insertion.
 * @param	data	Pointer to the element.
 */
void stack_insert(stack_t *stack, size_t offset, void *data);

/**
 * Returns an element stored in a stack.
 * @param	stack	Pointer to the stack.
 * @param	offset	Position of the element in the stack.
 * @return	A pointer to the element.
 */
void *stack_get(stack_t *stack, size_t offset);

/**
 * Removes an element from a stack and returns it.
 * @param	stack	Pointer to the stack.
 * @param	offset	Position of the element in the stack.
 * @return	A pointer to the element.
 */
void *stack_remove(stack_t *stack, size_t offset);

/**
 * Removes the last element of a stack and returns it.
 * @param	stack	Pointer to the stack.
 * @return	A pointer to the element.
 */
void *stack_pop(stack_t *stack);

/**
 * Resizes a stack.
 * @param	stack	Pointer to the stack.
 * @param	size	New size of the stack.
 */
void stack_resize(stack_t *stack, size_t size);

#endif // __STACK_H__
