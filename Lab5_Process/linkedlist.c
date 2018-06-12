#include<stdio.h>
#include<stdlib.h>
/* this is program to learn about linked list"*/

typedef struct node{
int data;
struct node *next;
} node; 

void main()
{

node *iterator, *first, *temp;

int count =0;

int choice =1;

first = 0;

while(choice)
{

iterator = (node *)malloc(sizeof(node)); 

printf( " Enter an integer to add to the list : "); 

scanf("%d", &iterator -> data);

	if(first !=0 )

	{

	temp->next = iterator;

	temp = iterator;

	}

	else
	{

	first = temp = iterator;

	}

printf( " Do you want to add more to the list? 1/0 : ");
scanf("%d",&choice);

}


temp -> next = 0;

temp = first; 


while(temp!=0 )
{

printf (" %d ", temp->data);

count++;

temp = temp->next ;

}


printf (" number of items in the list %d :", count);


}
