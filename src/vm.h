#ifndef __VM_H__
#define __VM_H__

#include "utils/buffstr.h"
#include "utils/hashmap.h"

/**
 * Virtual machine structure.
 * @field	globals		Global symbols table.
 * @field	bytecode	Buffer of executable bytecode.
 */
typedef struct {
	hashmap_t *globals;
	buffstr_t *bytecode;
} vm_t;

/** Creates a virtual machine. */
vm_t *new_vm(void);

#endif // __VM_H__
