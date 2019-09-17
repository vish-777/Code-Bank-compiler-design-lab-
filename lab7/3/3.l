%{
	#include<stdio.h>
	#include<stdlib.h>
	#include"3.tab.h"
%}

%%

[0-9]+ {printf("%s",yytext);return NUMBER;}
\n {return NL;}
[a-zA-Z]+ {printf("%s",yytext);return ID;}
"+" {printf("+");return PLUS;}
"-" {printf("-");return MINUS;}
"*" {printf("*");return MUL;}
"/" {printf("/");return DIV;}

%%

int yywrap(){return 1;}
