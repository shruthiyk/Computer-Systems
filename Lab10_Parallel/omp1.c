// gcc -std=c99 -fopenmp omp1.c -o omp1
// You fill in
#include<omp.h>
#include<stdio.h>

int main()
{
	int threads = 50 ; 
	int id ;
	#pragma omp parallel 
	{
		threads = omp_get_num_threads();  // this gives the number of threads in the team
		id = omp_get_thread_num();   // give the thread id 
		printf (" this is thread %d from %d threads \n", id, threads);
	}
return 0;
}
