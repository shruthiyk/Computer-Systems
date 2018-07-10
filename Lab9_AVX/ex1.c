// For this exercise, you are going to read in data from a file called 'data.txt'
// Increment all of the values by 1.
// 
// You will compile this source using the following:
// 
// clang -std=c11 -mavx2 ex1.c -o ex1prog
//
// Run as normal with: 
// 
// ./exx1prog
//
#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include <immintrin.h>

// global variables 

int a[8];
int b[8];
int c[8];
int d[8];
int array0[32] = {0};
int i = 0;
int j;

// print
void print__m256(__m256i data){
	int*f = (int*)&data;
	printf("%d %d %d %d %d %d %d %d\n", f[0],f[1],f[2],f[3],f[4],f[5],f[6],f[7]);
	
}

int main()
{

	__m256 one = _mm256_set1_epi32(1);

	FILE *ptr = fopen("data.txt","r");
	if(ptr == NULL)
	{
		printf(" no such file in the directory");
		return 0;
	}

	while(fscanf(ptr,"%d",&array0[i]) != EOF)
	{ 	
		++i;

	}

	//printf("a[0] to a[7]\n");
	for( j = 0; j<8; j++)
	{
	//	printf("%d\n", array0[j]);
		a[j] = array0[j];
		
	}


	__m256 two = _mm256_set_epi32(a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7]);
	__m256i data = _mm256_add_epi32(two, one);
	//printf("Incremented values\n");
	print__m256(data);

	//printf("b[0] to b[7]\n");
	for( j = 8; j<16; j++)
	{
	//	printf("%d\n", array0[j]);
	        b[j-8]  = array0[j];
		
	}
		
	__m256 three = _mm256_set_epi32(b[0],b[1],b[2],b[3],b[4],b[5],b[6],b[7]);
	__m256i data1 = _mm256_add_epi32(three, one);
	//printf("Incremented values\n");
	print__m256(data1);

	//printf("c[0] to c[7]\n");
	for( j = 16; j<24; j++)
	{
	//	printf("%d\n", array0[j]);
		c[j-16] = array0[j];
		
	}
	
	__m256 four = _mm256_set_epi32(c[0],c[1],c[2],c[3],c[4],c[5],c[6],c[7]);
	__m256i data2 = _mm256_add_epi32(four, one);
	//printf("Incremented values\n");
	print__m256(data2);
	

	//printf("d[0] to d[7]\n ");

	for( j = 24; j<32; j++)
	{
	//	printf(" %d\n", array0[j]);
		d[j-24] = array0[j];
		
	}

	__m256 five = _mm256_set_epi32(d[0],d[1],d[2],d[3],d[4],d[5],d[6],d[7]);
	__m256i data3 = _mm256_add_epi32(five, one);
	//printf("Incremented values\n");
	print__m256(data3);

	fclose(ptr);	
	
return 0;

}

