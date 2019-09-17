%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "1.tab.h"

%}


%%
"int" {printf("%s",yytext);return INT;}

"char" {printf("%s",yytext);return CHAR;}

\n {return NL;}

[0-9]+ {printf("%s",yytext);return NUMBER;}

[a-zA-Z_][a-zA-Z0-9_]* {printf("%s",yytext);return ID;}

"[" {printf("["); return SOPEN;}

"]" {printf("]"); return SCLOSE;}

"," {printf(","); return COMM;}

";" {printf(";"); return SCOLON;}

%%

int yywrap(){return 1;}