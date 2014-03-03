#include <string.h>
#include <stdio.h>
#include "hashmap.h"
#include "utils.h"

/** @define HASHMAP_DEFAULT_SIZE	Size of a newly created hashmap. */
#define	HASHMAP_DEFAULT_SIZE	16
/** @define HASHMAP_SIZE		Compute the size of a hashmap. */
#define	HASHMAP_SIZE(s)	((s < 16) ? 16 : \
			 (s < 256) ? 256 : \
			 (s < 4096) ? 4096 : \
			 (s < 65535) ? 65535 : \
			 (s < 524288) ? 524288 : ((s) * 2))
/** @define HASHMAP_MAX_LOAD_FACTOR Maximum load factor of a hashmap before increasing it. */
#define HASHMAP_MAX_LOAD_FACTOR	0.7
/** @define YHM_MIN_LOAD_FACTOR Minimum load factor of a hash map before reducing it. */
#define HASHMAP_MIN_LOAD_FACTOR	0.25

/* ********** PRIVATE FUNCTIONS ********* */
static long int _hashmap_hash(const char *key);
hashmap_t *_create_hashmap(size_t size);
bool _hashmap_copy(char *key, long int hash_value, void *data, void *private_data);

// create a hashmap
hashmap_t *new_hashmap() {
	return (_create_hashmap(HASHMAP_DEFAULT_SIZE));
}

// add an element to a hashmap
void hashmap_add(hashmap_t *hm, char *key, void *data) {
	long int hash_value;

	// compute the key's hash value
	hash_value = _hashmap_hash(key);
	// add the element
	hashmap_add_from_int(hm, key, hash_value, data);
}

// add an element to a hashmap, from an integer value (its hashed value for instance)
void hashmap_add_from_int(hashmap_t *hm, char *key, long int hash_value, void *data) {
	float load_factor;
	long int hash_offset;
	hashmap_bucket_t **pbucket, *bucket;

	// resize the map if its load factor would excess the limit
	load_factor = (float)(hm->count + 1) / hm->size;
	if (load_factor > HASHMAP_MAX_LOAD_FACTOR)
		hashmap_resize(hm, (hm->size + 1));
	// compute the key's hash offset
	hash_offset = hash_value % hm->size;
	// checking the bucket
	pbucket = &(hm->buckets[hash_offset]);
	if (*pbucket == NULL) {
		// no bucket, create a new one
		bucket = tmalloc(sizeof(hashmap_bucket_t));
		bucket->key = key;
		bucket->hashval = hash_value;
		bucket->data = data;
		bucket->prev = bucket;
		bucket->next = NULL;
		*pbucket = bucket;
		hm->count++;
		return;
	}
	// there is a bucket, check for the key
	for (bucket = *pbucket; bucket; bucket = bucket->next) {
		if (hash_value == bucket->hashval) {
			bucket->data = data;
			return;
		}
	}
	bucket = tmalloc(sizeof(hashmap_bucket_t));
	bucket->key = key;
	bucket->hashval = hash_value;
	bucket->data = data;
	bucket->prev = (*pbucket)->prev;
	bucket->next = NULL;
	(*pbucket)->prev->next = bucket;
	(*pbucket)->prev = bucket;
	hm->count++;
}

// Remove an element from a hashmap.
bool hashmap_remove(hashmap_t *hm, char *key) {
	long int hash_value;

	// compute the key's hash value
	hash_value = _hashmap_hash(key);
	// add the value
	return (hashmap_remove_from_int(hm, hash_value));
}

bool hashmap_remove_from_int(hashmap_t *hm, long int hash_value) {
	hashmap_bucket_t *bucket;
	long int hash_offset;

	// compute the element offset
	hash_offset = hash_value % hm->size;
	// retreiving the bucket
	bucket = hm->buckets[hash_offset];
	if (!bucket)
		return (false);
	if (!bucket->next) {
		hm->buckets[hash_value] = NULL;
		return (true);
	}
	for (; bucket; bucket = bucket->next) {
		// is it the right key?
		if (hash_value != bucket->hashval)
			continue;
		// is it the first bucket in the line
		if (bucket == hm->buckets[hash_offset]) {
			hm->buckets[hash_offset] = bucket->next;
			bucket->next->prev = bucket->prev;
			return (true);
		}
		// another bucket
		bucket->prev->next = bucket->next;
		if (!bucket->next)
			hm->buckets[hash_offset]->prev = bucket->prev;
		return (true);
	}
	return (false);
}

// Search an value in a hash map
void *hashmap_search(hashmap_t *hm, char *key) {
	long int hash_value;

	// compute the key's hash value
	hash_value = _hashmap_hash(key);
	// search
	return (hashmap_search_from_int(hm, hash_value));
}

void *hashmap_search_from_int(hashmap_t *hm, long int hash_value) {
	long int hash_offset;
	hashmap_bucket_t *bucket;

	// compute the key's offset
	hash_offset = hash_value % hm->size;
	// retreiving the bucket
	bucket = hm->buckets[hash_offset];
	if (!bucket)
		return (NULL);
	if (!bucket->next)
		return (bucket->data);
	for (; bucket; bucket = bucket->next) {
		if (hash_value == bucket->hashval)
			return (bucket->data);
	}
	return (NULL);
}

// process a function on every element of a hashmap
size_t hashmap_foreach(hashmap_t *hm, bool (*f)(char *key, long int hash_value, void *data, void *private_data), void *data) {
	size_t offset, nbr_processed;
	hashmap_bucket_t *bucket;
	bool res;

	// loop on every line of buckets
	for (offset = 0, nbr_processed = 0;
	     offset < hm->size && nbr_processed < hm->count;
	     ++offset) {
		// loop on every line of buckets
		for (bucket = hm->buckets[offset]; bucket; bucket = bucket->next) {
			nbr_processed++;
			res = f(bucket->key, bucket->hashval, bucket->data, data);
			if (!res)
				goto end_foreach;
		}
	}
end_foreach:
	return (nbr_processed);
}

// Resize a hashmap.
void hashmap_resize(hashmap_t *hm, size_t size) {
	hashmap_t *new_hashmap;

	new_hashmap = _create_hashmap(size);
	hashmap_foreach(hm, _hashmap_copy, new_hashmap);
	hm->size = new_hashmap->size;
	hm->buckets = new_hashmap->buckets;
}

// show the list of keys in a hashmap
void hashmap_keys(hashmap_t *hm) {
	size_t offset, nbr_processed;
	hashmap_bucket_t *bucket;

	// loop on every line of buckets
	for (offset = 0, nbr_processed = 0;
	     offset < hm->size && nbr_processed < hm->count;
	     ++offset) {
		// loop on every buckets of the line
		for (bucket = hm->buckets[offset]; bucket; bucket = bucket->next) {
			if (bucket->key)
				printf("> '%s'\n", bucket->key);
			else
				printf("> [%ld]\n", bucket->hashval);
		}
	}
}

/* ************ PRIVATE FUNCTIONS ********* */
// copy an element from a list to another
bool _hashmap_copy(char *key, long int hash_value, void *data, void *private_data) {
	hashmap_t *dest = private_data;

	hashmap_add_from_int(dest, key, hash_value, data);
	return (true);
}

/**
 * @function	_hashmap_hash
 *		Compute the hash value of a key, using the SDBM algorithm.
 * @see		http://www.cse.yorku.ca/~oz/hash.html
 * @see		http://en.literateprograms.org/Hash_function_comparison_%28C,_sh%29
 * @param	Key	The data to hash.
 * @return	The computed hash value.
 */
static long int _hashmap_hash(const char *key) {
	long int hash_value;

	for (hash_value = 0; *key; key++)
		hash_value = *key + (hash_value << 6) + (hash_value << 16) - hash_value;
	return (hash_value);
}

// create a hashmap with a given size
hashmap_t *_create_hashmap(size_t size) {
	hashmap_t *hashmap = tmalloc(sizeof(hashmap_t));

	size = HASHMAP_SIZE(size);
	hashmap->count = 0;
	hashmap->size = size;
	size *= sizeof(hashmap_bucket_t*);
	hashmap->buckets = tmalloc(size);
	memset(hashmap->buckets, 0, size);
	return (hashmap);
}
