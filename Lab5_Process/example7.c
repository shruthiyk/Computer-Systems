#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>


int main()
{

char* myargv[16];
myargv[0]="queue";
myargv[1]="-F";
myargv[2]=NULL;

if(fork()==0)
{
execve(myargv[0],myargv,NULL);
printf("Child: should never get here\n");
exit(1);
}

printf(" This always prints last\n");

return 0;
}


