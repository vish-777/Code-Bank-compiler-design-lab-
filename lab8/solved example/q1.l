
%option noyywrap nodefault yylineno
%{
#include "fun.h"
#include "cal.tab.h"
%}


EXP
([Ee][-+]?[0-9]+)
%%
"+" |
"-" |
"*" |
"/" |
"|" |
"(" |
")"
{ return yytext[0]; }
[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? { yylval.d = atof(yytext); return NUMBER; }
\n
{ return EOL; }
"//".*
[ \t] { /* ignore whitespace */ }
.
{ yyerror("Mystery character %c\n", *yytext); }
%%
