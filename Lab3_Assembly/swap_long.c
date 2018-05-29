#include<stdio.h>
#include<stdlib.h>

// program to swap two integers

int main()
{
long a, b, c;
printf(" enter the values for a : ");
scanf("%lu",&a);
printf(" enter the values for b : ");
scanf("%lu",&b);
printf("The values are \n a: %li \n b: %li \n", a, b);

if(a != b )
{
c = a;
a = b;
b = c;

printf(" The values after swapping are\n a: %lu\n b: %lu\n", a, b); 

}

else 
printf( " Both the numbers are same , hence not swapped ");

return 0;
}

