%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "cparser.tab.h"

%}


%%

"\t"|" "|"\n" {printf("%s",yytext);}

(("#".*)|("//".*))"\n" { }

("/*"(.|"\n")*"*/") { }

"int" {printf("%s",yytext);return INT;}

"char" {printf("%s",yytext);return CHAR;}


[0-9]+ {printf("%s",yytext);return NUMBER;}

"[" {printf("["); return LSB;}

"]" {printf("]"); return RSB;}

"{" {printf("{"); return LC;}

"}" {printf("}"); return RC;}

"(" {printf("("); return RP;}

")" {printf(")"); return LP;}

"," {printf(","); return COMM;}

";" {printf(";"); return SCOLON;}

"main" {printf("main"); return MAIN;}

"while" {printf("while"); return WHILE;}

"if" {printf("if"); return IF;}

"else" {printf("else"); return ELSE;}

"for" {printf("for"); return FOR;}

"=" {printf("="); return EQ;}

"==" {printf("=="); return EQEQ;}

"!=" {printf("!="); return NTEQ;}

">=" {printf(">="); return GTE;}

"<=" {printf("<="); return LTE;}

"<" {printf("<"); return LT;}

">" {printf(">"); return GT;}

"+" {printf("+"); return PLUS;}

"-" {printf("-"); return MINUS;}

"*" {printf("*"); return MUL;}

"/" {printf("/"); return DIV;}

"%" {printf("%s",yytext); return MOD;}

[a-zA-Z_][a-zA-Z0-9_]* {printf("%s",yytext); return ID;}

%%

int yywrap(){return 1;}