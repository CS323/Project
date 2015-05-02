
//  .y file

%{
#include <stdio.h>
%}

%start start
%token PROGRAM BEGIN END INTEGER
%token PRINT
%left '-' '+'
%left '*' '/'
%nonassoc UMINUS

%%
start		:	PROGRAM pname VAR dec-list BEGIN stat-list END.
				|	//error handling, expected PROGRAM

pname		:	id

id			:	letter{letter|digit}

dec-list	:	dec : type

dec			:	id, dec | id

stat-list	:	stat; | stat; stat-list

stat		:	print | assign

print		:	PRINT (output)

output		:	{"string",} id

assign		:	id = expr

expr		:	term | expr + term | expr - term

term		:	term * factor | term / factor | factor

factor		:	id | number | ( expr )

number		:	digit{digit}

type		:	INTEGER

digit		:	0|1|2|3|4|5|6|7|8|9

letter		:	a|b|c|d|e|f




			
							expression:	expression '+' expression	{ $$ = $1 + $3;
													printf ("Recognized '+' expression.\n");
													}
								|	expression '-' expression	{ $$ = $1 - $3; 
													printf ("Recognized '-' expression.\n");
													}
								|	expression '*' expression	{ $$ = $1 * $3; 
													printf ("Recognized '*' expression.\n");
													}
								|	expression '/' expression	{ if ($3 == 0)
														yyerror ("divide by zero");
													else
														$$ = $1 / $3; 
													printf ("Recognized '/' expression.\n");
													}
								|	'-' expression %prec UMINUS	{ $$ = - $2; 
													printf ("Recognized negation.\n");
													}
								|	'(' expression ')'		{ $$ = $2;
													printf ("Recognized parenthesized expression.\n");
													}
								|	NUMBER				{ $$ = $1; 
													printf ("Recognized a number.\n");
													}
								;
%%
int main (void) {
	return yyparse();
	}

/* Added because panther doesn't have liby.a installed. */
int yyerror (char *msg) {
	return fprintf (stderr, "YACC: %s\n", msg);
	}
