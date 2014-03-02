#include "utils/utils.h"
#include "daneel-vm.h"

vm_t *new_vm() {
	vm_t *daneel;

	daneel = tmalloc(sizeof(vm_t));
	daneel->mule = new_memory_manager();
	daneel->plan = new_buffstr(4096);
	return (daneel);
}
