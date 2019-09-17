%{
#include <stdio.h>
#include <stdlib.h>
int s,p;
FILE *in;
FILE *out;
%}

%%
"scanf" {s++;fprintf(yyout,"READ");}
"printf" {p++;fprintf(yyout,"WRITE");}
%%

main()
{
yyin=fopen("inpfile.c","r");
yyout = fopen("out1.c","r+");

yylex();
printf("No.of.scanfs:%d and No.of.printfs:%d\n",s,p);

}

int yywrap(){
return 1;
}



