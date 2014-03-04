#include "giskard-object.h"

// Creates a new class
object_t *new_class(stack_t *parents) {
	object_t *obj;

	obj = tmalloc(sizeof(object_t));
	obj->classdef = obj;
	obj->type = O_OBJECT;
	obj->parents = parents;
	obj->symtab = new_hashmap();
	obj->code = NULL;
	obj->exec = NULL;
	return (obj);
}

// Creates a news scalar object.
object_t *new_scalar_object(object_type_t type, void *value) {
	object_t *obj;

	obj = tmalloc(sizeof(object_t));
	obj->type = type;
	obj->classdef = NULL;
	obj->parents = new_stack();
	obj->symtab = new_hashmap();
	obj->value = value;
	obj->code = NULL;
	obj->exec = NULL;
	return (obj);
}

// Creates a new object
object_t *new_object(object_t *classdef) {
	object_t *obj;

	obj = tmalloc(sizeof(object_t));
	obj->type = O_OBJECT;
	obj->classdef = classdef;
	obj->parents = classdef->parents;
	obj->symtab = new_hashmap();
	obj->value = obj->code = NULL;
	obj->exec = NULL;
	return (obj);
}

// Set the bytecode pointer of an object.
void object_set_code(object_t *obj, void *code) {
	obj->code = code;
}

// Set the executable function of an object.
void object_set_exec(object_t *obj, object_exec_t exec) {
	obj->exec = exec;
}

// Add a symbol to an object.
void object_add_symbol(object_t *obj, char *name, object_t *value) {
	hashmap_add(obj->symtab, name, value);
}
