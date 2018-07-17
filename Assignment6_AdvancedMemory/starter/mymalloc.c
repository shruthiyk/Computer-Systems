#include <stdio.h> // Any other headers we need here
#include <malloc.h> // We bring in the old malloc function


void* mymalloc(size_t s){

	void* p = (void*)malloc(s); 	// In your solution no calls to malloc should be made!
					// Determine how you will request memory :)

	if(!p){
		// We we are out of memory
		// if we get NULL back from malloc
	}
	printf("Allocated %zu bytes\n",s);
	
	return p;
}
	
void myfree(void *ptr){
	printf("Freed some memory\n");
	free(ptr);
}
	
