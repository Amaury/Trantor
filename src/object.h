#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "utils/stack.h"
#include "utils/hashmap.h"

/** Executable function. */
typedef struct object_s *(*object_exec_t)(stack_t *params);

/**
 * Object type.
 * @value	O_BOOLEAN	Boolean.
 * @value	O_NUMBER	Number.
 * @value	O_STRING	String.
 * @value	O_LABEL		Label.
 * @value	O_OBJECT	Object.
 */
typedef enum {
	O_BOOLEAN = 0,
	O_NUMBER,
	O_STRING,
	O_LABEL,
	O_OBJECT
} object_type_t;

/**
 * Object definition.
 * @field	type		Object's basic type.
 * @field	classdef	Pointer to the object's class definition.
 * @field	parents		Parent classes.
 * @field	symtab		Object's symbol table.
 * @field	value		Pointer to the value, for scalar types.
 * @field	code		Pointer to the object's bytecode (if it's a function).
 * @field	exec		Pointer to the object's real code (if it's a function).
 */
typedef struct object_s {
	object_type_t type;
	struct object_s *classdef;
	stack_t *parents;
	hashmap_t *symtab;
	void *value;
	void *code;
	object_exec_t exec;
} object_t;

/**
 * Creates a new class definition.
 * @param	parents	List of class' parents.
 * @return	A pointer to the class object.
 */
object_t *new_class(stack_t *parents);
/**
 * Creates a new scalar object.
 * @param	type	Object type.
 * @param	value	Pointer to the object value.
 * @return	A pointer to the created object.
 */
object_t *new_scalar_object(object_type_t type, void *value);
/**
 * Creates a new object.
 * @param	classdef	Pointer to the object's class definition. Self-pointing if NULL.
 * @return	A pointer to the created object.
 */
object_t *new_object(object_t *classdef);
/**
 * Set the bytecode pointer of an object.
 * @param	obj	Pointer to the object.
 * @param	code	Pointer to the bytecode section.
 */
void object_set_code(object_t *obj, void *code);
/**
 * Set the executable function of an object.
 * @param	obj	Pointer to the object.
 * @param	exec	Pointer to the executable function.
 */
void object_set_exec(object_t *obj, object_exec_t exec);
/**
 * Add a symbol to an object.
 * @param	obj	Pointer to the object.
 * @param	name	Symbol's name.
 * @param	value	Symbol's value.
 */
void object_add_symbol(object_t *obj, char *name, object_t *value);

#endif // __OBJECT_H__
