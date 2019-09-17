%{
	#include<stdio.h>
	#include<stdlib.h>
	int yylex();
	int yyerror();
	extern FILE *yyin;
%}

%token NL INT CHAR NUMBER ID COMM SCOLON SOPEN SCLOSE
%left ',' ';' '[' ']'

%%


decl	:	dtype idlist SCOLON decl | dtype idlist SCOLON NL decl |
			;

dtype	:	INT 
			| CHAR
			;

idlist	:	ID
			|ID COMM idlist
			|ID SOPEN NUMBER SCLOSE COMM idlist
			|ID SOPEN NUMBER SCLOSE
			;

%%

int yyerror(char *msg){
	printf("\nInvalid expression");
	return 1;
}

void main (){
	yyin=fopen("inpfile.c","r");

	do{
		if(yyparse() )
		{
			printf("\n Failure");
			exit(0);
		}

	}while(!feof(yyin));
			
	printf("\n\nSuccess\n");
	
}
