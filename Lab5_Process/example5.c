#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{

	char* myargv[16];
	myargv[0]="/bin/ls";
	myargv[1]="-F";
	myargv[2]=NULL;
	myargv[3]="ifconfig"; 
	// Terminate the argument list
	
	if(fork()==0){
	// Executes command from child then terminates our process
	execve(myargv[3],myargv,NULL);
	printf("Child: Should never get here\n");
	exit(1);
	} 		 								
	printf("This always prints last\n");
	return 0;
}
//
