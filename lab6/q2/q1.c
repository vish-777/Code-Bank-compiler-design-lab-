#include "symtab.h"
#include <stdlib.h>
#include <stdio.h>
token tokens[100];
smt* table[SIZE];

int parseindex=0;
token lookahead;
int error = 0;
int* totallength;
void looping_stat();
void expn();
void statement_list();
void assign_stat();
void simple_expn();
void eprime();
void term();
void seprime();
void factor();
void tprime();
void declarations();
void identifier_list();
void statement_list();
void statement();
void decision_stat();
void dprime();
void program();


void program()
{
	lookahead = tokens[parseindex++];
	if(strcmp(lookahead.lexemename,"main")==0)
	{
		lookahead = tokens[parseindex++];
		if(strcmp(lookahead.lexemename,"(")==0)
		{
			lookahead = tokens[parseindex++];
			if(strcmp(lookahead.lexemename,")")==0)
			{
				lookahead = tokens[parseindex++];
				if(strcmp(lookahead.lexemename,"{")==0)
				{
					declarations();
					statement_list();
					lookahead = tokens[parseindex++];
					if(strcmp(lookahead.lexemename,"}")==0)
					{

						lookahead = tokens[parseindex++];
						if(strcmp(lookahead.lexemename,"$")==0)
						{
							printf("success!\n");
							exit(0);
						}else if(parseindex==*totallength)
						{
							printf("error: reached EOF file while parsing\n");
						}
					}else
					{
						printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,"}",lookahead.lexemename);
					exit(0);
					}
				}else
				{
					printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,"{",lookahead.lexemename);
					exit(0);
				}
			}else
			{
				printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,")",lookahead.lexemename);
					exit(0);
			}
		}else
		{
			printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,"(",lookahead.lexemename);
					exit(0);
		}
	}else
	{
		printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,"main",lookahead.lexemename);
					exit(0);
	}
}

void looping_stat()
{
	lookahead = tokens[parseindex++];
	if (strcmp(lookahead.lexemename,"while")==0)
	{
		lookahead = tokens[parseindex++];
		if(strcmp(lookahead.lexemename,"(")==0)
		{
			expn();
			lookahead = tokens[parseindex++];
			if (strcmp(lookahead.lexemename,")")==0)
			{
				lookahead = tokens[parseindex++];
				if(strcmp(lookahead.lexemename,"{")==0)
				{
					statement_list();
					lookahead = tokens[parseindex++];
					if(strcmp(lookahead.lexemename,"}")==0)
					{
						lookahead = tokens[parseindex++];
						if(strcmp(lookahead.lexemename,"$")==0&& parseindex==*totallength)
						{
							printf("error: end of file reached. Possibility of unbalanced braces.\n" );	
							exit(0);
						}else if(strcmp(lookahead.lexemename,"$")==0&& parseindex!=*totallength)
						{
							printf("error: end of file reached. Possibility of unbalanced braces.\n" );
							exit(0);
						}
						else 
						{
							parseindex--;
							return;
						}
					}else 
					{
						printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,"}",lookahead.lexemename);
						exit(0);
					}
				}else
				{
					printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,"{",lookahead.lexemename);
					exit(0);
				}
			}else{printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,")",lookahead.lexemename);
					exit(0);}
		}else{printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,"(",lookahead.lexemename);
					exit(0);}
	}else if(strcmp(lookahead.lexemename,"for")==0)
	{
		lookahead = tokens[parseindex++];
		if(strcmp(lookahead.lexemename,"(")==0)
		{
			assign_stat();

			lookahead = tokens[parseindex++];
			if(strcmp(lookahead.lexemename,";")==0)
			{

				expn();
				lookahead = tokens[parseindex++];
				if(strcmp(lookahead.lexemename,";")==0)
				{
					assign_stat();
					lookahead = tokens[parseindex++];
					if (strcmp(lookahead.lexemename,")")==0)
					{
						lookahead = tokens[parseindex++];
						if(strcmp(lookahead.lexemename,"{")==0)
						{
							statement_list();
							lookahead = tokens[parseindex++];
							if(strcmp(lookahead.lexemename,"}")==0)
							{

								lookahead = tokens[parseindex++];

								if(strcmp(lookahead.lexemename,"$")==0&& parseindex==*totallength)
								{
									printf("error: end of file reached. Possibility of unbalanced braces.\n" );
									exit(0);
								}else if(strcmp(lookahead.lexemename,"$")==0&& parseindex!=*totallength)
								{
									printf("error: end of file reached. Possibility of unbalanced braces.\n" );
									exit(0);
								}
								else 
								{
									parseindex--;
									return;
								}
							}else 
							{
								printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,"}",lookahead.lexemename);
								exit(0);
							}
						}else
						{
							printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,"{",lookahead.lexemename);
							exit(0);
						}
					}else{printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,")",lookahead.lexemename);
					exit(0);}
				}else{printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,";",lookahead.lexemename);
					exit(0);}
			}else{printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,";",lookahead.lexemename);
					exit(0);}	
		}else{printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,"(",lookahead.lexemename);
					exit(0);}	
	}else
	{
		printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,"for or while",lookahead.lexemename);
		exit(0);
	}
}









void declarations()
{
	lookahead = tokens[parseindex++];
	if(strcmp(lookahead.lexemename,"int")==0||strcmp(lookahead.lexemename,"char")==0)
	{
		identifier_list();
		lookahead = tokens[parseindex++];
		if(strcmp(lookahead.lexemename,";")==0)
		{
			declarations();
		}
	}else
	{
		parseindex--;
	}
}

void identifier_list()
{
	lookahead = tokens[parseindex++];
	if(lookahead.type == IDENTIFIER)
	{

		lookahead = tokens[parseindex++];
		if(strcmp(lookahead.lexemename,",")==0)
		{
			identifier_list();
		}else if(strcmp(lookahead.lexemename,"[")==0)
		{
			lookahead = tokens[parseindex++];
			if(lookahead.type == NUMBER)
			{
				lookahead = tokens[parseindex++];
				if(strcmp(lookahead.lexemename,"]")==0)
				{
					lookahead = tokens[parseindex++];
					if(strcmp(lookahead.lexemename,",")==0)
					{
						identifier_list();
					}else
					{
						parseindex--;
						return;
					}
				}else
				{
					printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,"]",lookahead.lexemename);
					exit(0);
				}
			}else
			{
				printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,"NUMBER",lookahead.lexemename);
				exit(0);
			}
		}else{
			parseindex--;
			return;
		}
	}else
	{
		printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,"IDENTIFIER",lookahead.lexemename);
		exit(0);
	}
}

void statement_list()
{
	lookahead = tokens[parseindex++];
	if(strcmp(lookahead.lexemename,"for")==0||strcmp(lookahead.lexemename,"if")==0||strcmp(lookahead.lexemename,"while")==0|| lookahead.type==IDENTIFIER||strcmp(lookahead.lexemename,"int")==0||strcmp(lookahead.lexemename,"char")==0)
	{
		parseindex--;
		statement();
		statement_list();
	}else
	{
		parseindex--;
	}
}
void statement()
{
	lookahead = tokens[parseindex++];
	if(strcmp(lookahead.lexemename,"if")==0)
	{
		parseindex--;
		decision_stat();
	}else if(lookahead.type==IDENTIFIER)
	{
		parseindex--;
		assign_stat();
		lookahead = tokens[parseindex++];
		if(strcmp(lookahead.lexemename,";")==0)
		{
			return;
		}else
		{
			printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,";",lookahead.lexemename);
			exit(0);
		}
	}else if(strcmp(lookahead.lexemename,"for")==0|| strcmp(lookahead.lexemename,"while")==0)
	{
		parseindex--;
		looping_stat();
	}else if(strcmp(lookahead.lexemename,"int")==0 || strcmp(lookahead.lexemename,"char")==0)
	{
		
		parseindex--;
		declarations();
	}
	else
	{
		printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,"statement(for,while,if or id)",lookahead.lexemename);
		exit(0);
	}
}
void assign_stat()
{
	lookahead = tokens[parseindex++];
	int whicherrormsg = search(&lookahead,NULL,table);
	if(lookahead.type==IDENTIFIER&&whicherrormsg!=-1)
	{
		lookahead = tokens[parseindex++];
		if(strcmp(lookahead.lexemename,"=")==0)
		{
			expn();
		}else
		{
			printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,"=",lookahead.lexemename);
			exit(0);
		}
	}else
	{
		if(whicherrormsg==-1)
		{
			printf("error: using variable %s without declaration\n",lookahead.lexemename);
		}else
		{
		printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,"IDENTIFIER",lookahead.lexemename);
		}
		exit(0);
	}
}

void expn()
{
	simple_expn();
	eprime();
}

void eprime()
{
	lookahead = tokens[parseindex++];
	if(lookahead.type == LTE ||lookahead.type == GTE || lookahead.type == LT ||lookahead.type == GT || lookahead.type == NE || lookahead.type == EE)
	{
		simple_expn();
	}else
	{
		parseindex--;
	}
}

void simple_expn()
{
	term();
	seprime();
}

void seprime()
{
	lookahead = tokens[parseindex++];
	if(lookahead.type==ADD || lookahead.type==SUB)
	{
		term();
		seprime();
	}else
	{
		parseindex--;
	}
}

void term()
{
	factor();
	tprime();
}

void tprime()
{
	lookahead = tokens[parseindex++];
	if(strcmp(lookahead.lexemename,"*")==0||strcmp(lookahead.lexemename,"/")==0||strcmp(lookahead.lexemename,"%")==0)
	{
		factor();
		tprime();
	}else
	{
		parseindex--;
	}
}

void factor()
{
	lookahead = tokens[parseindex++];
	if(lookahead.type == IDENTIFIER)
	{
		return;
	}else if (lookahead.type == NUMBER)
	{
		return;
	}else
	{
		printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,"IDENTIFIER or NUMBER",lookahead.lexemename);
			exit(0);
	}
}

void decision_stat()
{
	lookahead = tokens[parseindex++];
	if(strcmp(lookahead.lexemename,"if")==0)
	{
		lookahead = tokens[parseindex++];
		if(strcmp(lookahead.lexemename,"(")==0)
		{
			expn();
			lookahead = tokens[parseindex++];
			if(strcmp(lookahead.lexemename,")")==0)
			{
				lookahead = tokens[parseindex++];
				if(strcmp(lookahead.lexemename,"{")==0)
				{
					statement_list();
					lookahead = tokens[parseindex++];
					if(strcmp(lookahead.lexemename,"}")==0)
					{
						dprime();
					}else
					{
						printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,"}",lookahead.lexemename);
						exit(0);		
					}
				}else
				{
					printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,"{",lookahead.lexemename);
					exit(0);
				}
			}else
			{
				printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,")",lookahead.lexemename);
				exit(0);
			}
		}else
		{
			printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,"(",lookahead.lexemename);
			exit(0);
		}
	}else
	{
		printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,"if",lookahead.lexemename);
		exit(0);
	}
}

void dprime()
{
	lookahead = tokens[parseindex++];
	if(strcmp(lookahead.lexemename,"else")==0)
	{
		lookahead = tokens[parseindex++];
		if(strcmp(lookahead.lexemename,"{")==0)
		{
			statement_list();
			lookahead = tokens[parseindex++];
			if(strcmp(lookahead.lexemename,"}")==0)
			{
				return;
			}else
			{
				printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,"}",lookahead.lexemename);
				exit(0);
			}
		}else
		{
			printf("error: row:%d col:%d expected %s got %s\n",lookahead.row,lookahead.col,"{",lookahead.lexemename);
			exit(0);
		}
	}else
	{
		parseindex--;
	}
}


/*int main(int argc,char* argv[])
{
	smt* table[SIZE];
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
			printf("%d\n",keywordprev);
			if(keywordprev==0)
			{
				
				for(int i=0;i<argumentbuffercnt;i++)
				{	printf("%s\n",argumentbuffer[i]->lexemename);
					insert(argumentbuffer[i],argumentbuffersize[i],argdtype[i],1,NULL,0,NULL,table,1);	
				}
				
				insert(identifierbuffer[0],-1,NULL,scope,argumentbuffer,argumentbuffercnt,returntypebuffer,table,0);
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
		strcpy(tokens[index].lexemename,tk->lexemename);
		tokens[index].index = tk->index;
		tokens[index].row = tk->row;
		tokens[index].col = tk->col;
		tokens[index].type = tk->type;
	}
	print(table);

	looping_stat();
}

*/
