#ifndef __DANEEL_VM_H__
#define __DANEEL_VM_H__

#include "utils/buffstr.h"
#include "mule-memory.h"

typedef struct {
	memory_manager_t *mule;
	buffstr_t *plan;
} vm_t;

vm_t *new_vm(void);

#endif // __DANEEL_VM_H__
