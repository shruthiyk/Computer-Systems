// Modify this file for your assignment
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define READ_BUFFER_SIZE 80
#define TOKEN_BUFFER_SIZE 64
#define DELIMITERS "\t\n\a\r\v"


// function to read line/command entered by the user

char* read (void)
{
int buffer_size = READ_BUFFER_SIZE;
int position = 0; 
int character;
char *r_buffer  = malloc(sizeof(char) * buffer_size);

	if(!r_buffer)
	{	
		printf("memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	
	// loop through to read each character 
	while(1)
	{
		character = getchar();

		if( character == EOF || character == '\n')
		{		

		r_buffer[position] = '\0';
		return r_buffer;
		}

		else {
		r_buffer[position] = character ;
		}
 	position++;



	if(position >= buffer_size)
	{
	buffer_size+=READ_BUFFER_SIZE;
	r_buffer = realloc(r_buffer, buffer_size);
	if(!r_buffer)
		{
			printf(" memory allocation error\n");
			exit(EXIT_FAILURE);	
		}
	}
	}
}


// function to parse the line 

char **parse( char* line)
{
int buffer_size = TOKEN_BUFFER_SIZE;
int position = 0;
char *token;
char **t_size = malloc(buffer_size* sizeof(char*));

	if(!token_size)
	{
	printf("memory allocation error\n");
	exit(EXIT_FAILURE);
	}

	token = strtok(line, DELIMITERS);
	while(token!=NULL)
	{	
	t_size[position] = token;
	position++;

	if(position >= buffer_size)
        {
        buffer_size+=TOKEN_BUFFER_SIZE;
        t_buffer = realloc(t_buffer, buffer_size);
        if(!t_buffer)
                {
                        printf(" memory allocation error\n");
                        exit(EXIT_FAILURE);
                }
        }


	token = strtok(NULL,TOKEN_BUFFER_SIZE);
        }

	t_size[position] = NULL ;
	return t_size;
}


// functions to execute the command entered by the user 






int execute(char **args)
{

pid_t pid;
pid_w ;
int status;


pid= fork();
	if(pid == 0)
	{		
	if(execvp(args[0],args) == -1)
	{
	perror("error");
	}
	exit(EXIT_FAILURE);
	}  
	else if (pid < 0)
	{
	perror("error");
	}

	else {
 
	do {

		w_pid = waitpid(pid, &status, WUNTRACED);
	   }

	while (!WIFEXITED(status) && !WIFSIGNALED(status));
	} 

	return 1;
}


}
}





void loop()
{
char* line;
char** args;
int state;

// read the commands entered by the user 
// it will parse the commands computer can understand and execute the command

do {
	printf("mini-shell>");

// read each line i.e the command that is typed in by the user

	line = read_line();

// agrs is an array of strings 

	args = parse(line);

//to execute and return the state of the system

	state =execute(args);

// free the memory allocated 

	free(line);
	free(args);

} while(state);
}


int main (int agrc , char** argv)
{

// run an repl loop ie. read, evaluate, parse and loop again
	loop();

return 0;
}
