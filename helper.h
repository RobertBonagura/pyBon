#ifndef HELPER_H
#define HELPER_H

#include <ctype.h>
#include <string.h>
#include "dataStructs.h"

//Helper Functions
int isNumber(char* string);
int isOperator(const char** Operators, char* string);
int greaterOrEqual(Token itemIn, Token itemOut);
int evaluate(int acc, char op, int x);
//int getIdent(Vector iden, char* string);

#endif
