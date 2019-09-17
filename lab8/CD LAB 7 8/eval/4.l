%{
	#include<stdio.h>
	#include<stdlib.h>
	#include"4.tab.h"
%}

%%

[0-9]+ {printf("%s",yytext);return NUM;}
\n {return NL;}
[a-zA-Z]+ {printf("%s",yytext);return ID;}
"Switch" { return SWITCH;}
"case" {return CASE;}
"break" {return BREAK;}
"=" {printf("=");return EQU;}
":" {printf(":");return COLON;}
"+" {printf("+");return PLUS;}
"[" {printf("["); return SOPEN;}
"]" {printf("]"); return SCLOSE;}
"(" {printf("("); return LP;}
")" {printf(")"); return RP;}
"{" {printf("{"); return LSB;}
"}" {printf("}"); return RSB;}
"-" {printf("-");return MINUS;}
"/" {printf("/");return DIV;}
"*" {printf("*");return MUL;}
"^" {printf("^");return POW;}

%%

int yywrap(){return 1;}
