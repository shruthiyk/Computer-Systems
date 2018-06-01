#include <stdio.h>
#include <time.h>

int i=0;
clock_t t=0;

__attribute__((no_instrument_function))
void __cyg_profile_func_enter(void *this_fn, void *call_site){

	printf("Function entered\n");

	i++;
	printf("# of times function has been called: %d, fn = %p, caller = %p\n", i, this_fn, call_site);
	t = clock();
}

__attribute__((no_instrument_function))
void __cyg_profile_func_exit(void *this_fn, void *call_site){

	printf("Function exited\n");

	t = clock() - t;
    double time_diff = ((double)t)/CLOCKS_PER_SEC; // in seconds
 
    printf("Function cost us: %f seconds to execute \n", time_diff);
}

