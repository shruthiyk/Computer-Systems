// gcc -std=c99 -fopenmp omp2.c -o omp2
// You fill in
#include<stdio.h>
#include<omp.h>


int main()
{

	int threads = 50 ; 
	int id ;

	#pragma omp parallel 
	{
		threads = omp_get_num_threads();  // this gives the number of threads in the team
		id = omp_get_thread_num();   // give the thread id 
		
		#pragma omp for 
		for( int n=0 ; n<10 ; ++n )
		{
		printf (" thread id is %d \n", id);
		}
	
	}

return 0;
}
