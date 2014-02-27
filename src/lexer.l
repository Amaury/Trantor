%{
/* **************************** INITIALISATIONS ********************* */
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#include "utils.h"
#include "stack.h"
#include "hashmap.h"
#include "grammar.tab.h"

extern int yywrap();
%}
/* *************************** OPTIONS ***************************** */
/* option needed to get the parsed line number in Yacc */
%option yylineno
/* definition of the state used to handle multiline comments */
%s IN_COMMENT

%%
 /* ************************* RULES ************************* */
 /* main rules */
<INITIAL>{
"/*"			BEGIN(IN_COMMENT);
\/\/.*$			;

\"(\\.|[^\\"])*\"	{ yylval.str = tstrdup(yytext + 1, yyleng - 2); return T_STRING; }
[ \t\r\n]		;
[0-9]+\.?[0-9]*		{ yylval.number = strtold(yytext, NULL); return T_NUMBER; }
0x[a-fA-F0-9]+		{ yylval.number = strtold(yytext, NULL); return T_NUMBER; }

"null"			{ return T_NULL; }
"true"			{ yylval.boolean = true; return T_BOOL; }
"false"			{ yylval.boolean = false; return T_BOOL; }

"class"			{ return (yylval.token = T_CLASS); }
"extends"		{ return (yylval.token = T_EXTENDS); }
"final"			{ return (yylval.token = T_FINAL); }
"function"		{ return (yylval.token = T_FUNCTION); }
"if"			{ return (yylval.token = T_IF); }
"else"			{ return (yylval.token = T_ELSE); }
"while"			{ return (yylval.token = T_WHILE); }
"foreach"		{ return (yylval.token = T_FOREACH); }
"new"			{ return (yylval.token = T_NEW); }
"return"		{ return (yylval.token = T_RETURN); }
"break"			{ return (yylval.token = T_BREAK); }
"continue"		{ return (yylval.token = T_CONTINUE); }

[a-zA-Z_][a-zA-Z0-9_]*	{ yylval.str = tstrdup(yytext, yyleng); return T_IDENTIFIER; }

"+"|"-"|"*"|"/"|"%"	{ return (yylval.token = yytext[0]); }
"{"|"}"|"("|")"|"="	{ return (yylval.token = yytext[0]); }
"."|","|";"		{ return (yylval.token = yytext[0]); }
":="			{ return (yylval.token = T_CLONE); }
"=="			{ return (yylval.token = T_EQUAL); }
"==="			{ return (yylval.token = T_IDENTICAL); }
"!="			{ return (yylval.token = T_NEQUAL); }
"!=="			{ return (yylval.token = T_NIDENTICAL); }
"<"|">"			{ return (yylval.token = yytext[0]); }
"<="			{ return (yylval.token = T_LESSEQ); }
">="			{ return (yylval.token = T_GREATEREQ); }
"&&"			{ return (yylval.token = T_AND); }
"||"			{ return (yylval.token = T_OR); }
}

 /* management of multiline comments */
<IN_COMMENT>{
"*/"		BEGIN(INITIAL);
.|\n		;
}

%%
