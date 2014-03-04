#ifndef __LABEL_H__
#define	__LABEL_H__

/**
 * Immutable strings structure.
 * A hash value is computed from the string using the SDBM algorithm.
 * @field	buffer_size	Number of bytes used to store the string.
 * @field	string_length	Size of the stored string.
 * @field	s		Allocated buffer.
 * @field	hash_value	Hashed value of the string.
 */
typedef struct {
	size_t buffer_size;
	size_t string_length;
	unsigned char *s;
	unsigned long int hash_value;
} label_t;

/**
 * Immutable string constructor.
 * @param	s	Initial string.
 * @return	Pointer to the initialized string.
 */
label_t *new_label(char *s);
/**
 * Immutable string constructor, from a buffer.
 * @param	s	Pointer to the source buffer.
 * @param	size	Size of the data, excluding the trailing '\0' character.
 * @return	Pointer to the initialized string.
 */
label_t *new_label_from_buffer(void *ptr, size_t size);
/**
 * Immutable string cloning function.
 * @param	src	Pointer to the original string.
 * @return	Pointer to the copied string.
 */
label_t *label_clone(label_t *src);
/**
 * Returns a pointer of the raw UTF-8 string.
 * @param	me	Pointer to the string.
 * @return	A pointer to the raw character string.
 */
unsigned char *label_get_ptr(label_t *label);
/**
 * Returns the hash value of a label.
 * @param	me	Pointer to the string.
 * @return	The hash value.
 */
unsigned long int label_get_hash_value(label_t *label);
/**
 * Returns the number of UTF-8 characters in a string (exluding the trailing '\0' byte).
 * @param	me	Pointer to the string.
 * @return	The number of UTF-8 characters in the string.
 */
size_t label_get_length(label_t *label);
/**
 * Returns the number of bytes used to store a string (including the trailing '\0' byte).
 * @param	me	Pointer to the string.
 * @return	The number of bytes used to store the string.
 */
size_t label_get_size(label_t *label);

#endif // __LABEL_H__
