#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include "utils/hashmap.h"
#include "object.h"

void interpreter_exec_ast(vm_t *vm, node_t *node, hashmap_t *context);

#endif // __INTERPRETER_H__
