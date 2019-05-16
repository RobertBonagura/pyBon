#ifndef HELPER_H
#define HELPER_H

#include <ctype.h>
#include <string.h>
#include "dataStructs.h"

// Global variables
HashSet identifiers;

//Helper Functions
int isNumber(char* string);
int isOperator(char* string);
int isAssignment(char* string);
int isIdentifier(char* string);
int greaterOrEqual(Token itemIn, Token itemOut);
int evaluate(int acc, char op, int x);

#endif
