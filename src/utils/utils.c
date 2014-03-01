#include <string.h>
#include "utils.h"
#include "gc.h"

// malloc wrapper
void *tmalloc(size_t size) {
	return (GC_malloc(size));
}

// allocate and copy a memory buffer, adding a trailing '\0' character
void *tstrdup(void *src, size_t size) {
	void *dest;

	dest = tmalloc(size + 1);
	memcpy(dest, src, size);
	((char*)dest)[size] = '\0';
	return (dest);
}
