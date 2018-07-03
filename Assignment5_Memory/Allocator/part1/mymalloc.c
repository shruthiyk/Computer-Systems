#include <stdio.h> // Any other headers we need here
#include <malloc.h> // We bring in the old malloc function
#include <unistd.h>
#include <pthread.h>

// creating a struct called header to store the block information
// this is implemented as a linked list with *link pointing to the next block.
// using first-fit approach
// srbk() is the system call used to manipulate the pointer 'brk' that demarcates the end of  data segment , 
// where brk points to end of the heap 
//
//sbrk(0) gives current address of program break
//sbrk(x) increments the brk by x bytes
//sbrk(-x) decrements the brk by x bytes
//

// the struct header has the actual size of the memory, whether the block is free or not and the link to the next block 
// is_free is to check whether the block is free or not as the memory block here is cannot be allocated as a contiguous block

struct header_h{
size_t size;       
unsigned is_free;  
struct header_h *link;
};


struct header_h *head = NULL;
struct header_h *tail = NULL;

// to prevent threads from accessing a memory concurrenty we use a locking system 
// a global lock to lock the memory when acquired and to release when done 
pthread_mutex_t global_malloc_lock;


// to get a free block if it is free


struct header_h *get_block(size_t size)
{
struct header_h *current = head;

// traverse through the linked list to find whether a block marked as free exist
//  if yes whether the size meets the requirement and then we fetch block
while(current)
{
if( current->is_free && current->size >= size)
	return current;
	current = current->link;
}

return NULL;

}

// function to allocate the memory 

// this function allocates x size of memory and returns pointer to the allocated memory
void* mymalloc(size_t s){

//	void* p = (void*)malloc(s); 	// In your solution no calls to malloc should be made!
					// Determine how you will request memory :)


size_t total_size;
void *block;
struct header_h *header;

// check whether the size is valid

if(!s)
	return NULL;  // return null if size is zero

// else acquire the lock first 
pthread_mutex_lock(&global_malloc_lock);


// get the block after acquiring the lock 
header = get_block(s);



if(header)
{	

// if the block of memory found is large enough then mark it as not_free 

	header->is_free = 0;
	pthread_mutex_unlock(&global_malloc_lock);
	printf("Allocated %zu bytes\n",s);
	return(void*)(header + 1);
}



total_size = sizeof(struct header_h) + s;  // total size of the header and the memory block is calculated when a program requests for memory

block = sbrk(total_size);  // increment the program using sbrk()


// if error then unclock the block 
if(block == (void*) - 1)
{
	pthread_mutex_unlock(&global_malloc_lock);
	return NULL;
}

// fill the header with requested size 
header = block;
header->size = s;
header->is_free = 0;
header->link = NULL;


if(!head)
	head = header ;

if(tail)
	tail->link = header ;

tail = header ;


// release the global lock 
pthread_mutex_unlock(&global_malloc_lock);

printf("Allocated %zu bytes\n",s);


return (void*)(header + 1);  // the pointer to next block should be hidden about its existence. 
// hence it is type casted to void and returned 

// commented the intial code
//	if(!p){
		// We we are out of memory
		// if we get NULL back from malloc
//	}
//	printf("Allocated %zu bytes\n",s);
	
//	return p;   
//commented initial code	
}
	


void myfree(void *ptr){
//	printf("Freed some memory\n");
//	free(ptr);

// the program checks wheter the block that is freed is at the end of the heap, if yes release 
// else leave it as free to be used later 

size_t s;

struct header_h *header , *temp;

//
void *prgbrk;

if(!ptr)
	return;

	pthread_mutex_lock(&global_malloc_lock);

	header = (struct header_h*)ptr - 1; // get the header of the block of 

	prgbrk = sbrk(0);   // get the current value of the program break 

if((char*)ptr + header->size == prgbrk) // to check whether it is end of the heap and compare to the value of program break 
{

	if(head == tail)
	{
		head = tail = NULL;
	}
	else {

	temp = head ;

	while(temp)
	{	
		if(temp->link == tail)
		{
			temp->link = NULL ;
			tail = temp;
		}	

	temp = temp->link;
		}
	}

	printf("Freed %zu bytes\n", header->size);

	sbrk(0 - header->size - sizeof(struct header_h));  // calculate the amount to be released

       	pthread_mutex_unlock(&global_malloc_lock); //  unlock the block  and release 
 

	return;

}


	header->is_free = 1;  // if not end of heap just free the block 

	printf("Freed %zu bytes\n", header->size);

	pthread_mutex_unlock(&global_malloc_lock);

}
	
