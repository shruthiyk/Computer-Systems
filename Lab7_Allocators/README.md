# Allocators

In this lab, you are going to start getting familiar with some of the tools used to implement allocators. 

Remember, part of this class is building a concrete mental model of what is really going on inside of a machine (So that there is "no more magic" when you see a computer running). We have looked at how memory is managed by the operating system and hardware, launching processes (with fork and exec), understanding a processes memory spaces, and now allocating memory--we are getting very low level!

## Setup

This lab has been tested to run on `login.ccs.neu.edu`. You should do a `git pull` on the ccis servers.

## Background Reading on Memory Allocators

Take a moment to read the Cexcerpt.pdf (2 pages ~5 minutes reading) to get a basic understanding of how allocators work. 

**Discuss** with your partner and write why you think `typedef long Align` was used. 

**Write a 1-2 sentence answer here:**
When we use malloc, we have to ensure that the storage returned is aligned properly for the objects to be stored in it, that is, that datatypes of certain sizes are stored at addresses of similar sizes. Some machines have the restrictive data type as int or long. By defining an union that consists of the head structure and the Align type, we are forcing the alignment on the basis of long as a worst-case boundary.


## Allocator building blocks

A few of the key system calls that we will need to understand are the following (My professors use to always say "read the man pages", so I will echo that in honor of them).

* Type in `man sbrk` in the terminal. Read the description of what sbrk does .

```
BRK(2)                                                       Linux Programmer's Manual                                                      BRK(2)

NAME
       brk, sbrk - change data segment size

```

* Type in `man mmap` in the terminal next.

```
MMAP(2)                                                          Linux Programmer's Manual                                                         MMAP(2)

NAME
       mmap, munmap - map or unmap files or devices into memory
```

* Type in `man mlock` next.

```
MLOCK(2)                                                         Linux Programmer's Manual                                                        MLOCK(2)

NAME
       mlock, mlock2, munlock, mlockall, munlockall - lock and unlock memory
```

What do you think mlock is good for? This article discusses some of the tradeoffs nicely: https://eklitzke.org/mlock-and-mlockall

**Discuss** with your partner.

**Write a 1-2 sentence answer here:**
mlock() is used to lock one or more pages of memory into the RAM, preventing that memory from being swapped. One of the use cases for using mlock or mlockall (this locks all the pages of the memory to the RAM), as described in the link above is to lock sensitive decrypted data or passwords in memory. One extra example that I could think of where mlock might be used would be when we do a 'sudo' command. Once we perform a sudo command and provide the password once, we are not requested for the password if we do another 'sudo' command. It leads me to believe that the page containing the password might have been locked in memory for a certain period of time after we first provide it. 

Similarly, mlock can be used to lock any page that might be deemed useful by us for a process. But the drawbacks are that we might not necessarily know which page has what information. So, we could use the mlockall() function. This would lock all the pages to memory. This too has a major drawback in the sense that these pages will not be able to be swapped and some other process's pages might be swapped our, hindering it's work, and making the process slow. 

While mlock and mlockall have their advantages, their usage and consequences after usage must be considered before implementation

### The simplest memory allocator

We can actually write a very simple implementation of a memory allocator. The allocator below just gives us however many bytes of memory we request. 

```

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void *malloc(size_t size) {
  void *ptr = sbrk(0);
  void *request = sbrk(size);
  if (request == (void*) -1) {
    return NULL; 
  }
  
  return ptr;
}

int main(){

	// Memory leak! But why?
	malloc(8);

	return 0;
}


```

However, the problem with this allocator is that we do not have any notion over where that memory is. We also do not really know how much memory needs to be freed(or rather, could be reused rather than asking for more memory). This means we need some sort of data structure to keep track of our heap size.

**Discuss** with your partner what data structures you might use to keep track of memory. Record at least one below, but try to think of at least two in your discussion.

**Write a 1-2 sentence answer here:**
We could store the dynamically allocated memory in the form of a structure as below

struct dynaMemory
{
    void* address;   // This will hold the address of the first block allocated
    int blocks;          // This will be the number of blocks that we requested to be allocated
    int sizeOfBlock; // We can use this to see the size of each block (int/ char/ long ) etc
    int free;              // We can keep track of how many blocks were unused using this
    int allocated;      // We can keep track of how many blocks are used using this
    void* nextFree;  // We can store a pointer to the next block that is unused using this pointer.
}

We would just have to create an object of the above structure and assign it the necessary information during allocation. This can be done by writing a function which allocates memory based on the user's request and returns an object of this structure with the necessary details assigned to it 

## Lab Deliverable

1. Fill in the 3 discussion points above in the appropriate spaces.

## More Resources to Help

N/A

## Going Further

* Take a look at malloc.c. You can skim around and read some of the comments to see how the libc library performs memory allocation!
  * https://code.woboq.org/userspace/glibc/malloc/malloc.c.html
