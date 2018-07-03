#include <stdio.h> // Any other headers we need here
#include <malloc.h> // We bring in the old malloc function
#include <unistd.h>
#include <pthread.h>

// creating a struct called header to store the block information
// this is implemented as a linked list with *link pointing to the next block.
// using first-fit approach


struct header_h{
size_t size;       
unsigned is_free;  // to check whether the next block is free or not
struct header_h *link;
};

struct header_h *head = NULL;
struct header_h *tail = NULL;

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

void* mymalloc(size_t s){

//	void* p = (void*)malloc(s); 	// In your solution no calls to malloc should be made!
					// Determine how you will request memory :)


size_t total_size;
void *block;
struct header_h *header;
if(!s)
	return NULL;
pthread_mutex_lock(&global_malloc_lock);
header = get_block(s);
if(header)
{	
	header->is_free = 0;
	pthread_mutex_unlock(&global_malloc_lock);
	printf("Allocated %zu bytes\n",s);
	return(void*)(header + 1);
}

total_size = sizeof(struct header_h) + s;
block = sbrk(total_size);
if(block == (void*) - 1)
{
	pthread_mutex_unlock(&global_malloc_lock);
	return NULL;
}


header = block;
header->size = s;
header->is_free = 0;
header->link = NULL;


if(!head)
	head = header ;

if(tail)
	tail->link = header ;

tail = header ;

pthread_mutex_unlock(&global_malloc_lock);

printf("Allocated %zu bytes\n",s);


return (void*)(header + 1);
//	if(!p){
		// We we are out of memory
		// if we get NULL back from malloc
//	}
//	printf("Allocated %zu bytes\n",s);
	
//	return p;
}
	
void myfree(void *ptr){
//	printf("Freed some memory\n");
//	free(ptr);

size_t s;

struct header_h *header , *temp;

void *prgbrk;

if(!ptr)
	return;

pthread_mutex_lock(&global_malloc_lock);

header = (struct header_h*)ptr - 1;

prgbrk = sbrk(0);

if((char*)ptr + header->size == prgbrk)

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

	sbrk(0 - header->size - sizeof(struct header_h));

	pthread_mutex_unlock(&global_malloc_lock);

	printf("Free %zu bytes\n", header->size);

	return;

}


	header->is_free = 1;

	printf("Freed %zu bytes\n", header->size);

	pthread_mutex_unlock(&global_malloc_lock);

}
	
