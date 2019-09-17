%{
	#include<stdio.h>
	#include<stdlib.h>
	int yylex();
	int yyerror();
	extern FILE *yyin;
%}

%token INT CHAR NUMBER ID COMM SCOLON LSB RSB LC RC RP LP EQEQ NTEQ GTE LTE GT LT EQ WHILE FOR PLUS MINUS MUL DIV MOD MAIN IF ELSE

%%

program	: MAIN RP LP LC decl stmt_list RC ;

decl	: dtype idlist SCOLON decl |  ;

dtype	: INT | CHAR ;

idlist	:	ID
			|ID COMM idlist
			|ID LSB NUMBER RSB COMM idlist
			|ID LSB NUMBER RSB
			;

stmt_list	: stmt stmt_list |  ;

stmt    : assign-stat SCOLON | decision-stat | looping-stat;

assign-stat	: ID EQ expn;

expn : simple-expn eprime;

eprime	: relop simple-expn |  ;

simple-expn	: term seprime;

seprime	: addop term seprime |  ;

term	: factor tprime;

tprime	: mulop factor tprime |  ;

factor	: ID | NUMBER;

decision-stat	: IF RP expn LP LC stmt_list RC dprime;

dprime	: ELSE LC stmt_list RC |  ;

looping-stat : WHILE RP expn LP LC stmt_list RC 
			   | FOR RP assign-stat SCOLON expn SCOLON assign-stat LP LC stmt_list RC;

relop	: EQEQ | NTEQ | LTE | GTE | GT | LT;

addop	: PLUS | MINUS;

mulop	: MUL | DIV | MOD;

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
			
	printf("\n\ngrammar is accepted\n");
	
}
