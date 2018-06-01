#include <stdio.h>


void msg(){
	printf("Hello!\n");
}


int main(){

	int i;
	for(i=0; i<10; ++i){
//		printf("Debug message %d \n",i+1);
		 msg();
	}
		        		return 0;
}
