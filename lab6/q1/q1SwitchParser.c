#include "token.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int matchFlag = 1;
token* lookahead;

void reportError(token* tok, char *errMsg);
void SS();             
void LSS();            
void label_stmt();      
void looping_stat();    
void expn();            
void simple_expn();     
void eprime();         
void term();            
void factor();          
void tprime();          
void mulop();         
void seprime();         
void addop();           
void relop();           
void statement_list(); 
void statement();      
void assign_stat();    
void decision_stat();   
void dprime();         
 
void reportError(token* tok, char *errMsg) {
    char *finalStr = (char*)malloc(sizeof(char) * 1024);
    char *lineNumber = (char*)malloc(sizeof(char) * 16);
    char *columnNumber = (char*)malloc(sizeof(char) * 16);
    sprintf(lineNumber, "%d", tok->line);
    sprintf(columnNumber, "%d", tok->column);
    strcpy(finalStr, "[!]PARSE_ERROR @ {Line:Col}={");
    strcat(finalStr, lineNumber);
    strcat(finalStr, ":");
    strcat(finalStr, columnNumber);
    strcat(finalStr, "} >> ");
    strcat(finalStr, errMsg);
    strcat(finalStr, " | Got: '");
    strcat(finalStr, tok->lName);
    strcat(finalStr, "'");
    fprintf(stderr, "%s\n", finalStr);
    free(finalStr);
    free(lineNumber);
    free(columnNumber);
}

int main () {
    setupTokenList();
    printTokenList();
    SS();
    lookahead = getNextToken(); 
    if ( matchFlag && strcmp(lookahead->tName, "EOTL") == 0 ) {
        printf("Verdict: ACCEPTED.");
    } else {
        printf("Verdict: DENIED.");
    }
    return 0;
}

void SS() {
    lookahead = getNextToken();
    if (strcmp(lookahead->lName, "switch") == 0 ) {
        lookahead = getNextToken();
        if (strcmp(lookahead->lName, "(") == 0 ) {
            expn();
            lookahead = getNextToken();
            if (strcmp(lookahead->lName, ")") == 0 ) {
                lookahead = getNextToken();
                if (strcmp(lookahead->lName, "{") == 0 ) {
                    LSS();
                    lookahead = getNextToken();
                    if (strcmp(lookahead->lName, "}") == 0 ) {
                        return;
                    } else {
                        matchFlag = 0;
                        reportError(lookahead, "Expected '}'");
                        return;
                    }
                } else {
                    matchFlag = 0;
                    reportError(lookahead, "Expected '{'");
                    return;
                }
            } else {
                matchFlag = 0;
                reportError(lookahead, "Expected ')'");
                return;
            }
        } else {
            matchFlag = 0;
            reportError(lookahead, "Expected '('");
            return;
        }
    } else {
        matchFlag = 0;
        printf("e1\n");
        return;
    }
}

void LSS() {
    lookahead = getNextToken();
    if ( strcmp(lookahead->lName, "case") == 0 || strcmp(lookahead->lName, "default") == 0) {
        retract();
        label_stmt();
        LSS();
        return;
    }
    retract();
}

void label_stmt() {
    lookahead = getNextToken();
    if ( strcmp(lookahead->lName, "case") == 0 ) {
        lookahead = getNextToken();
        if ( strcmp(lookahead->tName, "NUMBER") == 0 ) {
            lookahead = getNextToken();
            if ( strcmp(lookahead->lName, ":") == 0 ) {
                statement_list();
                return;
            } else {
                matchFlag = 0;
                reportError(lookahead, "Expected ':'");
                return;
            }
        } else {
            matchFlag = 0;
            reportError(lookahead, "Expected NUMBER");
            return;
        }
    } else if (strcmp(lookahead->lName, "default") == 0) {
        lookahead = getNextToken();
        if ( strcmp(lookahead->lName, ":") == 0 ) {
            statement_list();
            return;
        } else {
            matchFlag = 0;
            reportError(lookahead, "Expected ':'");
            return;
        }
    } else {
        matchFlag = 0;
        reportError(lookahead, "Expected 'case' or 'default'");
        return;
    }
}

void looping_stat() {
    lookahead = getNextToken();
    if (strcmp(lookahead->lName, "while") == 0 ) {
        lookahead = getNextToken();
        if (strcmp(lookahead->lName, "(") == 0) {
            expn();
            lookahead = getNextToken();
            if (strcmp(lookahead->lName, ")") == 0) {
                lookahead = getNextToken();
                if (strcmp(lookahead->lName, "{") == 0) {
                    statement_list();
                    lookahead = getNextToken();
                    if (strcmp(lookahead->lName, "}") == 0) {
                        return;
                    } else {
                        matchFlag = 0;
                        reportError(lookahead, "Expected '}'");
                        return;
                    }
                } else {
                    matchFlag = 0;
                    reportError(lookahead, "Expected '{'");
                    return;
                }
            } else {
                matchFlag = 0;
                reportError(lookahead, "Expected ')'");
                return;
            }
        } else {
            matchFlag = 0;
            reportError(lookahead, "Expected '('");
            return;
        }
    } else if (strcmp(lookahead->lName, "for") == 0) {
        lookahead = getNextToken();
        if (strcmp(lookahead->lName, "(") == 0 ) {
            assign_stat();
            lookahead = getNextToken();
            if (strcmp(lookahead->lName, ";") == 0 ) {
                expn();
                lookahead = getNextToken();
                if (strcmp(lookahead->lName, ";") == 0 ) {
                    assign_stat();
                    lookahead = getNextToken();
                    if (strcmp(lookahead->lName, ")") == 0 ) {
                        lookahead = getNextToken();
                        if (strcmp(lookahead->lName, "{") == 0 ) {
                            statement_list();
                            lookahead = getNextToken();
                            if (strcmp(lookahead->lName, "}") == 0 ) {
                                return;
                            } else {
                                matchFlag = 0;
                                reportError(lookahead, "Expected '}'");
                                return;
                            }
                        } else {
                            matchFlag = 0;
                            reportError(lookahead, "Expected '{'");
                            return;
                        }
                    } else {
                        matchFlag = 0;
                        reportError(lookahead, "Expected ')'");
                        return;
                    }
                } else {
                    matchFlag = 0;
                    reportError(lookahead, "Expected ';'");
                    return;
                }
            } else {
                matchFlag = 0;
                reportError(lookahead, "Expected ';'");
                return;
            }
        } else {
            matchFlag = 0;
            reportError(lookahead, "Expected '('");
            return;
        }
    }  else {
        matchFlag = 0;
        printf("e2\n");
        return;
    }
}

void expn() {
    simple_expn();
    eprime();
}

void simple_expn() {
    term();
    seprime();
}

void eprime() {
    lookahead = getNextToken();
    if ( strcmp(lookahead->tName, "RLOP") == 0) {
        retract();
        relop();
        simple_expn();
        return;
    }
    retract();
}

void term() {
    factor();
    tprime();
}
void factor() {
    lookahead = getNextToken();
    if (strcmp(lookahead->tName, "IDENTIFIER") == 0 || strcmp(lookahead->tName, "NUMBER") == 0) {
        return;
    } else {
        matchFlag = 0;
        reportError(lookahead, "Expected IDENTIFIER OR NUMBER");
        return;
    }
}

void tprime() {
    lookahead = getNextToken();
    if (strcmp(lookahead->lName, "*") == 0 || strcmp(lookahead->lName, "/") == 0 ) {
        retract();
        mulop();
        factor();
        tprime();
        return;
    }
    retract();
}

void mulop() {
    lookahead = getNextToken();
    if (strcmp(lookahead->lName, "*") == 0 || strcmp(lookahead->lName, "/") == 0 ) {
        return;
    } else {
        matchFlag = 0;
        reportError(lookahead, "Expected '*' or '/'");
        return;
    }
}
void seprime() {
    lookahead = getNextToken();
    if (strcmp(lookahead->lName, "+") == 0 || strcmp(lookahead->lName, "-") == 0 ) {
        retract();
        addop();
        term();
        seprime();
        return;
    }
    retract();
}

void addop() {
    lookahead = getNextToken();
    if (strcmp(lookahead->lName, "+") == 0 || strcmp(lookahead->lName, "-") == 0 ) {
        return;
    } else {
        matchFlag = 0;
        reportError(lookahead, "Expected '+' or '-'");
        return;
    }
}

void relop() {
    lookahead = getNextToken();
    if ( strcmp(lookahead->tName, "RLOP") == 0) {
        return;
    } else {
        matchFlag = 0;
        reportError(lookahead, "Expected RELOP");
        return;
    }
}

void statement_list() {
    lookahead = getNextToken();
    if ( strcmp(lookahead->tName, "IDENTIFIER") == 0 || strcmp(lookahead->lName, "if") == 0 || strcmp(lookahead->lName, "for") == 0 || strcmp(lookahead->lName, "while") == 0) {
        retract();
        statement();
        statement_list();
        return;
    }
    retract();
}
     0   6  13 >
<         (         LP      0   6  19 >
<         1     NUMBER      0   6  20 >
<        ==       RLOP      0   6  22 >
<         1     NUMBER      0   6  25 >
<         )         RP      0   6  26 >
<         {         LC      0   6  28 >
<         i IDENTIFIER      0   7  17 >
<         =     ASSIGN      0   7  19 >
<         2     NUMBER      0   7  21 >
<         +        ADD      0   7  23 >
<         a IDENTIFIER      0   7  25 >
<         /       AROP      0   7  27 >
<         x IDENTIFIER      0   7  29 >
<         ;         SS      0   7  30 >
<         }         RC      0   8  13 >
<   default    KEYWORD      0  10   5 >
<         :         SS      0  10  12 >
<        if    KEYWORD      0  10  14 >
<         (         LP      0  10  17 >
<         b IDENTIFIER      0  10  19 >
<        ==       RLOP      0  10  21 >
<         2     NUMBER      0  10  24 >

void statement() {
    lookahead = getNextToken();
    if (strcmp(lookahead->tName, "IDENTIFIER") == 0) {
        retract();
        assign_stat();
        lookahead = getNextToken();
        if (strcmp(lookahead->lName, ";") == 0) {
            return;
        } else { //error missing ";"
            matchFlag = 0;
            reportError(lookahead, "Expected ';'");
            return;
        }
    } else if (strcmp(lookahead->lName, "if") == 0) {
        retract();
        decision_stat();
        return;
    } else if (strcmp(lookahead->lName, "while") == 0 || strcmp(lookahead->lName, "for") == 0) {
        retract();
        looping_stat();
        return;
    } else {
        matchFlag = 0;
        reportError(lookahead, "Unexpected input");
        return;
    }
}

void assign_stat() {
    lookahead = getNextToken();
    if ( strcmp(lookahead->tName, "IDENTIFIER") == 0 ) {
        lookahead = getNextToken();
        if ( strcmp(lookahead->lName, "=") == 0 ) {
            expn();
        } else {
            matchFlag = 0;
            reportError(lookahead, "Expected '='");            
            return;
        }
    } else {
        matchFlag = 0;
        reportError(lookahead, "Expected IDENTIFIER");
        return;
    }
}


void decision_stat() {
    lookahead = getNextToken();
    if ( strcmp(lookahead->lName, "if") == 0 ) {
        lookahead = getNextToken();
        if ( strcmp(lookahead->lName, "(") == 0 ) {
            expn();
            lookahead = getNextToken();
            if ( strcmp(lookahead->lName, ")") == 0 ) {
                lookahead = getNextToken();
                if ( strcmp(lookahead->lName, "{") == 0 ) {
                    statement_list();
                    lookahead = getNextToken();
                    if ( strcmp(lookahead->lName, "}") == 0 ) {
                        dprime();
                        return;
                    } else {
                        matchFlag = 0;
                        reportError(lookahead, "Expected '}'");
                        return;
                    }
                } else {
                    matchFlag = 0;
                    reportError(lookahead, "Expected '{'");
                    return;
                }
            } else {
                matchFlag = 0;
                reportError(lookahead, "Expected ')'");
                return;
            }
        } else {
            matchFlag = 0;
            reportError(lookahead, "Expected '('");
            return;
        }
    } else {
        matchFlag = 0;
        reportError(lookahead, "Expected 'if'");
        return;
    }
}

void dprime() {
    lookahead = getNextToken();
    if ( strcmp(lookahead->lName, "else") == 0 ) {
        lookahead = getNextToken();
        if ( strcmp(lookahead->lName, "{") == 0 ) {
            statement_list();
            lookahead = getNextToken();
            if ( strcmp(lookahead->lName, "}") == 0 ) {
                return;
            } else {
                matchFlag = 0;
                reportError(lookahead, "Expected '}'");
                return;
            }
        } else {
            matchFlag = 0;
            reportError(lookahead, "Expected '{'");
            return;
        }
        return;
    }
    retract();
}
