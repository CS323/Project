// .l file

%{
#include "ch302.tab.h"
extern int yylval;
%}

%%
"PROGRAM"		{return PROGRAM;
				printf("read PROGRAM");}
"BEGIN"			{return BEGIN;
				printf("read BEGIN");}
"VAR"			{return VAR;
				printf("read VAR");}
"END."			{return END.;
				printf("read END");}
"INTEGER"		{return INTEGER;
				printf("read INTEGER");}
"PRINT"			{return PRINT;
				printf("read PRINT");}
[ \t]			{ printf ("skipped whitespace\n"); }
\n				{ printf ("reached end of line\n");
				return 0;}
.				{ printf ("found other data \"%s\"\n", yytext);
				return yytext[0];
				}
%%

