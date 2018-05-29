#include<stdio.h>
#include<stdlib.h>

int main()
{

int n;
printf("Enter the size of the array\n");
scanf("%d",&n);

int *A= (int *)malloc(n*sizeof(int)*400);
A[20] = 10;
A[60] = 50;
A[100] =90;

printf("A[20] = %d\n A[60] = %d\n A[100]= %d\n",A[20],A[60],A[100]);

free(A);

return 0;
}
