%{
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#define YY_DECL struct token *yylex(void)
	enum tokenType{EOFILE=-1,LT,LTE,GT,GTE,EQ,NEQ,KEYWORD,IDENTIFIER,LOGICAL_OP,ARITHMETIC_OP,SPECIAL_SYMBOL};
	char names[100][30];
	struct token{
		char *lexeme;
		int index;
		unsigned int rowno,colno;
		enum tokenType type;
	};

	int lineno=1,colno=1;
	struct token *tk;

	struct token *allocToken(){
		struct token *tk;
		tk=(struct token *)malloc(sizeof(struct token));
		tk->lexeme=(char *)malloc(sizeof(char)*3);
		tk->index=-1;
		tk->type=EOFILE;
		return tk;
	}

	void setTokenArgs(struct token *tk,char *lexeme,int index,int rowno,int colno,enum tokenType type){
		if(tk==NULL)
			return;
		strcpy(tk->lexeme,lexeme);
		tk->index=index;
		tk->rowno=rowno;
		tk->colno=colno;
		tk->type=type;
	}
%}

%% 

("/*")(.*"\n".*)*("*/") {int i=0;
			while(yytext[i]!='\0'){
				if(yytext[i]=='\n'){
					lineno++;
					colno=1;
				}
				else
					colno++;
				i++;
			}
}

("//")(.*"\n") {lineno++;colno++;}

(\"(.)*\") {colno+=strlen(yytext);}

(\'(.)\') {colno+=strlen(yytext);}

\n {lineno++;colno=1;}

("#")(.*"\n") {lineno++;colno++;}

"<" {tk=allocToken();
	setTokenArgs(tk,yytext,-1,lineno,colno,LT);
	colno++;
	return tk;}

"<=" {tk=allocToken();
	setTokenArgs(tk,yytext,-1,lineno,colno,LTE);
	colno+=2;
	return tk;}

">" {tk=allocToken();
	setTokenArgs(tk,yytext,-1,lineno,colno,GT);
	colno++;
	return tk;}

">=" {tk=allocToken();
	setTokenArgs(tk,yytext,-1,lineno,colno,GTE);
	colno+=2;
	return tk;}

"==" {tk=allocToken();
	setTokenArgs(tk,yytext,-1,lineno,colno,EQ);
	colno++;
	return tk;}

"!=" {tk=allocToken();
	setTokenArgs(tk,yytext,-1,lineno,colno,NEQ);
	colno++;
	return tk;}

"\t" {colno+=4;}

"if"|"else"|"return"|"break"|"char"|"double" {
	tk=allocToken();
	setTokenArgs(tk,yytext,-1,lineno,colno,KEYWORD);
	colno+=strlen(yytext);
	return tk;
}

([a-zA-Z]|'_')([a-zA-Z]|[0-9]|'_')* {
	tk=allocToken();
	setTokenArgs(tk,yytext,-1,lineno,colno,IDENTIFIER);
	colno+=strlen(yytext);
	return tk;
}

"&&"|"||"|"!" {
	tk=allocToken();
	setTokenArgs(tk,yytext,-1,lineno,colno,LOGICAL_OP);
	colno+=strlen(yytext);
	return tk;
}

"+"|"-"|"/"|"*"|"%"|"++"|"--" {
	tk=allocToken();
	setTokenArgs(tk,yytext,-1,lineno,colno,ARITHMETIC_OP);
	colno+=strlen(yytext);
	return tk;
}

"{"|"}"|"("|")"|"["|"]" {
	tk=allocToken();
	setTokenArgs(tk,yytext,-1,lineno,colno,SPECIAL_SYMBOL);
	colno+=strlen(yytext);
	return tk;
}

%%

int main(int argc,char *argv[]){
	yyin=fopen("inp6.c","r");
	int cnt=0;

	for(int i=0;i<=5;i++)
		strcpy(names[i],"RELATIONAL_OP");
	strcpy(names[6],"KEYWORD");
	strcpy(names[7],"IDENTIFIER");
	strcpy(names[8],"LOGICAL_OP");	
	strcpy(names[9],"ARITHMETIC_OP");
	strcpy(names[10],"SPECIAL_SYMBOL");
	while((tk==yylex())){
		printf("< Row:%d Column:%d Type:%s Lexeme:'%s' >\n",tk->rowno,tk->colno,names[tk->type],tk->lexeme);
		cnt++;
	}
	return 0;
}

int yywrap(){return 1;}