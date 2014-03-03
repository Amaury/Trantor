#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>

/**
 * Wrapper to malloc().
 * @param	size	Size of the allocated buffer.
 * @return	A pointer to the allocated buffer.
 */
void *tmalloc(size_t size);

/**
 * Allocate and copy a memory buffer, adding a trailing '\0' character.
 * @param	src	Pointer to the source buffer.
 * @param	size	Size of the data.
 * @return	Pointer to the newly allocated buffer.
 */
void *tstrdup(void *src, size_t size);

#endif // __UTILS_H__
