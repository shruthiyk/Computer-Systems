// gcc -std=c99 -fopenmp omp3.c -o omp3
// You fill in
#include<stdio.h>
#include<omp.h>


// example for reduction clause 
// to compute factorial 

int factorial (int number)
{

int fac = 1; 
#pragma omp parallel for reduction(*:fac)
for( int n = 2;  n<= number; ++n)
  	fac*=n;
	return fac;
}


int main()
{

int number = factorial (4);
printf("factorial is %d : ", number);
return 0;

}
