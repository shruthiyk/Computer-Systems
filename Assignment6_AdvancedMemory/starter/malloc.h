#ifndef MYMALLOC_H
#define MYMALLOC_H

#define malloc(size) mymalloc(size)
#define free(ptr) myfree(ptr)

#include<unistd.h>

void *mymalloc(size_t size);
void myfree(void *ptr);

#endif

