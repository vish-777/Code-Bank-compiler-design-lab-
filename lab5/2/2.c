#include "token.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int matchFlag = 1;
token* lookahead;

void E();
void E1();
void T();
void T1();
void F();

void E(){
    T();
    E1(); 
}

void E1() {
    lookahead = getNextToken();
    if (strcmp(lookahead->tName, "ADD") == 0) {
        T();
        E1();
        return;
    }
    retract();
}

void T(){
	F();
	T1();
}

void T1(){
	lookahead = getNextToken();
	if (strcmp(lookahead->tName, "MUL") == 0) {
        F();        
        T1();
        return;
    }
    retract();
}

void F(){
	lookahead = getNextToken();
	if(strcmp(lookahead->tName, "IDENTIFIER")==0){
		return;
	}
	else if(strcmp(lookahead->tName, "LP")==0){
		E();
		lookahead = getNextToken();
		if(strcmp(lookahead->tName, "RP")==0)
			return;
		else
			matchFlag = 0;
	}
	else
		matchFlag = 0;
}

int main () {
    setupTokenList();
    printTokenList();
    E();
    lookahead = getNextToken();
    if ( matchFlag && strcmp(lookahead->tName, "EOTL") == 0 )
        printf("String Accepted");
    else
        printf("String Denied");
    return 0;
}