#include "token.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int matchFlag = 1;
token* lookahead;

void S();
void T();
void T1();

void S() {
    lookahead = getNextToken();
    
    if ( strcmp(lookahead->tName, "EOTL") == 0 && matchFlag == 1) {
        printf("SUCCESS");
        return;
    }
    
    if ( strcmp(lookahead->lName, "a") == 0 )
        return;
    else if (strcmp(lookahead->lName, ">") == 0 )
        return;
    else if (strcmp(lookahead->lName, "(") == 0 ) {
        T();
        lookahead = getNextToken();
        if ( strcmp(lookahead->lName, ")") == 0 )
            return; 
        else 
            matchFlag = 0;
    } 
    else
        matchFlag=0;
}

void T() {
    S();
    T1();
}

void T1() {
    lookahead = getNextToken();
    if ( strcmp(lookahead->lName, ",") == 0) {
        S();
        T1();
        return;
    }
    retract();
}

int main () {
    setupTokenList();
    printTokenList();
    S();
    lookahead = getNextToken();
    if ( matchFlag && strcmp(lookahead->tName, "EOTL") == 0 ) {
        printf("String Accepted");
    } else {
        printf("String Denied");
    }
    return 0;
}