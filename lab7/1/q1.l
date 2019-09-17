%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "q1.tab.h"
%}

%%


\n {return NL;}
"int"|"char" {printf("%s ",yytext) ;return DT;}
[a-zA-Z]+ {printf("%s ",yytext) ;return ID;}
"," {printf(", ") ;return COMMA;}




%%

int yywrap()
{
	return 1;
}
