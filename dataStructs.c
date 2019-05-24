
#include "dataStructs.h"

//Testing for getVal()
/**
int main()
{

HashSet* set = init_HashSet(97);
printf("Hash set\n");
Token first = {"499", NUMB};
Token* pToke1 = &first;
addVal(&*set, "var1", &*pToke1);

 * 
*/
/*
//Token second = getVal(set, "var1");
Token second = {"788", NUMB};
Token* pToke2 = &second;
addVal(&*set, "another", &*pToke2);

Token new = getVal(&*set, "var1");

return 0;
}
*/

/************************************************
 *  HashSet Functions
 * **********************************************/

HashSet* init_HashSet(unsigned capacity)
{
    HashSet* set = malloc(sizeof(HashSet));
    set->capacity = capacity;
    set->size = 0;
    set->array = malloc(capacity * sizeof(Token));
    return set;
}

int hashCode(const char* string)
{
    int accum = 1;
    for (int i = 0; i < strlen(string); i++)
    {
        accum = accum + 23 + (string[i] - '0');
        i++;
    }
    return accum % 97;
}

Token getVal(HashSet* set, char* key)
{
    int hashIndex = hashCode(key);
    Token* token = malloc(sizeof(Token));
    *token = set->array[hashIndex];
    return *token;
    
}

void addVal(HashSet* set, const char* key, Token* token)
{
    int hashIndex = hashCode(key);
    set->array[hashIndex] = *token;
    set->size++;
}

/*
int main()
{
	//Token token = {"499", NUMB};
    //printf("This token is %s\n", token.data);
    //int hashIndex = hashCode(token.data);
    //printf("%d\n", hashIndex);
    
    HashSet set;
    char* ident = "test";
    Token token = {"499", NUMB};
    addVal(&set, ident, token);
    Token token2 = getVal(set, ident);
    printf("%s\n", token2.data);

    return 0;
}
*/

/************************************************
 *  Queue Functions
 * **********************************************/

// Function to create a queue of given capacity.  
// It initializes size of queue as 0 
struct TokenQueue* createTokenQueue(unsigned capacity) 
{ 
    struct TokenQueue* queue = (TokenQueue*) malloc(sizeof(TokenQueue)); 
    queue->capacity = capacity; 
    queue->front = queue->size = 0;  
    queue->rear = capacity - 1;  // This is important, see the enqueue 
    queue->array = malloc(queue->capacity * sizeof(Token)); 
    return queue; 
} 
  
// Queue is full when size becomes equal to the capacity  
int isFull(struct TokenQueue* queue) 
{  return (queue->size == queue->capacity);  } 
  
// Queue is empty when size is 0 
int isEmpty(struct TokenQueue* queue) 
{  return (queue->size == 0); } 
  
// Function to add an item to the queue.   
// It changes rear and size 
void enqueue(struct TokenQueue* queue, struct Token token) 
{ 
    //if (isFull(queue)) 
        //printf("Queue is full\n"); 
    queue->rear = (queue->rear + 1)%queue->capacity; 
    queue->array[queue->rear] = token; 
    queue->size = queue->size + 1; 
} 
  
// Function to remove an item from queue.  
// It changes front and size 
struct Token dequeue(struct TokenQueue* queue) 
{ 
    //if (isEmpty(queue)) 
        //printf("Cant dequeue an empty Queue\n");
    struct Token token = queue->array[queue->front]; 
    queue->front = (queue->front + 1)%queue->capacity; 
    queue->size = queue->size - 1; 
    //printf("%s dequeued from queue\n ", token.data);
    return token; 
} 
  
// Function to get front of queue 
struct Token front(struct TokenQueue* queue) 
{ 
    //if (isEmpty(queue)) 
        //printf("Cant front an empty Queue\n"); 
    return queue->array[queue->front]; 
} 
  
// Function to get rear of queue 
struct Token rear(struct TokenQueue* queue) 
{ 
    //if (isEmpty(queue)) 
        //printf("Cant rear an empty Queue\n");
    return queue->array[queue->rear]; 
}