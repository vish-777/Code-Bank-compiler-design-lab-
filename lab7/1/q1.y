%{
	#include<stdio.h>
	#include<stdlib.h>

	int yylex();
	int yyerror();
	extern FILE *yyin;
%}

%token NL DT ID COMMA


%%

decl:DT idlist
	 ;

idlist:ID COMMA idlist|ID
	  ;


%%
int yyerror(char *msg)
{
	printf("Invalid Expression\n");
	return 1;
}

void main()
{
	yyin=fopen("int.txt","r");

	do{

		if(yyparse())
		{
			printf("\nFailure");
			exit(0);
		}
	}while(!feof(yyin));
	printf("success");
}
