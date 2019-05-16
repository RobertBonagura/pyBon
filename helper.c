
#include "helper.h"


int isNumber(char* string)
{

	char firstChar = string[0];
	int isNum = 0;

	int i = 0;
	if (firstChar == '-')
		i++;
	for (; i < strlen(string); i++)
	{
		if (isnumber(string[i]))
			isNum = 1;
		else
			return 0;
	}
	return isNum;
	
}

int isOperator(char* string)
{
	if (strlen(string) > 1)
		return 0;

	const char* Operators[] = {"+", "-", "*", "/", "f"};
	char firstChar = string[0];
	int listSize = sizeof(Operators) / sizeof(Operators[0]);

	for (int i = 0; i < listSize; i++)
	{
		if (firstChar == Operators[i][0])
			return 1;
	}
	return 0;
}

int isAssignment(char* string)
{
	if (strlen(string) > 1)
		return 0;

	const char assign = '=';
	char firstChar = string[0];
	if (firstChar == assign)
		return 1;
	else return 0;
}

int isIdentifier(char* string)
{
	// asserts first character is not Num or Uppercase
	if (!isNumber(string) && (!isupper(string[0])))
	{
		// checks all characters are valid ascii
		for (int i = 0; i < strlen(string); i++)
		{
			int asciVal = string[i];
			if ((asciVal >= 65 && asciVal <= 90) || (asciVal >= 97 && asciVal <= 122))
				;
			else
				return 0;
		}
		return 1;
	}
	else return 0;
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