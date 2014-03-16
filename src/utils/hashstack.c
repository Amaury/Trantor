#include "hashstack.h"

// Create a new hashstack.
hashstack_t *new_hashstack() {
	hashstack_t *hs;

	hs = (hashstack_t*)new_stack();
	return (hs);
}

// Add a new hashmap on top of a hashstack.
void hashstack_push(hashstack_t *hashstack, hashmap_t *hashmap) {
	stack_add((stack_t*)hashstack, hashmap);
}

// Removes the last hashmap of a hashstack and returns it.
hashmap_t *hashstack_pop(hashstack_t *hashstack) {
	return ((hashmap_t*)stack_pop((stack_t*)hashstack));
}

// Search a symbol in a hashstack.
void *hashstack_search(hashstack_t *hashstack, char *symbol) {
	size_t offset;
	stack_t *stack = (stack_t*)hashstack;
	hashmap_t *hm;
	void *result;

	for (offset = 0; offset < stack->count; ++offset) {
		hm = stack_get(stack, offset);
		if ((result = hashmap_search(hm, symbol)))
			return (result);
	}
	return (NULL);
}

// Search a symbol in a hashstack from an integer value.
void *hashstack_search_from_int(hashstack_t *hashstack, long int value) {
	size_t offset;
	stack_t *stack = (stack_t*)hashstack;
	hashmap_t *hm;
	void *result;

	for (offset = 0; offset < stack->count; ++offset) {
		hm = stack_get(stack, offset);
		if ((result = hashmap_search_from_int(hm, value)))
			return (result);
	}
	return (NULL);
}

// Set a symbol in the upper hashmap of a hashstack.
void hashstack_set(hashstack_t *hashstack, char *key, void *data) {
	stack_t *stack = (stack_t*)hashstack;
	hashmap_t *hm;

	// create the hashmap if there is none, fetch the upper one otherwise
	if (!stack->count) {
		hm = new_hashmap();
		stack_add(stack, hm);
	} else
		hm = stack_get(stack, (stack->count - 1));
	hashmap_add(hm, key, data);
}

// Set a symbol in the upper hashmap of a hashstack, from an integer value key.
void hashstack_set_from_int(hashstack_t *hashstack, char *key, long int value, void *data) {
	stack_t *stack = (stack_t*)hashstack;
	hashmap_t *hm;

	// create the hashmap if the is none, fetch the upper one otherwise
	if (!stack->count) {
		hm = new_hashmap();
		stack_add(stack, hm);
	} else
		hm = stack_get(stack, (stack->count - 1));
	hashmap_add_from_int(hm, key, value, data);
}

// Resizes a hashstack.
void hashstack_resize(hashstack_t *hashstack, size_t size) {
	stack_resize((stack_t*)hashstack, size);
}
