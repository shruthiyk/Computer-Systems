#include<stdio.h>
int main(){


int i;
int s;
int e;

printf("Enter the starting number:");
scanf("%d",&s);

printf("Enter the ending number:");
scanf("%d", &e);

if (e<s)
{
printf("ending number should be greater than the starting number!");
}
else 
{

for (i=s ; i<=e; i++)
{

printf("%d\n ", i);

}

}

return 0;

}


