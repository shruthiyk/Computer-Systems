// Implement a working parser in this file that splits text into individual tokens.

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{

char str[100]; // = "hello-hi-heu";
printf(" Enter any string: ");
scanf("%[^\n]%*c",str);
char *token =  strtok(str,"-");

	while(token!= NULL)
	{	
	printf("%s\n", token);
	token = strtok(NULL,"-");
	}

return 0;

}




