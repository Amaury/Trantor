#ifndef __HASHSTACK_H__
#define __HASHSTACK_H__

#include <stdlib.h>
#include "hashmap.h"
#include "stack.h"

/** A hashstack is simply a stack of hashmaps. */
typedef stack_t hashstack_t;

/**
 * Create a new hashstack.
 * @return	A pointer to the new hashstack.
 */
hashstack_t *new_hashstack(void);

/**
 * Add a new hashmap on top of a hashstack.
 * @param	hashstack	Pointer to the hashstack.
 * @param	hashmap		Pointer to the hashmap to add.
 */
void hashstack_push(hashstack_t *hashstack, hashmap_t *hashmap);

/**
 * Removes the last hashmap of a hashstack and returns it.
 * @param	hashstack	Pointer to the hashstack.
 * @return	A pointer to the removed hashmap.
 */
hashmap_t *hashstack_pop(hashstack_t *hashstack);

/**
 * Search a symbol in a hashstack.
 * @param	hashstack	Pointer to the hashstack.
 * @param	symbol		Pointer to the string key.
 * @return	A pointer to the symbol.
 */
void *hashstack_search(hashstack_t *hashstack, char *symbol);

/**
 * Search a symbol in a hashstack from an integer value.
 * @param	hashstack	Pointer to the hashstack.
 * @param	value		Integer value.
 * @return	A pointer to the symbol.
 */
void *hashstack_search_from_int(hashstack_t *hashstack, long int value);

/**
 * Set a symbol in the upper hashmap of a hashstack.
 * @param	hashstack	Pointer to the hashstack.
 * @param	key		Pointer to the symbol string.
 * @param	data		Pointer to the associated data.
 */
void hashstack_set(hashstack_t *hashstack, char *key, void *data);

/**
 * Set a symbol in the upper hashmap of a hashstack, from an integer value key.
 * @param	hashstack	Pointer to the hashstack.
 * @param	key		Pointer to the character string (could be NULL).
 * @param	value		Key's integer value.
 * @param	data		Pointer to the associated data.
 */
void hashstack_set_from_int(hashstack_t *hashstack, char *key, long int value, void *data);

/**
 * Resizes a hashstack.
 * @param	hashstack	Pointer to the hashstack.
 * @param	size		New size of the hashstack.
 */
void hashstack_resize(hashstack_t *hashstack, size_t size);

#endif // __HASHSTACK_H__
