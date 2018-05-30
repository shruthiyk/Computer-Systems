#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

int i=0;
int64_t start=0;

int64_t timestamp()
{

	struct timeval t;
	gettimeofday(&t , NULL);
	return (int64_t) t.tv_sec * CLOCKS_PER_SEC + t.tv_usec;
}

double timestamp_to_sec(int64_t time)
{
	return time / (double) CLOCKS_PER_SEC;
}


__attribute__((no_instrument_function))
void __cyg_profile_func_enter(void *this_fn, void *call_site){

	printf("Function entered\n");

	i++;
	printf("Number of times this function has been called %d \n", i);
	start = timestamp();

}

__attribute__((no_instrument_function))
void __cyg_profile_func_exit(void *this_fn, void *call_site){

	printf("Function exited\n");
	printf("Function cost us: %f seconds\n", timestamp_to_sec(timestamp()-start)); 
	
}

