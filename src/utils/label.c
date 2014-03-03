/**
 * Immutable UTF-8 string object.
 *
 * UTF-8 code inspired from MicroUTF-8 project (http://puszcza.gnu.org.ua/software/microutf8/).
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "utils.h"
#include "label.h"

#define	UTF8_BOM1	0xEF
#define	UTF8_BOM2	0xBB
#define	UTF8_BOM3	0xBF

// Immutable string constructor.
label_t *new_label(char *s) {
	// pointer to the new label
	label_t *label;
	// len  = number of UTF-8 characters in the string (without the '\0' byte)
	// size = number of bytes needed to store the string (including the trailing '\0')
	size_t len = 0, size = 0;
	// string's hash value
	unsigned long int hash_value = 0;

	label = tmalloc(sizeof(label_t));
	if (s) {
		unsigned char c;

		// is there a BOM?
		if (s[0] && (uint8_t)s[0] == UTF8_BOM1 && 
		    s[1] && (uint8_t)s[1] == UTF8_BOM2 &&
		    s[2] && (uint8_t)s[2] == UTF8_BOM3)
			s += 3;
		// compute string length
		while ((c = (unsigned char)s[size])) {
			// 5 possibilities:
			// 0xxxxxxx					regular ASCII character
			// 110xxxxx (10xxxxxx)				first byte of a two-bytes sequence
			// 1110xxxx (10xxxxxx 10xxxxxx)			first byte of a three-bytes sequence
			// 11110xxx (10xxxxxx 10xxxxxx 10xxxxxx)	first byte of a four-bytes sequence
			// 10xxxxxx					a subsequent byte in a multi-bytes sequence
			//
			// For performance reasons, we assume that the given string is a valid
			// UTF-8 string, so we don't check the string's validity.
			// Then only three possibilities are checked:
			// 0xxxxxxx	ASCII			length += 1 character	size += 1 byte
			// 11xxxxxx	first UTF-8 byte	length += 1 character	size += 1 byte
			// 10xxxxxx	subsequent UTF-8 byte	length unchanged	size += 1 byte
			if (!(c & 0x80) || (c & 0x40))
				++len;
			++size;
			// hash computation, using SDBM algorithm
			hash_value = c + (hash_value << 6) + (hash_value << 16) - hash_value;
		}
	}
	++size;	// count the trailing '\0' character
	label->buffer_size = size;
	label->s = tmalloc(label->buffer_size);
	if (s) {
		memcpy(label->s, s, size);
		label->string_length = len;
	} else
		label->s[0] = '\0';
	return (label);
}
// Immutable string constructor, from a buffer
label_t *new_label_from_buffer(void *ptr, size_t size) {
	// pointer to the new label
	label_t *label;
	// len  = number of UTF-8 characters in the string (without the '\0' byte)
	// size = number of bytes needed to store the string (including the trailing '\0')
	size_t len = 0;
	size_t tmp_size = 0;
	// string's hash value
	unsigned long int hash_value = 0;
	// readable pointer to the buffer
	unsigned char *s = (unsigned char*)ptr;

	label = tmalloc(sizeof(label_t));
	if (s) {
		unsigned char c;

		// is there a BOM?
		if (s[0] && (uint8_t)s[0] == UTF8_BOM1 && 
		    s[1] && (uint8_t)s[1] == UTF8_BOM2 &&
		    s[2] && (uint8_t)s[2] == UTF8_BOM3)
			s += 3;
		// compute string length
		while (tmp_size < size) {
			c = s[tmp_size];
			// 5 possibilities:
			// 0xxxxxxx					regular ASCII character
			// 110xxxxx (10xxxxxx)				first byte of a two-bytes sequence
			// 1110xxxx (10xxxxxx 10xxxxxx)			first byte of a three-bytes sequence
			// 11110xxx (10xxxxxx 10xxxxxx 10xxxxxx)	first byte of a four-bytes sequence
			// 10xxxxxx					a subsequent byte in a multi-bytes sequence
			//
			// For performance reasons, we assume that the given string is a valid
			// UTF-8 string, so we don't check the string's validity.
			// Then only three possibilities are checked:
			// 0xxxxxxx	ASCII			length += 1 character	size += 1 byte
			// 11xxxxxx	first UTF-8 byte	length += 1 character	size += 1 byte
			// 10xxxxxx	subsequent UTF-8 byte	length unchanged	size += 1 byte
			if (!(c & 0x80) || (c & 0x40))
				++len;
			++tmp_size;
			// hash computation, using SDBM algorithm
			hash_value = c + (hash_value << 6) + (hash_value << 16) - hash_value;
		}
	}
	++size;	// count the trailing '\0' character
	label->buffer_size = size;
	label->s = tmalloc(label->buffer_size);
	if (s) {
		memcpy(label->s, s, size);
		label->string_length = len;
	} else
		label->s[0] = '\0';
	return (label);
}
// Immutable string cloning function.
label_t *label_clone(label_t *src) {
	label_t *dst;

	dst = tmalloc(sizeof(label_t));
	dst->string_length = src->string_length;
	dst->buffer_size = src->buffer_size;
	dst->s = tmalloc(src->buffer_size);
	memcpy(dst->s, src->s, src->buffer_size);
	return (dst);
}

// Returns a pointer of the raw UTF-8 string.
unsigned char *label_get_ptr(label_t *label) {
	return (label->s);
}
// Returns the hash value of a label.
unsigned long int label_get_hash_value(label_t *label) {
	return (label->hash_value);
}
// Returns the number of UTF-8 characters in a string.
size_t label_get_length(label_t *label) {
	return (label->string_length);
}
// Returns the number of bytes used to store a string.
size_t label_get_size(label_t *label) {
	return (label->buffer_size);
}
