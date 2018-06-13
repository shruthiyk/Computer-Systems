#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

	pid_t pid;
	int x = 1;
	
	char* myarg1[16];
	myarg1[0]="/bin/whoami";
	myarg1[1]=NULL;

        char* myarg2[16];
	myarg2[0]="/bin/ls";
	myarg2[1]=NULL;

	char* myarg3[16];
	myarg3[0]="a1";
	myarg3[1]=NULL;

	pid = fork();
   
	if(pid==0)
	{
		execve(myarg1[0],myarg1,NULL);	
		printf("child: x=%d\n",++x,getpid());
		return 0;	
	}

	
	else if(pid==1)
		{
		pid = fork();
		if (pid==0)
		{
		execve(myarg2[0],myarg2,NULL);	        
        	printf("child: x=%d\n",++x,getpid());
               	return 0;       
        	}	
		}	

	else{
	pid = fork();
	if(pid==0)
		{
                execve(myarg3[0],myarg3,NULL);
                printf("child: x=%d\n",++x);
                return 0;
                }

		}		
	 return 0;
 }
	//
	//
