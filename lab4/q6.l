%{
	#include<stdio.h>
	#include<string.h>
	#include<stdlib.h>
	#include "symtab.h"
	#define YY_DECL Tokenptr yylex(void)

	int l=1, c=1, scope=0, fa=0;
	char dtype[10],dtypetemp[10],args[10][10];
	Tokenptr tp;
	Tokenptr allocToken()
	{
		Tokenptr tp;
		tp = (Tokenptr)malloc(sizeof(struct Token));
		tp -> lexeme = (char*)malloc(20*sizeof(char));
		tp -> index = 0;
		tp -> type = EOFILE;
		return tp;
	}
	void setTokenArgs(Tokenptr tp, char *lexeme, int row, int col, enum tokenType type, char *dtype)
	{
		if(tp==NULL)
			return;
		strcpy(tp->lexeme, lexeme);
		tp->row = row;
		tp->col = col;
		tp->type = type;
		if(tp->type!=3)
			tp->sizeofvar=0;
		else{
			if(strcmp(dtype,"int"))
				tp->sizeofvar=4;
			else if(strcmp(dtype,"float"))
				tp->sizeofvar=4;
			else if(strcmp(dtype,"char"))
				tp->sizeofvar=1;
			else if(strcmp(dtype,"double"))
				tp->sizeofvar=8;
		}
	}
	char* getType(enum tokenType t)
	{
		switch(t)
		{
			case 0: return "LITERAL";
			case 1: return "KEYWORD";
			case 2: return "NUMBER";
			case 3: return "IDENTIFIER";
			case 4: return "SYMBOL";
			case 5: return "AOP";
			case 6: return "LOP";
			case 7: return "RELOP";
			case 8: return "FUNCTION";
			default: return "";
		}
	}
	void printToken(Tokenptr tp)
	{
		//printf("<%s, %d, %d, %d, %s>\n", tp->lexeme, tp->row, tp->col, tp->index, getType(tp->type));
	}
%}
%%
"#"(.)*"\n" {
	l++;
}
"//"(.)*"\n" {
	l++;
}
"/*"([^*]|"*"[^/])*"*/"  {
	for(int i=0; i<yyleng; i++)
		if(yytext[i]=='\n')
		{
			l++;
			c=1;
		}
}
\"[^\"]*\" {
	tp = allocToken();
	setTokenArgs(tp, yytext, l, c, LITERAL,"NA");
	c+=yyleng;
	return tp;
}
"int"|"char"|"if"|"else"|"while"|"void"|"for"|"return"|"float"|"double" {
	if(strcmp(yytext, "int")||strcmp(yytext, "char")||strcmp(yytext, "float")||strcmp(yytext, "double")||strcmp(yytext, "void"))
		strcpy(dtype, yytext);
	tp = allocToken();
	setTokenArgs(tp, yytext, l, c, KEYWORD,"NA");
	c+=yyleng;
	return tp;
}
[a-zA-Z_][a-zA-Z0-9_]* {
	tp = allocToken();
	setTokenArgs(tp, yytext, l, c, IDENTIFIER,dtype);
	Insert(tp, dtype, scope, NULL, 0);
	c+=yyleng;
	return tp;
}
[a-zA-Z_][a-zA-Z0-9_]*[ ]*"(" {
	strcpy(dtypetemp,dtype);
	tp = allocToken();
	yytext[yyleng-1] = '\0';
	long int pos = ftell(yyin);
	int i = 0;
	Tokenptr temp = allocToken();
	setTokenArgs(temp, yytext, l, c, FUNCTION,"NA");
	printToken(temp);
	c+=yyleng-1;
	setTokenArgs(tp, "(", l, c, SYMBOL,"NA");
	c++;
	fseek(yyin, -1, SEEK_CUR);
	while(strcmp(tp -> lexeme, ")")!=0)
	{
		if(tp -> type == IDENTIFIER)
		{
			strcpy(args[i], tp -> lexeme);
			i++;
		}
		printToken(tp);
		tp = yylex();
	}
	if(strlen(dtype)>0)
		Insert(temp, dtypetemp, scope, args, i);
	return tp;
}
[+|-]?[0-9]+(.[0-9]+)?(E[+|-]?[0-9]+)? {
	tp = allocToken();
	setTokenArgs(tp, yytext, l, c, NUMBER,"NA");
	c+=yyleng;
	return tp;
}
"+"|"-"|"*"|"/"|"%"|"+="|"-="|"*="|"/="|"%="|"++"|"--" {
	tp = allocToken();
	setTokenArgs(tp, yytext, l, c, AOP,"NA");
	c+=yyleng;
	return tp;
}
"&"|"|"|"&&"|"||"|"!" {
	tp = allocToken();
	setTokenArgs(tp, yytext, l, c, LOP,"NA");
	c+=yyleng;
	return tp;
}
">"|"<"|"!="|">="|"<="|"==" {
	tp = allocToken();
	setTokenArgs(tp, yytext, l, c, RELOP,"NA");
	c+=yyleng;
	return tp;
}
\t|" " {
    c++;
}
\n {
	l++;
	c=1;
}
. {
	tp = allocToken();
	setTokenArgs(tp, yytext, l, c, SYMBOL,"NA");
	if(yytext[0] == ';')
		dtype[0]='\0';
	else if(yytext[0] == '{')
		scope++;
	else if(yytext[0] == '}')
		scope--;	
	c++;
	return tp;
}
%%
int main(int argc, char **argv)
{
	yyin = fopen("inpfile.c", "r");
	Tokenptr tk;
	//printf("<Lexeme, Row, Col, Index, Type>\n");
	while(tk = yylex())
		printToken(tk);
	fclose(yyin);
	printf("\n\nTable:\n");
	Display();
	return 0;
}
int yywrap()
{
	return 1;
}
