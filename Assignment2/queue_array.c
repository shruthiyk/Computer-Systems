// =================== Support Code =================
// Queue
//
// - Implement each of the functions.
// - Do not change any of the function declarations
//   - (i.e. queue_t* create_queue(unsigned int _capacity) should not have additional arguments)  
// ==================================================
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// The main data structure for the queue
struct queue{
	unsigned int back;	    // The next free position in the queue
				                  // (i.e. the end or tail of the line)
	unsigned int front;	    // Current 'head' of the queue
				                  // (i.e. the front or head of the line)
	unsigned int size;	    // How many total elements we have enqueued.
	unsigned int capacity;  // Number of items the queue can hold
	int* data; 		          // The 'integer' data our queue holds	
};
// Creates a global definition of 'queue_t' so we 
// do not have to retype 'struct queue' everywhere.
typedef struct queue queue_t;

// Create a queue
// Returns a pointer to a newly created queue.
// The queue should be initialized with data on
// the heap.
queue_t* create_queue(unsigned int _capacity){
	queue_t* myQueue = NULL;

	return myQueue;
}

// Queue Empty
// Check if the queue is empty
// Returns 1 if true (The queue is completely empty)
// Returns 0 if false (the queue has more space available)
int queue_empty(queue_t* q){

	return 0;
}

// Queue Full
// Check if the queue is Full
// Returns 1 if true (The queue is completely full)
// Returns 0 if false (the queue has more space available)
int queue_full(queue_t* q){

	return 0;
}

// Enqueue a new item
// i.e. push a new queue into our data structure
// Returns a -1 if the operation fails (otherwise returns 0 on success).
// (i.e. the queue is full).
int queue_enqueue(queue_t *q, int item){
		return -1;
}

// Dequeue an item
// Returns the item at the front of the queue and
// removes an item from the queue.
int queue_dequeue(queue_t *q){

		return -1;
}


// Queue Size
// Queries the current size of a queue
// A queue that has not been previously created will crash the program.
// (i.e. A NULL q cannot return the size.)
unsigned int queue_size(queue_t* q){
	return 0;
}


// Free queue
// Removes a queue and all of its elements from memory.
// This should be called before the proram terminates.
void free_queue(queue_t* q){

}


// A sample test of your program
// You can add as many unit tests as you like
// We will be adding our own to test your program.
void unitTest1(){

	queue_t* test1 = create_queue(1);
	printf("Attempting to add %d\n",1);
	queue_enqueue(test1,1);	
	printf("Removing: %d\n",queue_dequeue(test1));	

	free_queue(test1);
}


// ====================================================
// ================== Program Entry ===================
// ====================================================
int main(){

	// List of Unit Tests to test your data structure	
	unitTest1();

	return 0;
}
