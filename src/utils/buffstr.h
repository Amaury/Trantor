#ifndef __BUFFSTR_H__
#define __BUFFSTR_H__

/**
 * Buffered string structure.
 * @field	size	Total size of the buffer.
 * @field	used	Used space in the buffer.
 * @field	s	Allocated buffer.
 */
typedef struct {
	size_t size;
	size_t used;
	unsigned char *s;
} buffstr_t;

/**
 * Create a buffered string.
 * @param	size	Initial size of the buffer.
 * @return	A pointer to the buffered string.
 */
buffstr_t *new_buffstr(size_t size);

/**
 * Add data to a buffered string
 * @param	buf	Pointer to the buffered string.
 * @param	src	Pointer to the buffer to append.
 * @param	size	Size of the data to append.
 */
void buffstr_append(buffstr_t *buf, void *src, size_t size);

#endif // __BUFFSTR_H__
