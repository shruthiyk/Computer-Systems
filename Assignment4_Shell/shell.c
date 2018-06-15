// Modify this file for your assignment
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>

#define READ_BUFFER_SIZE 80
#define TOKEN_BUFFER_SIZE 64
#define DELIMITERS " \t\n\a\r\v"


void sigint_handler(int sig)
{
	write(1,"mini-shell terminated\n",80);
	exit(0);
}

// function to read line/command entered by the user

char *read_line(void)
{
int buffer_size = READ_BUFFER_SIZE;
int position = 0; 
int character;
char *r_buffer  = malloc(sizeof(char) * buffer_size);

	if(!r_buffer)
	{	
		fprintf(stderr,"memory allocation error\n");
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
	buffer_size += READ_BUFFER_SIZE;
	r_buffer = realloc(r_buffer, buffer_size);
	if(!r_buffer)
		{
			fprintf(stderr," memory allocation error\n");
			exit(EXIT_FAILURE);	
		}
	}
	}
}


// function to parse the line 

char **parse( char *line)
{
int buffer_size = TOKEN_BUFFER_SIZE;
int position = 0;
char *token;
char **t_size = malloc(buffer_size * sizeof(char*));

	if(!t_size)
	{
	fprintf(stderr,"memory allocation error\n");
	exit(EXIT_FAILURE);
	}

	token = strtok(line, DELIMITERS);
	while(token != NULL)
	{	
	t_size[position] = token;
	position++;

	if(position >= buffer_size)
        {
        buffer_size += TOKEN_BUFFER_SIZE;
        t_size = realloc(t_size, buffer_size * sizeof(char*));
        if(!t_size)
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


// function to start the process

int launch(char **args)
{
pid_t pid, wpid;

int status;

pid = fork();
if(pid == 0)
{
	// child process
	if (execvp(args[0],args) == -1 )
	{
	perror("error");
	}

	exit(EXIT_FAILURE);
}

else if(pid < 0)
	{
		perror("error");
	}

else {
	do {
 	wpid= waitpid(pid,&status,WUNTRACED);
	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}

return 1;
}


// builtin functions 

int cd(char **args);
int help(char **args);
int shell_exit(char **args);


char *builtin_str[] = {
"cd", 
"help",
"exit"
};


int (*builtin_func[])(char **) = {
&cd,
&help,
&exit
};

int num_builtins() {
	return sizeof(builtin_str) / sizeof(char *);
}

// function for cd 

int cd(char **args)
{

if(args[1] == NULL )
{
	printf(" error \n ");
}

else {

if(chdir(args[1]) != 0)
{

	perror(" error");
}
}

return 1;

}



// function for help
int help(char **args)
{
int i;
printf(" following are the builtin commands");
for (i = 0; i< num_builtins() ; i++)
{

	printf("%s\n",builtin_str[i]);

}

printf(" see the man page for more information\n");
return 1;

}

// function for exit 


int shell_exit(char **args)
{

	return 0;


}

// execute function 

int execute(char **args)
{

int i;
if(args[0] == NULL )
{
        return 1;

}

for ( i = 0;i < num_builtins(); i++) {
if (strcmp(args[0], builtin_str[i]) == 0)
{

        return(*builtin_func[i])(args);

}

}

        return launch(args);

}


// function for continous loop


void loop()
{
char *line;
char **args;
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


int main (int agrc , char **argv)
{

// run an repl loop ie. read, evaluate, parse and loop again
	loop();

return 0;
}
