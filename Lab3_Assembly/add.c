#include<stdio.h>
#include<stdlib.h>

long add( long a , long b)
{

long sum = a + b ;
//printf(" Sum is %li\n", sum);
return sum;
}


int main()
{

long a , b; 

/*printf(" enter the value for a : \n ");
scanf("%li", &a);
printf(" enter the value for b : \n ");
scanf("%li", &b);
*/
a = 20;
b = 30;

add(a,b);

return 0;

}

