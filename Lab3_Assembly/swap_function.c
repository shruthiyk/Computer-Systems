#include<stdio.h>
#include<stdlib.h>

int swap(int a, int b)
{

int c; 
c = a ;
a = b ;
b = c ;

printf("numbers after swapping are \n a : %d\n b : %d\n",a,b);
return 0;

}

void main()
{

int a, b;
printf("This is a program to swap two numbers :\n");

printf("Enter value for a : \n ");
scanf("%d", &a);
printf("Enter value for b : \n ");
scanf("%d", &b);

swap(a,b);

}
  

