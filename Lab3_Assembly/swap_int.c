#include<stdio.h>
#include<stdlib.h>

// program to swap two integers

int main()
{
int a, b, c;
printf(" enter the values for a : ");
scanf("%d",&a);
printf(" enter the values for b : ");
scanf("%d",&b);
printf("The values are \n a: %d \n b: %d \n", a, b);

if(a != b )
{
c = a;
a = b;
b = c;

printf(" The values after swapping are\n a: %d\n b: %d\n", a, b); 

}

else 
printf( " Both the numbers are same , hence not swapped ");

return 0;
}

