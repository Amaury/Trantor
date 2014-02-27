#include <stdio.h>
#include <stdint.h>
#include "node.h"
#include "utils.h"
#include "grammar.tab.h"

static void _print_offset(int offset);
static void _print_offset(int offset) {
	int i;

	for (i = 0; i < offset; ++i)
		printf("\t");
}
void print_stack(stack_t *stack, int offset) {
	size_t n;

	if (!stack)
		return;
	for (n = 0; n < stack->count; ++n)
		print_node(stack->buckets[n], offset);
}

// recursively print node content
void print_n(void *node) {
	print_node(node, 0);
}
// print node content with a given tabulation order
void print_node(node_t *node, int offset) {
	_print_offset(offset);
	if (!node) {
		printf("> NULL\n");
	} else if (node->type == N_BOOLEAN) {
		node_scalar_t *scalar = (node_scalar_t*)node;
		printf("> BOOL (%s)\n", scalar->value.boolean ? "true" : "false");
	} else if (node->type == N_NUMBER) {
		node_scalar_t *scalar = (node_scalar_t*)node;
		printf("> NUMBER (%Lf)\n", scalar->value.number);
	} else if (node->type == N_STRING) {
		node_scalar_t *scalar = (node_scalar_t*)node;
		printf("> STRING (%s)\n", scalar->value.str);
	} else if (node->type == N_ASSIGNMENT) {
		node_assignment_t *assign = (node_assignment_t*)node;
		printf("> ASSIGNMENT\n");
		_print_offset(offset + 1);
		printf("IDENTIFIER\n");
		print_node((node_t*)assign->identifier, offset + 2);
		_print_offset(offset + 1);
		printf("EXPRESSION\n");
		print_node((node_t*)assign->expression, offset + 2);
	} else if (node->type == N_OPERATION) {
		node_operation_t *ope = (node_operation_t*)node;
		printf("> OPERATION\n");
		_print_offset(offset + 1);
		printf("OP 1\n");
		print_node((node_t*)ope->op1, offset + 2);
		_print_offset(offset + 1);
		printf("OPERATOR: '%c'\n", ope->operator);
		_print_offset(offset + 1);
		printf("OP 2\n");
		print_node((node_t*)ope->op2, offset + 2);
	} else if (node->type == N_CONDITION) {
		node_condition_t *cond = (node_condition_t*)node;
		printf("> CONDITION\n");
		_print_offset(offset + 1);
		printf("EXPRESSION\n");
		print_node((node_t*)cond->condition_expression, offset + 2);
		_print_offset(offset + 1);
		printf("TRUE INSTRUCTIONS\n");
		print_stack(cond->true_instructions, offset + 2);
		if (cond->false_instructions) {
			_print_offset(offset + 1);
			printf("FALSE INSTRUCTIONS\n");
			print_stack(cond->false_instructions, offset + 2);
		}
	} else if (node->type == N_WHILE) {
		node_while_t *loop = (node_while_t*)node;
		printf("> WHILE\n");
		_print_offset(offset + 1);
		printf("EXPRESSION\n");
		print_node((node_t*)loop->loop_expression, offset + 2);
		_print_offset(offset + 1);
		printf("INSTRUCTIONS\n");
		print_stack(loop->instructions, offset + 2);
	} else if (node->type == N_FUNC_CALL) {
		node_funccall_t *call = (node_funccall_t*)node;
		printf("> FUNCTION CALL\n");
		_print_offset(offset + 1);
		printf("IDENTIFIER\n");
		print_node((node_t*)call->identifier, offset + 2);
		_print_offset(offset + 1);
		if (!call->parameters)
			printf("NO PARAMETER\n");
		else {
			printf("PARAMETERS\n");
			print_stack(call->parameters, offset + 2);
		}
	} else if (node->type == N_METH_CALL) {
		node_methcall_t *call = (node_methcall_t*)node;
		printf("> METHOD CALL\n");
		_print_offset(offset + 1);
		printf("OBJECT NAME\n");
		print_node((node_t*)call->objname, offset + 2);
		_print_offset(offset + 1);
		printf("METHOD NAME\n");
		print_node((node_t*)call->methname, offset + 2);
		_print_offset(offset + 1);
		if (!call->parameters)
			printf("NO PARAMETER\n");
		else {
			printf("PARAMETERS\n");
			print_stack(call->parameters, offset + 2);
		}
	} else if (node->type == N_FUNC_DEF) {
		node_funcdef_t *def = (node_funcdef_t*)node;
		printf("> FUNCTION DEF\n");
		_print_offset(offset + 1);
		if (!def->parameters)
			printf("NO PARAMETER\n");
		else {
			printf("PARAMETERS\n");
			print_stack(def->parameters, offset + 2);
		}
		_print_offset(offset + 1);
		printf("INSTRUCTIONS\n");
		print_stack(def->instructions, offset + 2);
	} else if (node->type == N_CLASS) {
		node_class_t *classdef = (node_class_t*)node;
		printf("> CLASS DEF\n");
		_print_offset(offset + 1);
		printf("INSTRUCTIONS\n");
		print_stack(classdef->instructions, offset + 2);
	} else if (node->type == N_IDENTIFIER) {
		node_identifier_t *ident = (node_identifier_t*)node;
		printf("> IDENTIFIER (%s)\n", ident->name);
	} else if (node->type == N_RETURN) {
		node_return_t *ret = (node_return_t*)node;
		if (!ret->value)
			printf("> RETURN (NULL)\n");
		else {
			printf("> RETURN\n");
			_print_offset(offset + 1);
			printf("VALUE\n");
			print_node((node_t*)ret->value, offset + 2);
		}
	} else if (node->type == N_BREAK) {
		printf("> BREAK\n");
	} else if (node->type == N_CONTINUE) {
		printf("> CONTINUE\n");
	} else {
		printf("!! UNKNOWN TYPE\n");
	}
}

node_t *new_node(node_type_t type) {
	node_t *node = tmalloc(sizeof(node_t));
	printf("+ new node\n");
	node->type = type;
	return (node);
}

node_instruction_t *new_node_instruction() {
	node_instruction_t *node = tmalloc(sizeof(node_instruction_t));
	printf("+ new instruction\n");
	((node_t*)node)->type = N_INSTRUCTION;
	return (node);
}

node_expression_t *new_node_expression() {
	node_expression_t *node = tmalloc(sizeof(node_expression_t));
	printf("+ new expression\n");
	((node_t*)node)->type = N_EXPRESSION;
	return (node);
}

node_identifier_t *new_node_identifier(char *name) {
	node_identifier_t *node = tmalloc(sizeof(node_identifier_t));
	printf("+ new identifier (%s)\n", name);
	((node_t*)node)->type = N_IDENTIFIER;
	node->name = name;
	return (node);
}

node_assignment_t *new_node_assignment(node_identifier_t *identifier, node_expression_t *expression) {
	node_assignment_t *node = tmalloc(sizeof(node_assignment_t));
	printf("+ new assignment\n");
	((node_t*)node)->type = N_ASSIGNMENT;
	node->identifier = identifier;
	node->expression = expression;
	return (node);
}

node_operation_t *new_node_operation(node_expression_t *op1, char operator, node_expression_t *op2) {
	node_operation_t *node = tmalloc(sizeof(node_operation_t));
	printf("+ new operation\n");
	((node_t*)node)->type = N_OPERATION;
	node->op1 = op1;
	node->operator = operator;
	node->op2 = op2;
	return (node);
}

node_comparison_t *new_node_comparison(node_expression_t *op1, char bool_operator, node_expression_t *op2) {
	node_comparison_t *node = tmalloc(sizeof(node_comparison_t));
	printf(" + new comparison\n");
	((node_t*)node)->type = N_COMPARISON;
	node->op1 = op1;
	node->bool_operator = bool_operator;
	node->op2 = op2;
	return (node);
}

node_condition_t *new_node_condition(node_expression_t *condition_expression, stack_t *true_instructions, stack_t *false_instructions) {
	node_condition_t *node = tmalloc(sizeof(node_condition_t));
	printf("+ new condition\n");
	((node_t*)node)->type = N_CONDITION;
	node->condition_expression = condition_expression;
	node->true_instructions = true_instructions;
	node->false_instructions = false_instructions;
	return (node);
}

node_while_t *new_node_while(node_expression_t *loop_expression, stack_t *instructions) {
	node_while_t *node = tmalloc(sizeof(node_while_t));
	printf("+ new while\n");
	((node_t*)node)->type = N_WHILE;
	node->loop_expression = loop_expression;
	node->instructions = instructions;
	return (node);
}

node_funccall_t *new_node_funccall(node_identifier_t *identifier, stack_t *parameters) {
	node_funccall_t *node = tmalloc(sizeof(node_funccall_t));
	printf("+ new funccall\n");
	((node_t*)node)->type = N_FUNC_CALL;
	node->identifier = identifier;
	node->parameters = parameters;
	return (node);
}

node_methcall_t *new_node_methcall(node_identifier_t *objname, node_identifier_t *methname, stack_t *parameters) {
	node_methcall_t *node = tmalloc(sizeof(node_methcall_t));
	printf("+ new methcall\n");
	((node_t*)node)->type = N_METH_CALL;
	node->objname = objname;
	node->methname = methname;
	node->parameters = parameters;
	return (node);
}

node_funcdef_t *new_node_funcdef(stack_t *parameters, stack_t *instructions) {
	node_funcdef_t *node = tmalloc(sizeof(node_funcdef_t));
	printf("+ new funcdef\n");
	((node_t*)node)->type = N_FUNC_DEF;
	node->parameters = parameters;
	node->instructions = instructions;
	return (node);
}

node_class_t *new_node_class(stack_t *instructions) {
	node_class_t *node = tmalloc(sizeof(node_class_t));
	printf("+ new class\n");
	((node_t*)node)->type = N_CLASS;
	node->instructions = instructions;
	return (node);
}

node_return_t *new_node_return(node_expression_t *value) {
	node_return_t *node = tmalloc(sizeof(node_return_t));
	printf("+ new return\n");
	((node_t*)node)->type = N_RETURN;
	node->value = value;
	return (node);
}

node_break_t *new_node_break() {
	node_break_t *node = tmalloc(sizeof(node_return_t));
	printf("+ new break\n");
	((node_t*)node)->type = N_BREAK;
	return (node);
}

node_continue_t *new_node_continue() {
	node_continue_t *node = tmalloc(sizeof(node_continue_t));
	printf("+ new continue\n");
	((node_t*)node)->type = N_CONTINUE;
	return (node);
}

node_scalar_t *new_node_string(char *str) {
	node_scalar_t *node = tmalloc(sizeof(node_scalar_t));
	printf("+ new string (%s)\n", str);
	((node_t*)node)->type = N_STRING;
	node->value.str = str;
	return (node);
}

node_scalar_t *new_node_boolean(bool boolean) {
	node_scalar_t *node = tmalloc(sizeof(node_scalar_t));
	printf("+ new boolean (%s)\n", boolean ? "true" : "false");
	((node_t*)node)->type = N_BOOLEAN;
	node->value.boolean = boolean;
	return (node);
}

node_scalar_t *new_node_number(long double number) {
	node_scalar_t *node = tmalloc(sizeof(node_scalar_t));
	printf("+ new number (%Lf)\n", number);
	((node_t*)node)->type = N_NUMBER;
	node->value.number = number;
	return (node);
}
