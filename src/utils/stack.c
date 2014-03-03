#include <string.h>
#include "stack.h"
#include "utils.h"

/** @define STACK_DEFAULT_SIZE	Size of a newly created stack. */
#define STACK_DEFAULT_SIZE	16
/** @define STACK_SIZE	Compute the size of a stack. */
#define STACK_SIZE(s)	((s < 16) ? 16 : \
			 (s < 256) ? 256 : \
			 (s < 4096) ? 4096 : \
			 (s < 65535) ? 65535 : \
			 (s < 524288) ? 524288 : ((s) * 2))

// Create a new stack.
stack_t *new_stack() {
	stack_t *stack;

	stack = tmalloc(sizeof(stack_t));
	stack->count = 0;
	stack->size = STACK_DEFAULT_SIZE;
	stack->buckets = tmalloc(STACK_DEFAULT_SIZE * sizeof(void*));
	return (stack);
}

// Add an element at the end of a stack.
void stack_add(stack_t *stack, void *data) {
	if (stack->size < (stack->count + 1))
		stack_resize(stack, stack->size + 1);
	stack->buckets[stack->count] = data;
	stack->count++;
}

// Insert an element at a given offset in a stack.
void stack_insert(stack_t *stack, size_t offset, void *data) {
	if (offset == stack->count)
		return (stack_add(stack, data));
	if (offset > stack->count)
		offset = stack->count;
	else
		memmove(&(stack->buckets[offset]), &(stack->buckets[offset + 1]), stack->count - offset);
	stack->buckets[offset] = data;
}

// Returns an element stored in a stack.
void *stack_get(stack_t *stack, size_t offset) {
	return (stack->buckets[offset]);
}

// Removes an element from a stack and returns it
void *stack_remove(stack_t *stack, size_t offset) {
	void *data = NULL;

	if (offset < stack->count) {
		data = stack->buckets[offset];
		memmove(&(stack->buckets[offset]), &(stack->buckets[offset + 1]), (stack->count - offset));
	}
	return (data);
}

// Removes the last element of a stack and returns it
void *stack_pop(stack_t *stack) {
	void *data = NULL;

	if (stack->count) {
		data = stack->buckets[stack->count - 1];
		--stack->count;
	}
	return (data);
}

// Resizes a stack.
void stack_resize(stack_t *stack, size_t size) {
	size_t new_size;
	void **buckets;

	new_size = STACK_SIZE(size);
	buckets = tmalloc(new_size);
	memcpy(buckets, stack->buckets, stack->count);
	stack->buckets = buckets;
	stack->size = new_size;
}
