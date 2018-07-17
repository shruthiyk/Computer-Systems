// gcc -std=c99 -fopenmp omp1.c -o omp1
// You fill in

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) 
{
int nthreads, tid, procs, maxt, inpar, dynamic, nested;
#pragma omp parallel private(nthreads, tid)
  {
  tid = omp_get_thread_num();

  if (tid == 0) 
    {
    printf("Main thread displaying the environment info\n", tid);

    procs = omp_get_num_procs();
    nthreads = omp_get_num_threads();
    maxt = omp_get_max_threads();
    inpar = omp_in_parallel();
    dynamic = omp_get_dynamic();
    nested = omp_get_nested();

    printf("Processor count= %d\n", procs);
    printf("Thread count = %d\n", nthreads);
    printf("Maximum thread count = %d\n", maxt);
    printf("Parallelism Enabled? = %d\n", inpar);
    printf("Dynamism Enabled? = %d\n", dynamic);
    printf("Nested Parallelism Enabled? = %d\n", nested);
    }
  }
}

// gcc -std=c99 -fopenmp omp4.c -o omp4
// You fill in
