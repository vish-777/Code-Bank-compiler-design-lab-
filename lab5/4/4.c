#include "token.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int matchFlag = 1;
token* lookahead;

void lexp();
void aterm();
void list();
void lexp_seq();
void lexp_seq1();

void lexp(){
    lookahead = getNextToken();
    if(strcmp(lookahead->tName,"IDENTIFIER")==0 || strcmp(lookahead->tName,"NUMBER")==0){
    	retract();
        aterm();
        return;
    }
    else if(strcmp(lookahead->lName, "(") == 0){
    	retract();
        list();
        return;
    }
    else
        matchFlag=0;
}

void aterm() {
    lookahead=getNextToken();
    if (strcmp(lookahead->tName, "NUMBER")==0 || strcmp(lookahead->tName,"IDENTIFIER")==0)
        return;
    else
    	matchFlag=0;
}

void list(){
    lookahead=getNextToken();
    if (strcmp(lookahead->tName, "LP") == 0) {
        lexp_seq();
        lookahead = getNextToken();
        if (strcmp(lookahead->tName, "RP") == 0)
        	return;
        else 
        	matchFlag=0;
    }
    else
    	matchFlag=0;
}

void lexp_seq(){
	lexp();
	lexp_seq1();
}

void lexp_seq1(){
	lookahead=getNextToken();
    if (strcmp(lookahead->tName, "NUMBER") == 0 || strcmp(lookahead->tName, "IDENTIFIER") == 0 || strcmp(lookahead->lName, "(") == 0) {
        retract();
        lexp();
        lexp_seq1();
        return;
    }
    retract();
}

int main () {
    setupTokenList();
    printTokenList();
    lexp();
    lookahead = getNextToken();
    if ( matchFlag && strcmp(lookahead->tName, "EOTL") == 0 )
        printf("String Accepted");
    else
        printf("String Denied");
    return 0;
}