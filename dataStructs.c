
#include "dataStructs.h"

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