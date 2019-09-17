%{
	#include<stdio.h>
	#include<stdlib.h>
	int yylex();
	int yyerror();
	extern FILE *yyin;	
%}

%token NL ID NUMBER PLUS MINUS DIV MUL POW
%left '+' '-'

%%

SwitchStatement: Switch LP ID RP Switchblock;

Switchblock: LSB Switchlabel RSB;

Switchlabels:Switchlabels moreSwitchlabels | ;

moreSwitchlabels:Switchlabel moreSwitchlabels | ;

switchlabel:case
/* exp: NUMBER | exp exp PLUS | exp exp MINUS | exp exp MUL | exp exp DIV | exp exp POW | ID; */


%%

int yyerror(char *msg){
	printf("Invalid expression");
	return 1;
}

void main(){
	yyin=fopen("inpfile.c","r");
	do{
		if(yyparse()){
			printf("\nFailure\n");
			exit(0);
		}
	}while(!feof(yyin));

	printf("\nSuccess\n");
}
