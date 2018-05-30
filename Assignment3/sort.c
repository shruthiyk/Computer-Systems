// Do not add any more 'includes'
#include <unistd.h>
//
void sort(int* array, int size);
void swap(int *a1, int *a2);
// // Implement your sort function here
// // This can be any sort function you like(brute force, bubble, quick, etc.)
void sort(int* array, int size){
int i=0 ;
int j;
for (i=0; i<size-1 ; i++)
  {
  for ( j=0 ; j<size-1 ; j++)
  {
  if(array[j]>array[j+1])
  {
  swap(&array[j],&array[j+1]);
  }
  }
  }
  }

  void swap(int *a1, int *a2)
  {
  int temp; 

  temp = *a1;
  *a1 = *a2;
  *a2= temp;
  }
//  	 
//
  	 int main(){
//
//  	 // Initialize the data array
//  	 // Do not modify this data.
//  	 // You will see a nice printout if your data is sorted correctly with these values :)
//  	 	
//  	 		    
  	 		    int data[9] = {116,67,69,102,101,102,111,114,65};
//
//  	 		    // Call sort
  	 		    sort(data,9);
//  	 		    // Iterate through the data
  	 		    int i =0;
//  	 		    // Use the 'write' system call. 
//  	 		    // Do NOT use printf anywhere in your assembly.
  	 		    for(i = 0 ; i < 9; ++i){
  	 		    write(1,&data[i],sizeof(data[i]));
//  	 		    //printf("%d\n", data[i]);
  	 		    }
//
  	 		    return 0;
  	 		    }
