#ifndef __HASHMAP_H__
#define __HASHMAP_H__

#include <stdlib.h>
#include <stdbool.h>

/**
 * Hashmap structure.
 * @field	count	Number of elements in the hashmap.
 * @field	size	Current size of the hashmap.
 * @field	buckets	Array of bucket pointers.
 */
typedef struct {
	size_t count;
	size_t size;
	struct hashmap_bucket_s **buckets;
} hashmap_t;

/**
 * Hashmap bucket.
 * @field	key	Element's key.
 * @field	hashval	Hashed value of the key.
 * @field	data	Pointer to the element's data.
 * @field	prev	Pointer to the previous element with the same hash value.
 * @field	next	Pointer to the next element with the same hash value.
 */
typedef struct hashmap_bucket_s {
	char *key;
	long int hashval;
	void *data;
	struct hashmap_bucket_s *prev;
	struct hashmap_bucket_s *next;
} hashmap_bucket_t;

/**
 * Creates a new hashmap.
 * @return	A pointer to the created hashmap.
 */
hashmap_t *new_hashmap(void);
/**
 * Add a new element to a hashmap, indexed by a null-terminated string.
 * @param	hm	Pointer to the hashmap.
 * @param	key	Pointer to the character string.
 * @param	data	Pointer to the value.
 */
void hashmap_add(hashmap_t *hm, char *key, void *data);
/**
 * Add a new element to a hashmap, indexed by an integer value. This value could
 * have been computed from the given character string, or be any other value
 * (a pointer for example) if the key is set to NULL.
 * @param	hm		Pointer to the hashmap.
 * @param	key		Pointer to the character string (could be NULL).
 * @param	hash_value	Integer value used to index the element.
 * @param	data		Pointer to the element.
 */
void hashmap_add_from_int(hashmap_t *hm, char *key, long int hash_value, void *data);
/**
 * Remove an element from a hashmap, from its null-terminated character string key.
 * @param	hm	Pointer to the hashmap.
 * @param	key	Pointer to the string key.
 * @return	True if the element was removed.
 */
bool hashmap_remove(hashmap_t *hm, char *key);
/**
 * Remove an element from its numeric index value.
 * @param	hm		Pointer to the hashmap.
 * @param	hash_value	Integer value used to index the element.
 * @return	True if the element was removed.
 */
bool hashmap_remove_from_int(hashmap_t *hm, long int hash_value);
/**
 * Search an element in a hashmap, from its null-termined string key.
 * @param	hm	Pointer to the hashmap.
 * @param	key	Pointer to the string key.
 * @return	A pointer to the value associated to the key.
 */
void *hashmap_search(hashmap_t *hm, char *key);
/**
 * Search an element in a hashmap, from its numeric index value.
 * @param	hm		Pointer to the hashmap.
 * @param	hash_value	Integer value used to index the element.
 * @return	A pointer to the value associated to the key.
 */
void *hashmap_search_from_int(hashmap_t *hm, long int hash_value);
/**
 * Process a function on every element of a hashmap.
 * @param	hm	Pointer to the hashmap.
 * @param	f	Pointer to the function called for each element.
 * @param	data	Private data given to the function.
 * @return	The number of processed elements.
 */
size_t hashmap_foreach(hashmap_t *hm, bool (*f)(char *key, long int hash_value, void *data, void *private_data), void *data);
/**
 * Resize a hashmap to expand or shrink its capacity.
 * @param	hm	Pointer to the hashmap.
 * @param	size	New size of the hashmap.
 */
void hashmap_resize(hashmap_t *hm, size_t size);
/**
 * Returns a list which contains the keys of a hashmap.
 * @param	hm	Pointer to the hashmap.
 */
void hashmap_keys(hashmap_t *hm);

#endif // __HASHMAP_H__
