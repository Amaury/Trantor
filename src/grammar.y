%{
	#include <stdio.h>
	#include <stdint.h>
	#include <stdbool.h>
	#include "utils/utils.h"
	#include "utils/stack.h"
	#include "utils/hashmap.h"
	#include "utils/label.h"
	#include "ast.h"

	/* declarations */
	extern int yylineno;
	extern int yylex();
	void yyerror(const char *s);

	/* Error display function. */
	void yyerror(const char *s) {
		printf("PARSE ERROR (l. %d): %s.\n", yylineno, s);
	}
	/* root stack of statements */
	stack_t *root_statements;
%}

/* ask for verbose error descriptions */
%error-verbose

/* definition of the YYSTYPE union */
%union {
	bool boolean;
	long double number;
	label_t *label;
	char *str;
	uint16_t token;
	node_statement_t *statement;
	node_expression_t *expression;
	node_identifier_t *identifier;
	stack_t *stack;
};

/* list of tokens (terminal symbols), with their types in the YYSTYPE union */
%token T_NULL
%token <str> T_IDENTIFIER T_STRING
%token <label> T_LABEL
%token <number> T_NUMBER
%token <boolean> T_BOOL
%token <token> '{' '}' '(' ')' '.' ',' '+' '-' '*' '/' '%' '~' '=' ';' '<' '>'
%token <token> T_CLONE T_EQUAL T_IDENTICAL T_NEQUAL T_NIDENTICAL T_GREATEREQ T_LESSEQ
%token <token> T_CLASS T_EXTENDS T_FINAL T_IF T_ELSE T_FOREACH T_FUNCTION T_NEW T_WHILE
%token <token> T_RETURN T_BREAK T_CONTINUE T_PRINT T_AND T_OR

/* types of non-terminal symbols */
%type <token> operator bool_operator
%type <identifier> identifier
%type <expression> expression scalar assignment cloning operation comparison
%type <expression> function_call method_call function_def class print
%type <statement> statement condition while
%type <stack> statements block call_parameters def_parameters root

/* operators priority */
%left	'+' '-'
%left	'*' '/' '%'

%start	root

%%

root
	: /* empty */			{ printf("~ root - empty\n"); }
	| statements			{ root_statements = $1; }
	;

block
	: '{' '}'			{ $$ = NULL; }
	| '{' statements '}'		{ $$ = $2; }
	| statement			{ $$ = new_stack(); stack_add($$, $1); }
	;

statements
	: statements statement	{ stack_add($1, $2); }
	| statement			{ $$ = new_stack(); stack_add($$, $1); }
	;

statement
	: expression ';'		{ $$ = (node_statement_t*)$1; }
	| T_RETURN ';'			{ $$ = (node_statement_t*)new_node_return(NULL); }
	| T_RETURN expression ';'	{ $$ = (node_statement_t*)new_node_return($2); }
	| T_BREAK ';'			{ $$ = (node_statement_t*)new_node_break(); }
	| T_CONTINUE ';'		{ $$ = (node_statement_t*)new_node_continue(); }
	| condition
	| while
	;

expression
	: '(' expression ')'	{ $$ = $2; }
	| scalar
	| identifier		{ $$ = (node_expression_t*)$1; }
	| operation
	| comparison
	| assignment
	| cloning
	| print
	| function_def
	| function_call
	| method_call
	| class
	;

// condition
condition
	: T_IF '(' expression ')' block			{ $$ = (node_statement_t*)new_node_condition($3, $5, NULL); }
	| T_IF '(' expression ')' block T_ELSE block	{ $$ = (node_statement_t*)new_node_condition($3, $5, $7); }
	;

// while loop
while
	: T_WHILE '(' expression ')' block	{ $$ = (node_statement_t*)new_node_while($3, $5); }
	;

// scalar values
scalar
	: T_NULL				{ $$ = NULL; /*$$ = (node_expression_t*)new_node_null();*/ }
	| T_BOOL				{ $$ = (node_expression_t*)new_node_boolean($1 ? true : false); }
	| T_NUMBER				{ $$ = (node_expression_t*)new_node_number($1); }
	| T_STRING				{ $$ = (node_expression_t*)new_node_string($1); }
	| T_LABEL				{ $$ = (node_expression_t*)new_node_label($1); }
	;

// mathematical operation
operation
	: expression operator expression		{ $$ = (node_expression_t*)new_node_operation($1, $2, $3); }
	;

operator: '+' | '-' | '*' | '/' | '%' | '~';

// comparison
comparison
	: expression bool_operator expression	{ $$ = (node_expression_t*)new_node_comparison($1, $2, $3); }
	;

bool_operator: T_EQUAL | T_IDENTICAL | T_NEQUAL | T_NIDENTICAL | '<' | '>' | T_LESSEQ | T_GREATEREQ;

// variable assignment and cloning
assignment
	: identifier '=' expression		{ $$ = (node_expression_t*)new_node_assignment($1, $3); }
	;

cloning
	: identifier T_CLONE identifier		{ }
	;

// identifier
identifier
	: T_IDENTIFIER				{ $$ = new_node_identifier($1); }
	;

// function call
function_call
	: identifier '(' ')'			{ $$ = (node_expression_t*)new_node_funccall($1, NULL); }
	| identifier '(' call_parameters ')'	{ $$ = (node_expression_t*)new_node_funccall($1, $3); }
	;

call_parameters
	: call_parameters ',' expression	{ stack_add($1, $3); }
	| expression				{ $$ = new_stack(); stack_add($$, $1); }
	;

// method call
method_call
	: identifier '.' identifier '(' ')'			{ $$ = (node_expression_t*)new_node_methcall($1, $3, NULL); }
	| identifier '.' identifier '(' call_parameters ')'	{ $$ = (node_expression_t*)new_node_methcall($1, $3, $5); }
	;

// function definition
function_def
	: T_FUNCTION '(' ')' block			{ $$ = (node_expression_t*)new_node_funcdef(NULL, $4); }
	| T_FUNCTION '(' def_parameters ')' block	{ $$ = (node_expression_t*)new_node_funcdef($3, $5); }
	;

def_parameters
	: def_parameters ',' identifier		{ stack_add($1, $3); }
	| identifier				{ $$ = new_stack(); stack_add($$, $1); }
	;

// class definition
class
	: T_CLASS block	{ $$ = (node_expression_t*)new_node_class($2); }
	;

// print
print
	: T_PRINT '(' expression ')'	{ $$ = (node_expression_t*)new_node_print($3); }
	;

%%
