// Modify this file for your assignment
// program to implement a mini shell

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>

#define READ_BUFFER_SIZE 80    // macro to limit the input size of the shell to 80
#define TOKEN_BUFFER_SIZE 64
#define DELIMITERS " &\n"   //macro to define & in order to run the program in background when the user specifies "&" in the input command
#define PIPE "|"   // macro to define pipe as delimiter 
#define WRITE_END 1 
#define READ_END 0
#define REDIRECTION1 <
#define REDIRECTION2 >


// function for signal handling( to identify Ctrl+C as an interrupt to exit the mini-shell
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
 	position++;    // increment after reading each character 


	// if position crosses the buffer limit , show memory allocation error
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

	token = strtok(line, DELIMITERS);   // strtok to check for the delimiter and to remove them 

	// execute while token is not null yet
	while(token != NULL)
	{

	t_size[position] = token;
	position++;

	// check whether token buffer size crosses the specified limit
	if(position >= buffer_size)
        {

        buffer_size += TOKEN_BUFFER_SIZE;
        t_size = realloc(t_size, buffer_size * sizeof(char*));

        if(!t_size)
                {
                        printf("memory allocation error\n");
                        exit(EXIT_FAILURE);
                }
        }

	token = strtok(NULL,DELIMITERS);
        }

	t_size[position] = NULL ;
	return t_size;
}

// function to find pipe 
// and return 1 if pipe is found , else 0 if not  to check for pipe in execute function

int find_pipe(char* line , char **line_piped)
{
int i;
for (i=0 ; i<2 ; i ++)
{
	line_piped[i] = strsep(&line , "|");   // strsep to  extract token "|" from the line 
	if (line_piped == NULL){
		break;
	}
}

if (line_piped[1] == NULL ){

	return 0;   // return zero if pipe is not found 
}else{

	return 1;

	}
}


// function to start the process

int launch(char **args, int last_char_is_amp_and)
{
pid_t pid, wpid;

int status;

pid = fork();
if(pid == 0)
{
	if(last_char_is_amp_and){
		
		setpgid(pid, 0);
	}
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
	

	// Background Process Checking
	if(last_char_is_amp_and == 0){
		// If last character is not ampersand then the parent will wait
		do {
 			wpid= waitpid(pid,&status,WUNTRACED);
		   } while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
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
"exit",
};


int (*builtin_func[])(char **) = {
&cd,
&help,
&exit,
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
printf("the following are the builtin commands:\n");
for (i = 0; i< num_builtins() ; i++)
{

	printf("%s\n",builtin_str[i]);

}

printf(" see man pages for more details\n ");
return 1;

}

// function for exit 


int shell_exit(char **args)
{

	return 0;
}


//function to find last character and check whether it's "&" 

int find_lastcharacter(char* line)
{

if(line[(strlen(line)-1)] == '&')
{

printf(" process is running in the background\n");

return 1;
}

return 0;
}


//function to execute the command provided by the user

int execute(char **args, int last_char_amp_and)
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

        return launch(args, last_char_amp_and);

}


// function to  execute when user provides "|" in the command

int execute_pipe(char** args1,char** abc,int is_last_character_amp_and)
{

pid_t pid;
int fd[2];
pipe(fd);
pid = fork();

if(pid == 0)
{

	dup2(fd[WRITE_END],STDOUT_FILENO);
	close(fd[READ_END]);
	close(fd[WRITE_END]);
	if(execvp(args1[0],args1)<0)
	{
	perror("Error in execution\n");
	}

}

else 
{
pid= fork();
if(pid == 0){
	
	dup2(fd[READ_END],STDIN_FILENO);
	close(fd[WRITE_END]);
	close(fd[READ_END]);
	if (execvp(abc[0],abc)<0)
	{
	perror("Error in execution\n");
	}
	}else {

		if(is_last_character_amp_and == 0)
		{
		
		int status;
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		waitpid(pid, &status,0);
		}
	}

}

return 1;
}

// function to implement the built-in command export

int execute_export(char** export_arr){

	// Call setenv
//	printf("Calling this function\n");
//	printf("1st element = %s\n", export_arr[1]);
//	printf("3rd element = s \n", export_arr[3]);
	setenv(export_arr[1], export_arr[3], 1);
	return 1;
}


// function for continous loop to call thr repl (read, evaluate  , print, loop)

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
	char duplicate_inp[80];

	line = read_line();
	strcpy(duplicate_inp, line);

// check for & (to identify whether the user entered the command to run in the background)
        int is_last_character_amp_and;
	is_last_character_amp_and = find_lastcharacter(line);

// to run the process in the background

// check for pipe 
// declare an array to hold the split array

	char *p_array[80];

	int is_pipe_present;
	is_pipe_present = find_pipe(line,p_array);
//	printf("PARSED %s\n", parse(duplicate_inp)[0]); 
	if(strcmp("export", parse(duplicate_inp)[0]) == 0)
	{
	 //printf("Coming here\n");
	char** export_arr = parse(line);
//	printf("1st = %s\n", export_arr[1]);
//	printf("2nd = %s\n", export_arr[3]);  
	state = execute_export(export_arr);

	}
	else if(is_pipe_present)
	{
// split into two arrays before parsing 
// p_array[0] and p_array[1]

	char** args1 = parse(p_array[0]);
	char** args2 = parse(p_array[1]);
	state = execute_pipe(args1, args2, is_last_character_amp_and);
	free(line);
	}

	else {

// agrs is an array of strings 

	args = parse(line);

// to execute and return the state of the system

	state = execute(args, is_last_character_amp_and);

// free the memory allocated 

	free(line);
	free(args);
}

} while(state);
}


int main (int agrc , char **argv[])
{
	signal(SIGINT,sigint_handler);

	// Handle zombie
	signal(SIGCHLD, SIG_IGN);
	printf(" Press Ctrl+C to terminate\n");
 	while(1){

// run an repl loop ie. read, evaluate, parse and loop again
	loop();
		}
return 0;
}
