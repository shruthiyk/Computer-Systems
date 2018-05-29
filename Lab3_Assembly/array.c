#include<stdio.h>
#include<stdlib.h>

int main()
{
static int myArray[400];


int i = myArray[10] = 20;
int j = myArray[40] = 40;
int e = myArray[401] = 0;

printf("The array elements are : \n ");

printf(" %d\n " , i);
printf(" %d\n " , j);
printf(" %d\n " , e);

return 0;
}
