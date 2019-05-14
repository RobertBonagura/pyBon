
#include "pyBon.h"

//#include "helper.h"
//const char* TestIdentifiers[] = {"x", "t", "age", "minus"};

/**
 * ********************************************************************
 *  Main Function   
 * ********************************************************************/

int main(int argc, char *argv[])
{

	printf("Welcome to PyBon!\n");

	if (argc > 2) 
	// Too many arguments
	{
		printf("Please pass only one text file as an argument\n");
		exit(1);
	}

	else if (argc == 2) 
	// One python file passed in, runs file
	{	
		printf("Running %s... ", argv[1]);
		int file_size = sizeof(argv[1]);
		FILE *f = fopen(argv[1], "r"); // "r" for read

		if (!f) // If file isnt opened, a 1 is returned
		{
			printf("\nError: Could not read %s\n", argv[1]);
			return 1;
		}
		else 
		{
			printf("file opened succesfully\n");
			runfile(f);
			return 0;
		}
		
	}
	else  
	// Runs REPL
	{
		printf("Running REPL\n");
		runprompt();
		return 0;
	}
	
}
/*****************************************************
 * runfile(File*) - Runs PyBon on given file 
 ****************************************************/

int runfile(FILE* file)
{
	if (file == NULL) 
		{
			perror("Unable to open file");
			exit(1);
		}
	else
	{
		char line[1000];	
		while (fgets(line, 1000, file) != NULL) 
		{
			printf("This line is: %s", line);
			tokenize(line);
		}
		printf("Success reading from file\n");
		fclose(file);
		return 0;
	}
}

/*****************************************************
 * runprompt() - Runs PyBon REPL
 ****************************************************/

int runprompt()
{
	char line[1000]; 
	for (;;)
	{	
		printf(">>> ");
		fgets(line, 1000, stdin);
		tokenize(line);
		if (has_error == TRUE) 
			{
				return 1;
			}
	
	}
	// BREAK LOOP HERE
	/* if (inser_exit_condition_here) 
	{
		return 0;
	}
	*/
}

/****************************************************************************
 * tokenize(*string) - iterates through each word on given line
 * 	calls two important functions: 
 * 		makeToken(token) - to create Token struct
 * 		parseTokens(QueueOfTokens, SetOfVariables)
 *****************************************************************************/

void tokenize(char* string)
{
	struct Token *temp = malloc(sizeof(Token));

	//prepares space to copy string paramater to be split into multiple words
	int init_size = strlen(string);
	char * copy = malloc(strlen(string) + 1); 
	strcpy(copy, string);
	void *memory = malloc(sizeof(copy));
	char *word = (char *)memory;
	char delim[] = " ";
	word = strtok(copy, delim);

	TokenQueue* tokens = createTokenQueue(init_size);

	do 
	{
		 // if token has a trailing '\n', remove the '\n'
		if (word[strlen(word)-1] == '\n')
			word[strlen(word)-1] = '\0';

		if (strlen(word) == 0)
			printf("This is an empty line\n");

		else 
		{
			//determines type of word and creates appropriate Token
			Token token = makeToken(word); 
			enqueue(tokens, token); // adds this Token to queue of tokens for parser
		} 
		word = strtok(NULL, delim);
	} while (word != NULL);

	// returns result of parseTokens as value
	int val = parseToke(tokens);
	printf("%d\n", val);

	free(memory);
	free(copy);
}

/************************************************************************ 
 * makeToken(char* token) - reads str, determined type, returns Token
 ************************************************************************/
Token makeToken(char* word) 
{
	if (isNumber(word)) 
	{
		Token t = {word, NUMB};
		return t;
	}
	if (isOperator(Operators, word))
	{
		Token t = {word, OPER};
		return t;
	}
	/**
	  if (isIdentifier(identifiers, word))
	  {
	  		Token t = getVal(identifiers, word)
	  		return t;
	  }
	*/
	else
	{
		Token t = {word, IDEN};
		return t;
	}
}
/*****************************************************
 * parseTokens(Queue of Tokens, Set of Variables) 
 * Parses Tokens and evaluates them as an expression
 * 		State 0 - Ensures first token is number
 * 		State 1 - Ensures number is followed by Operator
 * 		State 2 - Ensure Operator is followed by Number
 * 
 * 	Tokens can be given as type NUMB or IDEN
 * 		- if Token is IDEN, check to see if it exists on VariableSet
 * 
 * 	If the first Token is not an IDEN, or, is an IDEN not followed by an
 *  assignment operation, this line will be an expression.
 * 
 *  This funciton currently assumes no assignment operation will be passed in
 *  and evaluates the line as an expression, returning an int value.
 ****************************************************/
int parseToke(TokenQueue* tokens)
{

	//State 0 - ensures first token is a number
	int accum = 0;
	if (isEmpty(tokens))
	{
		printf("Expression is empty.\n");
		return -1;
	}

	Token temp = dequeue(tokens);
	const char* type = tokenTypes[temp.type];
	if (strncmp(type, "NUMB", 3) != 0 && strncmp(type, "NUMB", 3) != 0)
	{
		printf("The expression must start with a number\n");
		return -1;
	}
	
	if (strncmp(type, "NUMB", 3) == 0)
	{
		accum = atoi(temp.data);
	}
	else //temp.type == "IDEN"
	{
		//accum = getIden(&identifiers, temp.data);
		printf("Error: Not able to evalute identifiers yet\n");
	}
	
	//loops through queue untill its gone through all tokens.
	int needsOperator = TRUE;
	int needsNumber = FALSE;
	char operation = 0;
	while (!isEmpty(tokens))
	{
		// State 1  - Ensures Number is followed by Operator
		
		if (needsOperator)
		{
			Token temp = dequeue(tokens);
			const char* type = tokenTypes[temp.type];
			if (strncmp(type, "IDEN", 3) == 0)
			{
				//temp = getIden(TestIdentifiers, temp.data);
				//type = tokenTypes[temp.type];
			}
			if (strncmp(type, "OPER", 3) != 0)
			{
				printf("ERROR: Every number must be followed by an Operator\n");
				return -1;
			}
				operation = *temp.data;
				needsOperator = FALSE;
				needsNumber = TRUE;
		}
		// State 2  - Ensures Operator is followed by a number
		if (needsNumber)
		{	
			if (isEmpty(tokens))
			{
				printf("ERROR: An operation must be followed by a number\n");
				return -1;
			}

			Token temp = dequeue(tokens);
			const char* type = tokenTypes[temp.type];
			if (strncmp(type, "IDEN", 3) == 0)
			{
				printf("Sorry, cant check for Identifiers right now\n");
				return -1;
				//temp = getIden(TestIdentifiers, temp.data);
				//type = tokenTypes[temp.type];
			}

			if (strncmp(type, "NUMB", 3) != 0)
			{
				printf("ERROR: An operation must be followed by a number\n");
				return -1;	
			}
			int operand = atoi(temp.data);
			needsOperator = TRUE;
			needsNumber = FALSE;
			accum = evaluate(accum, operation, operand);
		}
	}
	return accum;
}