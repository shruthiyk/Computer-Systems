// gcc -std=c99 -fopenmp omp5.c -o omp5
// You fill in
#include<stdio.h>
#include<omp.h>

// example to know data share between threads 
int main()
{

int a, b= 0;
#pragma omp parallel for private(a) shared(b)
for(a = 0; a<50;++a)
{
 #pragma omp atomic 
  b +=a;
}

printf (" b is %d\n", b);

}
