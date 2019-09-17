%{
	#include<string.h>
	int words=0,chars=0,blanks=0,lines=1;
%}

%% 

[a-zA-Z]+ {words++;chars+=strlen(yytext);}
[' '] {blanks++;chars++;}
\n {lines++;}
. {chars++;}

%%

main(int argc,char **argv){
	yyin=fopen("inpfile.c","r");
	yylex();	
	printf("\n\nWords:%d Characters:%d Blanks:%d Lines:%d\n",words,chars,blanks,lines);
	return 0;
}

int yywrap(){return 1;}



