#include <stdio.h>


void msg(){
	printf("Hello!\n");
}


int main(){

	int i;
	for(i= 0;i  < 10; ++i){
		msg();
	}

//printf(" debug message %d \n",i);

	return 0;
}
