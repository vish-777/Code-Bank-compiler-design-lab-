%{
	#include<stdio.h>
	#include<stdlib.h>
	int yylex();
	int yyerror();
	extern FILE *yyin;	
%}

%token NL ID NUMBER PLUS MINUS
%left '+' '-'

%%

stmt: exp ;

exp: exp PLUS term| exp MINUS term | term;

term: ID | NUMBER;

%%

int yyerror(char *msg){
	printf("Invalid expression");
	return 1;
}

void main(){
	printf("enter the expression:\n");
	yyin=fopen("inpfile.c","r");
	do{
		if(yyparse()){
			printf("\nFailure\n");
			exit(0);
		}
	}while(!feof(yyin));

	printf("\nSuccess\n");
}
