#include "utils/utils.h"
#include "mule-memory.h"

memory_manager_t *new_memory_manager() {
	memory_manager_t *mule;

	mule = tmalloc(sizeof(memory_manager_t));
	return (mule);
}
