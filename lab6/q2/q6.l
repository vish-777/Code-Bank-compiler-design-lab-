%{
#include <stdio.h>
#include "q1.c"
#define YY_DECL token* yylex(void)

int rownum=1;
int colnum=1;
token* tk;
token* alloctoken()
{
	token* t;
	t=(token*)malloc(sizeof(token));
	t->lexemename=malloc(50);
	t->index=0;
	t->row=0;
	t->col=0;
	t->type=EOFFile;
	return t;
}

void setTokenargs(token* tk,char* lexemename,int index,int row,int col,enum Tokentype type)
{
	if(tk==NULL)
	{
		return;
	}
	strcpy(tk->lexemename,lexemename);
	tk->index=index;
	tk->row=row;
	tk->col=col;
	tk->type=type;
}
%}

%%
"/*"[.|\n]*"*/" {
	int i=0;
	while(yytext[i]!='\0')
	{
		if(yytext[i]=='\n')
		{
			rownum++;
			colnum=1;
		}else
		{
			colnum++;
		}
		i++;
	}
}

"//".*"\n" {
	rownum++;
	colnum=1;
}
"("|")"|"{"|"}"|"["|"]" {
	tk=alloctoken();
	if(strcmp(yytext,"(")==0)
	{
	setTokenargs(tk,yytext,0,rownum,colnum,LB);
	}
	else if(strcmp(yytext,")")==0)
	{
	setTokenargs(tk,yytext,0,rownum,colnum,RB);
	}else if(strcmp(yytext,"{")==0)
	{
	setTokenargs(tk,yytext,0,rownum,colnum,LCB);
	}else if(strcmp(yytext,"}")==0)
	{
	setTokenargs(tk,yytext,0,rownum,colnum,RCB);
	}else if(strcmp(yytext,"[")==0)
	{
	setTokenargs(tk,yytext,0,rownum,colnum,LSB);
	}else if(strcmp(yytext,"]")==0)
	{
	setTokenargs(tk,yytext,0,rownum,colnum,LSB);
	}
	colnum+=1;
	return tk;	
}
^#.*\n {
	rownum++;
	colnum=1;
}
\"(.)*\" {

	tk=alloctoken();
	setTokenargs(tk,yytext,0,rownum,colnum,LITERAL);
	colnum+=strlen(yytext);
	return tk;
}
\n {
	rownum++;
	colnum=1;
}
"<" {
		tk=alloctoken();
		setTokenargs(tk,yytext,0,rownum,colnum,LT);
		colnum++;
		return tk;

}


">" {
		tk=alloctoken();
		setTokenargs(tk,yytext,0,rownum,colnum,GT);
		colnum++;
		return tk;

}

"&" {
		tk=alloctoken();
		setTokenargs(tk,yytext,0,rownum,colnum,ADDRESS);
		colnum++;
		return tk;

}

"<=" {
	tk=alloctoken();
	setTokenargs(tk,yytext,0,rownum,colnum,LTE);
	colnum+=2;
	return tk;
}

">=" {
	tk=alloctoken();
	setTokenargs(tk,yytext,0,rownum,colnum,GTE);
	colnum+=2;
	return tk;	
}

"==" {
	tk=alloctoken();
	setTokenargs(tk,yytext,0,rownum,colnum,EE);
	colnum+=2;
	return tk;
}

"!=" {
	tk=alloctoken();
	setTokenargs(tk,yytext,0,rownum,colnum,NE);
	colnum+=2;
	return tk;
}

\t {
	colnum+=8;
}

"++"|"--" {
	tk=alloctoken();
	setTokenargs(tk,yytext,0,rownum,colnum,AOP);
	colnum+=2;
	return tk;
}

\+ {
	tk=alloctoken();
	setTokenargs(tk,yytext,0,rownum,colnum,ADD);
	colnum++;
	return tk;
}

\- {
	tk=alloctoken();
	setTokenargs(tk,yytext,0,rownum,colnum,SUB);
	colnum++;
	return tk;
}

\* {
	tk=alloctoken();
	setTokenargs(tk,yytext,0,rownum,colnum,MUL);
	colnum++;
	return tk;
}
\/ {
	tk=alloctoken();
	setTokenargs(tk,yytext,0,rownum,colnum,DIV);
	colnum++;
	return tk;
}

\% {
	tk=alloctoken();
	setTokenargs(tk,yytext,0,rownum,colnum,MODULUS);
	colnum++;
	return tk;
}

\= {
	tk=alloctoken();
	setTokenargs(tk,yytext,0,rownum,colnum,ASSIGN);
	colnum++;
	return tk;
}

[\;,\,] {
	tk=alloctoken();
	setTokenargs(tk,yytext,0,rownum,colnum,SS);
	colnum++;
	return tk;
}

"if"|"else"|"for"|"while"|"int"(\*)?|"char"(\*)?|"do"|"return"|"void"|"float"(\*)|"double"(\*)?|return {
	tk=alloctoken();
	setTokenargs(tk,yytext,0,rownum,colnum,KEYWORD);
	colnum+=strlen(yytext);
	return tk;	
}
[-]?[0-9]+([.]?[0-9]+)? {
	tk=alloctoken();
	setTokenargs(tk,yytext,0,rownum,colnum,NUMBER);
	colnum+=strlen(yytext);
	return tk;
}
[a-zA-Z][a-zA-Z0-9_]* {
	tk=alloctoken();
	setTokenargs(tk,yytext,0,rownum,colnum,IDENTIFIER);
	colnum+=strlen(yytext);
	return tk;
}


"&&"|"||" {
	tk=alloctoken();
	setTokenargs(tk,yytext,0,rownum,colnum,LOP);
	colnum+=2;
	return tk;
}

"$" {
	tk=alloctoken();
	setTokenargs(tk,yytext,0,rownum,colnum,dollar);
	colnum+=1;
	return tk;	
}

.
{
	colnum++;
}


%%

int main(int argc,char* argv[])
{
	init(table);
	char* datatypebuffer=malloc(50);
	int datatypebufferfull=0;
	token* identifierbuffer[50];
	int identifierbuffercnt=0;
	token* argumentbuffer[50];
	int argumentbuffercnt=0;
	int argumentbufferactivate=0;
	int keywordprev=0;
	int argumentbuffersize[50];
	char returntypebuffer[50];
	char argdtype[50][10];
	char identifierdtype[50][10];
	int identifiersize[50];
	int arrayactivate=0;
	yyin=fopen("test.c","r");
	int cnt=0;
	int scope=0;
	int index=0;
	while(tk==yylex())
	{
		printf("<%d %d %d %s %s>\n",tk->index,tk->row,tk->col,tk->lexemename,Tokentypestr[tk->type]);
		
		if( strcmp(tk->lexemename,"int")==0||strcmp(tk->lexemename,"float")==0||strcmp(tk->lexemename,"char")==0||strcmp(tk->lexemename,"double")==0||strcmp(tk->lexemename,"int*")==0||strcmp(tk->lexemename,"float*")==0||strcmp(tk->lexemename,"char*")==0||strcmp(tk->lexemename,"double*")==0)
		{
			if(!argumentbufferactivate)
				strcpy(returntypebuffer,tk->lexemename);
			datatypebufferfull = 1;
			strcpy(datatypebuffer,tk->lexemename);

		}else if(strcmp(tk->lexemename,";")==0 && datatypebufferfull==1)
		{
			printf("helloins%d\n",identifierbuffercnt);
			for (int i=0;i<identifierbuffercnt;i++)
			{
				
				printf("%s\n",identifierbuffer[i]->lexemename);
				insert(identifierbuffer[i],identifiersize[i],identifierdtype[i],scope,NULL,0,NULL,table,0);
			}
			identifierbuffercnt=0;
			datatypebufferfull=0;
			
		}else if(keywordprev==0 && strcmp(tk->lexemename,"(")==0)
		{
			argumentbufferactivate=1;
		}else if(strcmp(tk->lexemename,")")==0)
		{	
			
			if(keywordprev==0)
			{
				if (argumentbuffercnt>0)
				{
				for(int i=0;i<argumentbuffercnt;i++)
				{	printf("%s\n",argumentbuffer[i]->lexemename);
					insert(argumentbuffer[i],argumentbuffersize[i],argdtype[i],1,NULL,0,NULL,table,1);	
				}
				insert(identifierbuffer[0],-1,NULL,scope,argumentbuffer,argumentbuffercnt,returntypebuffer,table,0);
				}

				
				argumentbuffercnt=0;
				identifierbuffercnt=0;
				datatypebufferfull=0;
				
			}
			argumentbufferactivate=0;
			keywordprev=0;
		}else if(tk->type==IDENTIFIER)
		{
			printf("%d %d\n",datatypebufferfull,argumentbufferactivate);
			if(datatypebufferfull && argumentbufferactivate==0)
			{

				identifierbuffer[identifierbuffercnt] = tk;
				strcpy(identifierdtype[identifierbuffercnt],datatypebuffer);
				int size=4;
				if(strcmp(datatypebuffer,"int")==0)
				{
					size=4;
				}
				else if(strcmp(datatypebuffer,"float")==0)
				{
					size=8;
				}else if (strcmp(datatypebuffer,"char")==0)
				{
					size=1;
				}else if (strcmp(datatypebuffer,"double")==0)
				{
					size=16;
				}
				identifiersize[identifierbuffercnt++]=size;
 			}else if(datatypebufferfull && argumentbufferactivate)
 			{
 				argumentbuffer[argumentbuffercnt] = tk;
 				int size = 4;
				if(strcmp(datatypebuffer,"int")==0)
				{
					size=4;
				}
				else if(strcmp(datatypebuffer,"float")==0)
				{
					size=8;
				}else if (strcmp(datatypebuffer,"char")==0)
				{
					size=1;
				}else if(strcmp(datatypebuffer,"double")==0)
				{
					size=16;
				}
 				argumentbuffersize[argumentbuffercnt]=size;
 				strcpy(argdtype[argumentbuffercnt++],datatypebuffer);
 			}else{
 				if(strcmp(tk->lexemename,"printf")==0||strcmp(tk->lexemename,"scanf")==0||strcmp(tk->lexemename,"return")==0)
 				{
 					keywordprev=1;
 					continue;
 				}
 				tk->index=hash(tk);
 			}
		}else if(strcmp(tk->lexemename,"for")==0 || strcmp(tk->lexemename,"while")==0|| strcmp(tk->lexemename,"if")==0)
		{
			keywordprev=1;
		}else if(strcmp(tk->lexemename,"{")==0)
		{
			scope++;
		}else if(strcmp(tk->lexemename,"}")==0)
		{
			scope--;
		}else if (strcmp(tk->lexemename,"[")==0&&(datatypebufferfull||argumentbufferactivate)){
			printf("hufihdi\n");
			if (argumentbufferactivate)
			{
				char temp[10];
				strcpy(temp,argdtype[argumentbuffercnt-1]);
				strcat(temp,"array");
				strcpy(argdtype[argumentbuffercnt-1],temp);

			}else
			{
				char temp[10];
				strcpy(temp,identifierdtype[identifierbuffercnt-1]);
				strcat(temp,"array");
				strcpy(identifierdtype[identifierbuffercnt-1],temp);		
				arrayactivate=1;		
			}
		}else if(tk->type==NUMBER && arrayactivate && datatypebufferfull)
		{
			identifiersize[identifierbuffercnt-1]=identifiersize[identifierbuffercnt-1]*atoi(tk->lexemename);
			arrayactivate=0;
		}
		else
		{
			arrayactivate=0;
		}

		tokens[index].lexemename=malloc(100);
		strcpy(tokens[index].lexemename,tk->lexemename);
		tokens[index].index = tk->index;
		tokens[index].row = tk->row;
		tokens[index].col = tk->col;
		tokens[index].type = tk->type;
		index++;
	}
	print(table);
	totallength=(int*)malloc(sizeof(int));
	*totallength = index;
	program();
}

int yywrap()
{
	return 1;
}