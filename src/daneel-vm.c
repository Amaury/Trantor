#include "utils/utils.h"
#include "daneel-vm.h"

// private functions
void _vm_init_globals(vm_t *vm);

// Creates a virtual machine.
vm_t *new_vm() {
	vm_t *vm;

	vm = tmalloc(sizeof(vm_t));
	vm->globals = new_hashmap();
	vm->bytecode = new_buffstr(4096);
	_vm_init_globals(vm);
	return (vm);
}

/* ********** PRIVATE FUNCTIONS *********** */
/**
 * Initialize global variables.
 * @param	vm	Pointer to the VM.
 */
void _vm_init_globals(vm_t *vm) {
	
}
