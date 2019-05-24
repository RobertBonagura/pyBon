
#include "pyBon.h"

// TO DO

// print set
// isEmpty set

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
	/*
	Token first = {"499", NUMB};
	Token* pToke = &first;
	addVal(&*set, "var", &*pToke);
	*/
	HashSet* set;

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
			tokenize(line, &*set);
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
	HashSet* set = init_HashSet(97);
	/*
	Token first = {"499", NUMB};
	Token* pToke = &first;
	//Come back an check, i may not need to dereference Token
	addVal(&*set, "var1", &*pToke);

	Token second = {"788", NUMB};
	pToke = &second;
	addVal(&*set, "age", &*pToke);
	Token new2 = getVal(set, "var1");
		

	for (int i = 0; i < set->capacity; i++)
	{
		printf("%s\n", set->array[0].data);
	}

	Token new3 = getVal(set, "age");

	*/
	char line[1000]; 
	for (;;)
	{	
		printf(">>> ");
		fgets(line, 1000, stdin);
		tokenize(line, &*set);
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

void tokenize(char* string, HashSet* set)
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
			printf("");

		else 
		{
			//determines type of word and creates appropriate Token
			Token token = makeToken(word); 
			enqueue(tokens, token); // adds this Token to queue of tokens for parser
		} 
		word = strtok(NULL, delim);
	} while (word != NULL);

	parseToke(&*tokens, &*set);

	free(memory);
	free(copy);
}

/************************************************************************ 
 * makeToken(char* token) - reads str, determined type, returns Token
 ************************************************************************/
Token makeToken(char* word) 
{
	//char* new;
	if (isNumber(word)) 
	{
		Token t = {word, NUMB};
		return t;
	}
	else if (isOperator(word))
	{
		Token t = {word, OPER};
		return t;
	}
	else if (isAssignment(word))
	{
		Token t = {word, ASGN};
		return t;
	}
	else if (isIdentifier(word))
	{
		Token t = {word, IDEN};
		return t;
	}
	else
	{
		Token t = {word, UNDF};
		return t;
	}
}
/*****************************************************
 * parseTokens(Queue of Tokens, Set of Variables) 
 * Parses Tokens and evaluates them as an expression
 * 		State 0 : Ensures first token is proper value
 * 			- If first token is number -> Looks for Operator (s1)
 * 		 	- It is an undefined Identifier  -> Looks for assignment (s3)
 * 		
 * 		State 1 : Ensures token is Operator
 * 			- If it is an Operator -> s2 
 * 
 * 		State 2 : Ensures token is a Number
 * 			- Can exit here, or recive an Operation and go back to s1
 * 
 * 		State 3 : Ensures token is assingment operator
 * 			- If it is -> state s2

 * 
 ****************************************************/
void parseToke(TokenQueue* tokens, HashSet* set)
{
	int accum = 0; // value to be returned
	if (isEmpty(tokens))
	{
		printf("its empty");
		return;
	}

	/***********************************************************************
	 * State 0 - ensures first token is a number and assigns it to accum
	 ***********************************************************************/

	Token temp = dequeue(tokens);
	const char* type = tokenTypes[temp.type];
	const char* varName;
	int nextState;

	// If first token is neither NUMB nor IDEN, ends here
	if (strncmp(type, "NUMB", 3) != 0 && strncmp(type, "IDEN", 3) != 0)
	{
		printf("Error: Pybon can only evaluate expressions or assign values to variables at this time.\n");
		printf("\tExpression must start with either:\n");
		printf("1) A number to begin expression evaluation, or\n");
		printf("2) An undefined variable followed by an assignment to some value\n");
		return;
	}
	
	// If first token is IDEN, get value and replace temp with this
	if (strncmp(type, "IDEN", 3) == 0)
	{
		//print each value of set
		int hashIndex = hashCode(temp.data);
		if (set->array[hashIndex].data == NULL)
		{
			if (isEmpty(tokens))
			{
				printf("Error: identifier '%s' is not defined\n", temp.data);
				return;	
			}
			varName = temp.data;
			nextState = 3;
		}
		else
		{
			temp = getVal(&*set, temp.data);
			accum = atoi(temp.data);
			nextState = 1;
		}

	}
	else // (strncmp(type, "NUMB", 3) == 0)
	{
		accum = atoi(temp.data);
		nextState = 1;
	}

	if (isEmpty(tokens))
	{
		printf("%d\n", accum);
		return;
	}
	
	//loops through queue untill its gone through all tokens.
	char operation = 0;
	int assignAccumToVar = 0;
	while (!isEmpty(tokens))
	{

	/***********************************************************************
	 * State 1  - Ensures Number is followed by Operator
	 ***********************************************************************/ 
		
		if (nextState == 1)
		{
			Token temp = dequeue(tokens);
			const char* type = tokenTypes[temp.type];
			if (strncmp(type, "OPER", 3) != 0)
			{
				printf("ERROR: Every number must be followed by an Operator\n");
				return;
			}
				operation = *temp.data;
				nextState = 2;
		}
		/***********************************************************************
	 	* State 2  - Ensures Token is a number
	 	***********************************************************************/
		if (nextState == 2)
		{	
			if (isEmpty(tokens))
			{
				printf("ERROR: An operation must be followed by a number\n");
				return;
			}

			Token temp = dequeue(tokens);
			const char* type = tokenTypes[temp.type];

			if ((strncmp(type, "NUMB", 3) != 0 ) && strncmp(type, "IDEN", 3) != 0)
			{
				printf("ERROR: An operation must be followed by a number\n");
				return;	
			}

			int operand;
			if (strncmp(type, "IDEN", 3) == 0)
			{
				int hashIndex = hashCode(temp.data);
				if (set->array[hashIndex].data == NULL)
				{
					printf("Error: identifier '%s' is not defined\n", temp.data);
					return;
				}
				else
				{
					temp = getVal(&*set, temp.data);
					operand = atoi(temp.data);
				}
			}
			else // (strncmp(type, "NUMB", 3) == 0)
			{
				operand = atoi(temp.data);
			}

			accum = evaluate(accum, operation, operand);
			nextState = 1;
		}
		if (isEmpty(tokens))
		{
			printf("%d\n", accum);
			return;
		}
	/***********************************************************************
	 * State 3  - Ensures Assignment Operator
	 ***********************************************************************/		
		if (nextState == 3)
		{
			Token temp = dequeue(tokens);
			const char* type = tokenTypes[temp.type];

			if (isEmpty(tokens))
			{
				printf("Error: Identifier '%s' is not defined\n", temp.data);
				return;
			}

			if (strncmp(type, "ASGN", 3) != 0 )
			{
				printf("ERROR: Unable to evaluate unassigned identifier\n");
				return;	
			}			

			nextState = 4; 
		}
	/***********************************************************************
	 * State 4  - Creates token
	 ***********************************************************************/
		if (nextState == 4)
		{
			assignAccumToVar = TRUE;
			nextState = 2;
		}

		if (assignAccumToVar == TRUE)
		{
			Token temp = dequeue(tokens);
			const char* type = tokenTypes[temp.type];
			Token newVal = {temp.data, NUMB};
			Token* pToke = &newVal;
			addVal(&*set, varName, &*pToke);

			/*
			for (int i = 0; i < set->capacity; i++)
			{
				printf("%d: %s\n", i, set->array[i].data);
			}
			*/

			if (isEmpty(tokens))
				return;
			else
				nextState = 2;
		}
	}
}