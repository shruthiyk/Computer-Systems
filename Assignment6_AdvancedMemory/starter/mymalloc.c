// file to submit

#define _GNU_SOURCE
#include<stdio.h> // Any other headers we need here
#include<malloc.h> // We bring in the old malloc function
#include<string.h>
#include<stdint.h>
#include<stdbool.h>
#include<errno.h>
#include<sys/mman.h>
#include<linux/mman.h>
#include<sched.h>
#include<unistd.h>
// making changes to implement advanced memory allocator using mmap

#define null 0
//
#define PAGE_SIZE (sysconf(_SC_PAGE_SIZE))
#define MIN_BLOCK_SIZE 32
#define MMAP_SIZE 1048576
#define GIVE_BACK_SIZE 33554432
#define ALLOC_SIZE 33445532
#define MERGE_ADJ_ON_REALLOC 1


// defining memory block structure, implelemted using doubly linked list

typedef struct memory_block_t {
	size_t size ;
	struct memory_block_t* prev;
	struct memory_block_t* next;
} memory_block;



// function to free the memory block Allocated

static memory_block freelist[] = { { 0, null, &(freelist[1])}, {0, &(freelist[0]), null} };
#define freelist_start (freelist[0].next)
#define freelist_begin (&(freelist[0]))
#define freelist_end (&(freelist[1]))


// heap

static memory_block* heap_start = null ;
static memory_block* heap_end= null;
static uint32_t heap_size;
static uint32_t mmap_size;


//mmap
#define is_mmap_block(b) (!(heap_start <= b && b < heap_end))
volatile bool locked = 0;



static inline void spinlock(){
	if(!__sync_bool_compare_and_swap(&locked,0,1)){
		int i=0;
		do{
			if(__sync_bool_compare_and_swap(&locked,0,1))
			break;
			else{
				if(i == 10)
				{
					i = 0 ;
					sched_yield();
				}else
				++i;
			}
		} while(1);
	}
}

#define lock spinlock();

#define unlock \
		__asm__ __volatile__ ("" ::: "memory");\
locked = 0;

// defining some more macros

#define byte_ptr(p) ((uint8_t*)p)
#define shift_ptr(p,s) (byte_ptr(p)+s)
#define shift_block_ptr(b,s) ((memory_block*)(shift_ptr(b,s)))
#define block_data(b) (shift_ptr(b,sizeof(size_t)))
#define data_block(p)(shift_block_ptr(p,-sizeof(size_t)))
#define block_end(b) (shift_block_ptr(b, b->size))

#define block_link(lb,rb) \
rb->prev = lb; \
lb->next = rb;

#define block_link_left(lb,b) \
block_link(b->prev,lb) \
block_link(lb,b)

#define block_link_right(b,rb) \
block_link(rb,b->next) \
block_link(b,rb)

#define block_unlink(b) \
block_link(b->prev,b->next)

#define block_unlink_right(b) \
block_unlink(b->next);

#define block_replace(b,nb) \
block_link(b->prev,nb) \
block_link(nb,b->next)







// add block to free list
static inline void add_block(memory_block* block){
	if(freelist_start != freelist_end){
		// find the superseeding block and replace it
		memory_block* b  = freelist_start;
		while(1)
		{
			if(b > block){
				block_link_left(block,b);
				break;
			}

				if(b->next == freelist_end){
					block_link_right(b,block);
					break;
				}
					else {
						b = b->next ;
					}
				}

				// merging adjacent blocks

				bool merged = true;
				while(merged)
				{
					// merge right end block
					if(block_end(block) == block->next)
					{
						block->size += block->next->size;
						block_unlink_right(block);
						continue;
					}

					if(block_end(block->prev) == block)
					{
						block = block->prev;
						block->size  += block->next->size;
						block_unlink_right(block);
						continue;
					}

					merged = false ;
				}
			}

			else {
				memory_block* b = freelist_begin;
				block_link_right(b,block);
			}
		}


		// split memory block into 2
		static inline memory_block* split_memory_block(memory_block* b ,size_t s)
		{
			size_t remainder = b->size - s ;
			if(remainder >= MIN_BLOCK_SIZE)
			{
				memory_block* nb = shift_block_ptr(b,s);
				nb->size = remainder;
				block_replace(b,nb);
				b->size = s;
			}
			else {
				block_unlink(b);
			}
			return b;
		}


		// finding optimal memory block size for size s
		static inline size_t find_optimal_memory_size(size_t s)
		{
			size_t suitable_size = MIN_BLOCK_SIZE;

			while(suitable_size < s)
			{
				suitable_size =suitable_size << 1;
			}

			return suitable_size;
		}


		// find suitable block
		static inline memory_block* find_suitable_block(size_t ns)
		{
			memory_block* b = freelist_start;
			while(b != freelist_end) {
				if(b->size >= ns){
					return split_memory_block(b,ns);
				}
				b = b->next;
			}
			return null;
		}


		// updating the mymalloc function
		void* mymalloc(size_t s){
			/*	void* p = (void*)malloc(s); 	// In your solution no calls to malloc should be made!
			// Determine how you will request memory :)

			if(!p){
			// We we are out of memory
			// if we get NULL back from malloc
		}
		printf("Allocated %zu bytes\n",s);

		return p;
		*/
		//modifying mymalloc function

		if(s == 0 )
		{
			return null;
		}
		s += sizeof(size_t);
		size_t ns = find_optimal_memory_size(s);

		if(ns >= MMAP_SIZE){
			void* m = mmap(NULL,s,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);
			if( m == MAP_FAILED)
						return null;
			memory_block* b = (memory_block*)m;
			b->size = s;
			lock
			mmap_size += s;
			unlock
			return block_data(b);
		}

		lock
		// find free memory block
		memory_block* block = find_suitable_block(ns);
		if(block != null){
			unlock
			return block_data(block);
		}
		// no free memory blocks found
		size_t pages_size = ((ns/PAGE_SIZE)+1)*PAGE_SIZE;
		if(pages_size < ALLOC_SIZE)
		pages_size = ALLOC_SIZE;
		// using sbrk to allocate memory

		void* p = sbrk(pages_size);
		if(p == (void*)-1){
			unlock
			return null;
		}

		block = (memory_block*)p;
		heap_size += pages_size;
		block->size = ns;

		heap_end = shift_block_ptr(block,pages_size);
		heap_start = shift_block_ptr(heap_end,-heap_size);
		ns = pages_size - ns;

		if(ns >= MIN_BLOCK_SIZE){
			memory_block* b = shift_block_ptr(block,block->size);
			b->size = ns;
			add_block(b);
		}
		unlock
		return block_data(block);
	}

	// end mymalloc function

	static inline memory_block* merge_with_adjacent_block(memory_block* block, size_t s){
		if(freelist_start == freelist_end)
		return null;

		memory_block* b = freelist_start;
		memory_block* be = block_end(block);

		do{
			// left adjacent
			if(block_end(b) == block)
			{
				if((b->size + block->size) >= s)	{
					size_t remainder = (b->size + block->size) - s ;
					memory_block* temp_prev = b->prev;
					memory_block* temp_next = b->next;
					memcpy(block_data(b), block_data(block),block->size - sizeof(size_t));
					if(remainder >= MIN_BLOCK_SIZE){
						b->size = s;
						memory_block* nb= shift_block_ptr(b,s);
						nb->size = remainder;
						block_link(temp_prev,nb);
						block_link(nb,temp_next);
					} else {
						block_link(temp_prev,temp_next);
					}
					return b;
				}
			}
			if(be == b)
			{
				if((block->size + b->size) >= s)
				{
					size_t remainder = (block->size + b->size) - s ;
					if(remainder >= MIN_BLOCK_SIZE){
						memory_block* nb = shift_block_ptr(block,s);
						nb->size = remainder;
						block_replace(b,nb);
						block->size = s;
					}
					else
					{
						block_unlink(b);
					}
					return block;
				}
				break;
			}
			b = b->next;
		}   while(b  != freelist_end && b >= be);
		return null;
	}


	// free function
	void myfree(void *p){
		//	printf("Freed some memory\n");
		//	free(ptr);
		if( p == null)
				return;
		memory_block* b = 	data_block(p);
		lock
		if(is_mmap_block(b)){
			mmap_size -= b->size;
			unlock
			munmap(b, b->size);
			return;
		}
		add_block(b);
		b = freelist_end->prev;
		if(block_end(b) == heap_end){
			intptr_t inc = b->size;
			if(inc >= GIVE_BACK_SIZE)
			{
				if(b == heap_start){
					if(inc > GIVE_BACK_SIZE){
						inc = inc - GIVE_BACK_SIZE;
						sbrk(-inc);
						b->size = GIVE_BACK_SIZE;
					}
				}else{
					block_unlink(b);
					sbrk(-inc);
					heap_size -= inc;
					heap_end = shift_block_ptr(heap_end, -inc);
					heap_start = shift_block_ptr(heap_end,-heap_size);
				}
			}
		}
		unlock
	}
