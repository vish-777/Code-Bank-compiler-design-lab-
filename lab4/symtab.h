#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define tableLen 30
int len_of_table=0;
// enum tokenType {ID, FUNCTION};

enum tokenType {EOFILE=-1, LITERAL, KEYWORD, NUMBER, IDENTIFIER, SYMBOL, AOP, LOP, RELOP, FUNCTION};

struct Token
{
	char *lexeme;
	int index,sizeofvar;
	int row, col;
	enum tokenType type;
};
typedef struct Token* Tokenptr;

struct ListElement
{
	Tokenptr tp;
	int hashval, argc;
	char *name, *type, scope, args[10][10], *ret;
	struct ListElement *next;
};
typedef struct ListElement* LEptr;

LEptr TABLE[1000];

void initialize()
{
	for(int i=0; i<len_of_table; i++)
		TABLE[i] = NULL;
}

void Display()
{
	char arr[15][15]={"LITERAL",
			  "KEYWORD", 
			  "NUMBER",
			  "IDENTIFIER",
			  "SYMBOL", 
			  "AOP",
			  "LOP",
			  "RELOP", 
			  "FUNCTION"};
	printf("Name\t\tType\t\tSize\tScope\tNoArgs\tArgs\tRetType\n\n");	
	for(int i=0; i<=len_of_table; i++)
	{
		LEptr temp = TABLE[i];
		while(temp)
		{
			printf("%s\t\t%s\t%d\t  %c\t  %d\t",temp->tp->lexeme,arr[temp->tp->type],temp->tp->sizeofvar,temp->scope,temp->argc);
			for(int i=0;i<temp->argc;i++)
				printf("%s,",temp->args[i]);
			printf("\t%s\n",temp->ret);
			temp = temp->next;
		}		
	}
}

int Hash(char *str)
{
	int s=0, p=31, pw=1;
	for(int i=0; i<strlen(str); i++)
	{
		s+=((str[i]-'a'+1)*pw)%tableLen;
		pw = pw*p%tableLen;
	}
	return s;
}

int Search(char *str)
{
	int x = Hash(str);
	LEptr temp = TABLE[x];
	while(temp)
	{
		if(strcmp(temp->tp->lexeme, str)==0)
			return 1;
		temp = temp->next;
	}
	return 0;
}

void Insert(Tokenptr tp, char* dtype, int scope, char args[10][10], int argc)
{
	if(Search(tp->lexeme)==1)
		return;
	//printf("\nInserting %s", tp->lexeme);
	int x = Hash(tp->lexeme);
	//printf("    Hash value:%d\n\n", x);
	if(len_of_table<x)
		len_of_table=x;
	LEptr le = (LEptr)malloc(sizeof(struct ListElement));
	le -> tp = tp;
	le -> name = (char*)malloc(sizeof(tp->lexeme));
	strcpy(le -> name, tp->lexeme);
	le -> hashval = x;
	if(tp->type==IDENTIFIER)
	{
		le -> argc = 0;
		le -> ret = "NULL";
	struct ListElement *next;
		if(scope == 0)
			le -> scope = 'G';
		else
			le -> scope = 'L';
		le -> type = (char*)malloc(sizeof(dtype));
		strcpy(le -> type, dtype);

	}
	else if(tp->type==FUNCTION)
	{
		le -> scope = ' ';
		le -> type = "";
		le -> ret = (char*)malloc(sizeof(dtype));
		strcpy(le -> ret, dtype);
		le -> argc = argc;
		for(int i=0; i<argc; i++)
			strcpy(le -> args[i], args[i]);
	}
	// **args, ret;
	le -> next = NULL;
	if(TABLE[x]==NULL)
		TABLE[x] = le;
	else
	{
		LEptr temp = TABLE[x];
		while(temp->next)
		{
			temp = temp->next;
			le -> hashval +=tableLen;
		}
		temp->next = le;
	}
}