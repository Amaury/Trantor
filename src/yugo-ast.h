#ifndef __YUGO_AST_H__
#define __YUGO_AST_H__

#include <stdbool.h>
#include "utils/stack.h"
#include "utils/label.h"

// node types
typedef enum {
	N_BOOLEAN,
	N_NUMBER,
	N_STRING,
	N_LABEL,
	N_STATEMENT,
	N_EXPRESSION,
	N_IDENTIFIER,
	N_ASSIGNMENT,
	N_OPERATION,
	N_COMPARISON,
	N_CONDITION,
	N_WHILE,
	N_FUNC_DEF,
	N_FUNC_CALL,
	N_CLASS,
	N_RETURN,
	N_BREAK,
	N_CONTINUE,
	N_METH_CALL
} node_type_t;

// default node type
typedef struct {
	node_type_t type;
} node_t;
// statement node
typedef struct {
	node_t node;
} node_statement_t;
// expression node
typedef struct {
	node_statement_t node;
} node_expression_t;
// identifier node
typedef struct {
	node_expression_t node;
	char *name;
} node_identifier_t;
// assignment node
typedef struct {
	node_expression_t node;
	node_identifier_t *identifier;
	node_expression_t *expression;
} node_assignment_t;
// operation node
typedef struct {
	node_expression_t node;
	node_expression_t *op1;
	char operator;
	node_expression_t *op2;
} node_operation_t;
// comparison node
typedef struct {
	node_expression_t node;
	node_expression_t *op1;
	char bool_operator;
	node_expression_t *op2;
} node_comparison_t;
// condition node
typedef struct {
	node_statement_t node;
	node_expression_t *condition_expression;
	stack_t *true_statements;
	stack_t *false_statements;
} node_condition_t;
// while node
typedef struct {
	node_statement_t node;
	node_expression_t *loop_expression;
	stack_t *statements;
} node_while_t;
// function call node
typedef struct {
	node_expression_t node;
	node_identifier_t *identifier;
	stack_t *parameters;
} node_funccall_t;
// method call node
typedef struct {
	node_expression_t node;
	node_identifier_t *objname;
	node_identifier_t *methname;
	stack_t *parameters;
} node_methcall_t;
// function definition node
typedef struct {
	node_expression_t node;
	stack_t *parameters;
	stack_t *statements;
} node_funcdef_t;
// class definition node
typedef struct {
	node_expression_t node;
	stack_t *statements;
} node_class_t;
// return statement
typedef struct {
	node_statement_t node;
	node_expression_t *value;
} node_return_t;
// break statement
typedef struct {
	node_statement_t node;
} node_break_t;
// continue statement
typedef struct {
	node_statement_t node;
} node_continue_t;
// scalar node
typedef struct {
	node_expression_t node;
	union {
		char *str;
		label_t *label;
		bool boolean;
		long double number;
	} value;
} node_scalar_t;

/* ****** METHODS ********* */
void print_n(void *node);
void print_node(node_t *node, int offset);
void print_stack(stack_t *stack, int offset);
node_t *new_node(node_type_t type);
node_statement_t *new_node_statement(void);
node_expression_t *new_node_expression(void);
node_identifier_t *new_node_identifier(char *name);
node_assignment_t *new_node_assignment(node_identifier_t *identifier, node_expression_t *expression);
node_operation_t *new_node_operation(node_expression_t *op1, char operator, node_expression_t *op2);
node_comparison_t *new_node_comparison(node_expression_t *op1, char bool_operator, node_expression_t *op2);
node_condition_t *new_node_condition(node_expression_t *condition_expression, stack_t *true_statements, stack_t *false_statements);
node_while_t *new_node_while(node_expression_t *loop_expression, stack_t *statements);
node_funccall_t *new_node_funccall(node_identifier_t *identifier, stack_t *parameters);
node_methcall_t *new_node_methcall(node_identifier_t *objname, node_identifier_t *methname, stack_t *parameters);
node_funcdef_t *new_node_funcdef(stack_t *parameters, stack_t *statements);
node_class_t *new_node_class(stack_t *statements);
node_return_t *new_node_return(node_expression_t *value);
node_break_t *new_node_break(void);
node_continue_t *new_node_continue(void);
node_scalar_t *new_node_string(char *str);
node_scalar_t *new_node_boolean(bool boolean);
node_scalar_t *new_node_number(long double number);

#endif // __YUGO_AST_H__
