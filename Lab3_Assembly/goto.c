#include<stdio.h>
#include<stdlib.h>


// this is a program to implement goto in C


int main()
{

int x = 100 ;

	LOOP:do {

	if (x == 10){

	x = x / 5;

	goto LOOP;

	}

	printf(" value is %d\n", x);
	
	x--;

	}while (x > 1);

return 0;
}


