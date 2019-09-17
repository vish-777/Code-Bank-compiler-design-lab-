%{
	#include<stdio.h>
	#include<stdlib.h>
	int yylex();
	int yyerror();
	extern FILE *yyin;	
%}

%token NL ID NUM PLUS MINUS DIV MUL POW SWITCH CASE BREAK LP RP LSB RSB COLON EQU
%left '+' '-'

%%

SwitchStatement: SWITCH LP ID RP Switchblock;

Switchblock: LSB Switchlabel RSB;

Switchlabels:Switchlabels moreSwitchlabels |epsilon ;

moreSwitchlabels:Switchlabel moreSwitchlabels |epsilon ;

Switchlabel:CASE NUM COLON assignstat BREAK;

assignstat: ID EQU NUM; | ID;

epsilon: ;



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
