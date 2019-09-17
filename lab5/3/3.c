#include "token.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int matchFlag = 1;
token* lookahead;

void S();
void A();
void A1();
void B();

void S(){
    lookahead = getNextToken();
    if(strcmp(lookahead->lName,"a")==0){
    	A();
        lookahead = getNextToken();
    	if(strcmp(lookahead->lName,"c")==0){
    		B();
    		lookahead = getNextToken();
    		if(strcmp(lookahead->lName,"e")==0)
    			return;
    		else
    			matchFlag=0;
    	}
    	else
    		matchFlag=0;
    }    
    else
    	matchFlag=0; 
}

void A() {
    lookahead = getNextToken();
    if (strcmp(lookahead->lName, "b") == 0) {
        A1();
        return;
    }
    else
    	matchFlag=0;
}

void A1(){
	lookahead = getNextToken();
    if (strcmp(lookahead->lName, "b") == 0) {
        A1();
        return;
    }
    else
    	retract();
}

void B(){
	lookahead = getNextToken();
	if(strcmp(lookahead->lName, "d")==0){
		return;
	}
	else
		matchFlag = 0;
}

int main () {
    setupTokenList();
    printTokenList();
    S();
    lookahead = getNextToken();
    if ( matchFlag && strcmp(lookahead->tName, "EOTL") == 0 )
        printf("String Accepted");
    else
        printf("String Denied");
    return 0;
}