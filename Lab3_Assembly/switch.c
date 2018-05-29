#include<stdio.h>
#include<stdlib.h>

int main()
{

int n , a ,b ,c;

printf(" Enter the numbers : a\n ");
scanf("%d", &a);
printf(" Enter the numbers : b\n ");
scanf("%d", &b);

printf(" 1: Add 2: Sub 3: Mul 4:Div \n");
printf(" Enter any option : \n ");
scanf("%d", &n);

switch(n)
{

case 1: c = a + b;
	printf(" Sum is %d \n", c);
	break;
	
case 2: c = a - b;
	printf(" Sub is %d \n", c);
	break;
	
case 3: c = a * b;
	printf(" Mul is %d \n", c);
	break;

case 4: c = a / b;
	printf(" Div is %d \n", c);
	break;
	
default : printf( " enter one among the options only");
break;
}


return 0;
}
