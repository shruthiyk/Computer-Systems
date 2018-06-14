// Modify this file for your assignment

void loop()
{

char* line;
char ** status;
int status;

// read the commands entered by the user 
// it will parse the commands computer can understand and execute the command

do {
printf("%s","mini-shell> ");
line = read();

// agrs is an array of strings 
args = parse(line);

//  to execute and return the status
status = execute(args);
// free the memory allocated 
free(line);
free(args);

} while(status)
}


int main (int agrc , char** argv){

// load the configuration files

// run an repl loop: 
loop();
// perform any shutdown clean up
return 0;
}
