
#include "helper.h"


int isNumber(char* string)
{
	char firstChar = string[0];
	int isNum = 0;
	for (int i = 0; i < strlen(string); i++)
	{
		if (isnumber(string[i]))
			isNum = 1;
		else
			return 0;
	}
	return isNum;
}

int isOperator(const char** Operators, char* string)
{
	if (strlen(string) > 1)
		return 0;

	char firstChar = string[0];
	for (int i = 0; i < sizeof(Operators); i++)
	{
		if (firstChar == Operators[i][0])
			return 1;
	}
	return 0;
}

int greaterOrEqual(Token itemIn, Token itemOut)
{
	if (*itemIn.data == '/' || *itemIn.data == '*')
	{
		return 1;
	}
	else
	{
		if (*itemOut.data == '+' || *itemOut.data == '-')
			return 1;
		return 0;
	}
}

int evaluate(int acc, char op, int x)
{
	int val;
	if (op == '+')
		val = acc + x;
	else if (op == '-')
		val = acc - x;
	else if (op == '/')
		val = acc / x;
	else if (op == '*')
		val = acc * x;
	else val = -1;
	return val;
}
/*
int getIdent(Vector iden, char* string)
{
	for (int i = 0; i < iden.size; i++)
	{
		if ( vector_get(iden, i ) == *string)
		{
			return TRUE;
		}
	}
	return FALSE;
}
*/