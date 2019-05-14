#ifndef PYBON_H
#define PYBON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helper.h"


#define TRUE  1
#define FALSE 0

int has_error = FALSE;

// Function declarations
int runfile(FILE *fp);
int runprompt();
void tokenize(char* str);
Token makeToken(char* word);
int parseToke(TokenQueue* tokens);

const char* tokenTypes[] = {"UNDEF", "NUMB", "OPER", "IDEN"};
const char* Operators[] = {"+", "-", "*", "/"};
const char* TestIdentifiers[] = {"x", "t", "age", "minus"};

#endif