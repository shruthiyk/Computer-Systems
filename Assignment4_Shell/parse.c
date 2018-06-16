// Implement a working parser in this file that splits text into individual tokens.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>

#define DELIMITERS " |\n"

char *read_line(void)
{

char *line = NULL; 

size_t buffer_size = 0;

getline(&line,&buffer_size ,stdin);

return line;

}

int main (int agrc , char **argv)
{

char *line;
char *token;

printf(" Enter any string or set of strings/characters: \n ");
//printf("Hello World\n");
line = read_line();
//printf("Line is %s\n", line);
token = strtok(line, DELIMITERS);

while(token != NULL)
{
        printf(" %s\n", token);
        token=strtok(NULL,DELIMITERS);
}

//return 0;
}













