#include <unistd.h>
//
void sort(int* array, int size);
void swap(int *a1, int *a2);
// Implement your sort function here
// This can be any sort function you like(brute force, bubble, quick, etc.)
void sort(int* array, int size){
int i;
int j;
int temp;
for (i=0; i<size-1 ; i++)
  {
    for ( j=0 ; j<size-1 ; j++)
      {
        if(array[j]>array[j+1])
          {
         
                 temp = array[j];
                 array[j] = array[j+1];
                 array[j+1]= temp;
           }
         }
     }
}

int main(){
                                                               
// Initialize the data array
// Do not modify this data.
// You will see a nice printout if your data is sorted correctly with these values :)
                                       
int data[9] = {116,67,69,102,101,102,111,114,65};
                                                                                           
// Call sort
sort(data,9);
// Iterate through the data
int i =0;  
// Use the 'write' system call. 
// Do NOT use printf anywhere in your assembly.
for(i = 0 ; i < 9; ++i){
 write(1,&data[i],sizeof(data[i]));
        }

        return 0;
}
