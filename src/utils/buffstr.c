#include <string.h>
#include "buffstr.h"
#include "utils.h"

// Create a buffered string.
buffstr_t *new_buffstr(size_t size) {
	buffstr_t *buf;

	buf = tmalloc(sizeof(buffstr_t));
	buf->s = tmalloc(size);
	buf->size = size;
	buf->used = 0;
	return (buf);
}

// Add data to a buffered string
void buffstr_append(buffstr_t *buf, void *src, size_t size) {
	void *ptr;

	if ((buf->size - buf->used) < size) {
		unsigned char *s;
		size_t new_size;

		new_size = buf->size * 2;
		if (new_size < (buf->used + size))
			new_size = buf->size + size;
		s = tmalloc(new_size);
		memcpy(s, buf->s, buf->used);
		buf->s = s;
		buf->size = new_size;
	}
	ptr = (void*)((size_t)buf->s + buf->used);
	memcpy(ptr, src, size);
	buf->used += size;
}
