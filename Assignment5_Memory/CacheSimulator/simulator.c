// Compile with: clang -std=c11 -lm simulator.c -o simulator
//
// Run with: ./simulator realistic.txt
//
// All in one go run with: clang -std=c11 -lm simulator.c -o simulator && ./simulator realistic.txt
//
// This program imports a trace file
// and tells us how many cache hits and misses
// we get based on the policy functions you implement.
//
//
#include <stdio.h>
#include <stdlib.h>
#include "binary.h"
#include <string.h>

// Toggle these values to generate different
// addresses
#define BITWIDTH 16	// Our architecture is an 16-bit architecture. i.e. contains M= 2^m where m is BITWIDTH unique addresses.
#define ADDRESSES 16384	// By default we generate 16384 instructions
#define RANGE 256	// The range of these instructions is a value 0-RANGE. Co-incides with 'M'

// =============== Our CPU ===============
// This is where all of our instructions are loaded up into
char instructionCache[ADDRESSES][BITWIDTH+1];
// This is our Program Counter which executes the next
// instruction. In this case, it looks at our instruction Cache.
// which for our (fictional) machine holds all the instructions
// that will be executed.
int PC = 0;

// Attributes of our cache
#define E  4 // Number of cachelines. 1 cacheline in each of our 4 sets.
#define B  2 // Data block bits B = 2^b. 2 for example with 16 bit addresses (8 bytes per block)
#define S  4 // Number of cache sets. S=2^s. By default, start with 4.

// Some helper variables for the range of bits to collect to determine
// the cache set.
const int cacheLineOffsetStart = 0;
const int cacheLineOffsetStop = 1;

const int cacheSetOffsetStart = 2;
const int cacheSetOffsetStop = 3;

const int tagStart = 3;

// Some structures for managing our cache.
// You can add whatever you think is necessary if you need to do more book keeping.
char cacheSet[S][E][BITWIDTH+1];
int cacheOccupied[S][E];				// 1 or a 0 if occupied
// =============== Our CPU ===============


// =============== Cache Performance ================
// Keep track of how well our cache is performing with some metrics.
// Minimize the cache misses and maximize the cache hits!
int cacheHit = 0;
int cacheMisses = 0;

int costOfCacheHit = 1; // This is the latency
int costOfCacheMiss = 100; // This is latency,

int totalLatency =0;	// How fast or slow is our system
// =============== The Game ================


// implementing FIFO/LRR (first-in,first-out/least-recently replaced) policy
// FIFO replaces the oldest item in the cache favoring recetly loaded items to old items in the cache
// initializing 4 sets of cache

int s0cacheArray[] = {0, 0, 0, 0};
int s1cacheArray[] = {0, 0, 0, 0};
int s2cacheArray[] = {0, 0, 0, 0};
int s3cacheArray[] = {0, 0, 0, 0};

// initialize a counter for each set and set it to 0
// each of this points to the line that will be replaced next and these counters are updated only on cache misses

int s0Counter = 0;
int s1Counter = 0;
int s2Counter = 0;
int s3Counter = 0;


// This function loads a trace file that has been
// previously generated.
// Trace files consist of binary numbers which
// (fictionally) represent instructions that have
// been executed by a CPU.
void loadTrace(char* filename){
	FILE* fp = fopen(filename,"r");

	char str[BITWIDTH+2]; // Strings are null terminated, so there is one extra character, plus the endline
	int pos = 0;
	while(fgets(str,sizeof(str),fp)){
		str[strlen(str)-1]='\0';		// Remove the endline character by terminating it
		strcpy(instructionCache[pos],str);	// Allocates memory for our array
		//printf("%d: %s",pos, instructionCache[pos]); // print out lines read in from file
		++pos;
	}

	fclose(fp);
}



// User interface showing our cache simulator each step along the way.
void drawCache(){

	int cacheLineIndex = binaryStringRangeToInt(instructionCache[PC],cacheLineOffsetStart,cacheLineOffsetStop);
	int cacheSetIndex = binaryStringRangeToInt(instructionCache[PC],cacheSetOffsetStart,cacheSetOffsetStop);
	int tag = binaryStringRangeToInt(instructionCache[PC],cacheSetOffsetStop+1,BITWIDTH-1);


	printf("Hits: %d Misses: %d Total Latency: %d\n",cacheHit,cacheMisses,totalLatency);
	printf("Instruction[%d] is executed\n",binaryStringToInt(instructionCache[PC],BITWIDTH+1));

	// Note that 'set' is the cache set
	// Note that 'block' is the cache line.
	// We assume all data is valid in this cache for simplicity.
	// When the cache starts out, all of these bits are 0 however!
	printf("---------------------------\n");
	printf("valid | tag | Set | block | value\n");
	printf("1       %d    %d      %d      %s   \n",tag, cacheSetIndex,cacheLineIndex,instructionCache[PC]);
	printf("---------------------------\n");

	for(int i =0; i < S; i++){
		printf("Cacheset[%d]",i);
		for(int j = 0; j < E; j++){
			printf("(%d) %s ",j,cacheSet[i][j]);
		}
		printf("\n");
	}


	if(cacheMisses!=0){
		printf("Total Cache Hits: %d Cache Misses %d ratio %f Total Latency: %d  \n",cacheHit,cacheMisses,((float)cacheHit)/((float)cacheMisses),totalLatency);
	}
//	printf("\033[7A]");

}


// This function loads an address in the simulator.
// This is equivalent to moving the program counter.
// and then we decide if it goes in the cache or not.
void stepSimulator(){
	PC++;
}


// Scorekeeping update when we have a cache miss
void incrementCacheMiss(){
	// Any time we replace we up the count
	cacheMisses++;
	// Update the total latency
	totalLatency+=costOfCacheMiss;
}

// Scorekeeping update when we have a cache miss
void incrementCacheHit(){
	// Update our count
	cacheHit++;
	// Update our latency
	totalLatency+=costOfCacheHit;
}

//

int findMinIndex(int cacheArr[], int cacheLen){
int cacheIndex = 0;
int i,minEle;
minEle = cacheArr[0];
for( i = 0;i < cacheLen ; i++){
	if(cacheArr[i] < minEle) {
  		minEle = cacheArr[i];
		cacheIndex = i;
	}
}

return cacheIndex;

}


void updateCacheArray(int s , int e){
if(s == 0) {
	s0cacheArray[e] = s0Counter;
} else if( s ==1 ) {
	s1cacheArray[e] = s1Counter;
}
else if( s == 2 ) {
        s2cacheArray[e] = s2Counter;
}
else {
        s3cacheArray[e] = s3Counter;
}
}

// incrementing each set
void updateCacheCount( int s){
	if(s == 0) {
	s0Counter++;
	}
	else if(s == 1) {
	s1Counter++;
	}
	else if(s == 2) {
	s2Counter++;
	}
	else {
	s3Counter++;
	}
}


int getLineToRemove( int s){
if( s == 0 ){
return findMinIndex(s0cacheArray ,4);
}
if( s == 1 ){
return findMinIndex(s1cacheArray ,4);
}
if( s == 2 ){
return findMinIndex(s2cacheArray ,4);
}
if( s == 3 ){
return findMinIndex(s3cacheArray ,4);
}
}




// Decide which index should be replaced in our cache.
// And then perform the actual replacement.i
// In our scheme, we are going to replace all of the blocks at once.
// This will help improve spatial locality.
void ReplacementPolicy(){
	// Figure out where to look in the cache based on the index.
	int cacheLineIndex = binaryStringRangeToInt(instructionCache[PC],cacheLineOffsetStart,cacheLineOffsetStop);
	int cacheSetIndex = binaryStringRangeToInt(instructionCache[PC],cacheSetOffsetStart,cacheSetOffsetStop);
	// The cache is now occupied
	cacheOccupied[cacheSetIndex][cacheLineIndex]=1;

	// call the function to update the cache count
  updateCacheCount(cacheSetIndex);
	// function to update the specific cache line in the specific cache set
  updateCacheArray(cacheSetIndex,cacheLineIndex);

	// Copy in the string to the cache
	strcpy(cacheSet[cacheSetIndex][cacheLineIndex],instructionCache[PC]);	// Allocates memory for our array
	// Any time we are replacing in our cache, that is a cache miss!
	incrementCacheMiss();
}

// Decide whether an item is in the cache or not.
// If an item needs to be evicted, the replacement policy is called
// otherwise, we do not need to do any worj,
void evictionPolicy(){
	// Figure out where to look in the cache based on the index.
	int cacheLineIndex = binaryStringRangeToInt(instructionCache[PC],cacheLineOffsetStart,cacheLineOffsetStop);
	int cacheSetIndex = binaryStringRangeToInt(instructionCache[PC],cacheSetOffsetStart,cacheSetOffsetStop);
  int tag = binaryStringRangeToInt(instructionCache[PC], cacheSetOffsetStop+1,BITWIDTH-1);

  int counter;
	// lop through each set
  for(counter = 0; counter < 4; counter++){
    int innerTag = binaryStringRangeToInt(cacheSet[cacheSetIndex][counter], cacheSetOffsetStop+1, BITWIDTH-1);
    if(innerTag == tag){
			// if the tag is matched , it's a cache hit and thus increment the cachehit count
      incrementCacheHit();
      return;
    }

  }
	 // it's a compulsary miss when the tag does not match the existing element in the cache
	 printf("Compulsary miss!\n");

   int minCacheLineIndex = getLineToRemove(cacheSetIndex);
	 // update the cache count
   updateCacheCount(cacheSetIndex);
	 // update the cache array
   updateCacheArray(cacheSetIndex,minCacheLineIndex);
   cacheOccupied[cacheSetIndex][minCacheLineIndex] = 1;

		// Cache miss and decide who to keep.
		// In general, always swap in for a simple policy!
		strcpy(cacheSet[cacheSetIndex][minCacheLineIndex],instructionCache[PC]);	// Allocates memory for our array
		// Update our scoreboard.
		incrementCacheMiss();
}

// check if cache is filled first.
// If it is filled, figure out whether something should
// be evicted and tally a cache hit or miss.
void checkCache(){
	// Figure out where to look in the cache based on the index.
	int cacheLineIndex = binaryStringRangeToInt(instructionCache[PC],cacheLineOffsetStart,cacheLineOffsetStop);
	int cacheSetIndex = binaryStringRangeToInt(instructionCache[PC],cacheSetOffsetStart,cacheSetOffsetStop);

	// If the cache is not occupied, it is a cache miss
	if(cacheOccupied[cacheSetIndex][cacheLineIndex]==0){
		printf("Cold Miss!\n");
		ReplacementPolicy();
	}else if(cacheOccupied[cacheSetIndex][cacheLineIndex]==1){
		evictionPolicy();
	}

}


int main(int argc, char **argv){

	// Loads a programs execution.
	// Ideally this would be happening one instruction at a time
	// However, for our purposes, we have a 'trace' of a program
	// That is, a captured execution of the addresses that were
	// 'fetched' from the CPU.
	loadTrace(argv[1]);


	// Initiate our cache sets to be empty.
	// If there were additional blocks or cachelines in each set
	// we would also zero those out.
	// Remember, all programs start out empty.
	for(int i =0; i < S; ++i){
		for(int j=0; j < E; ++j){
			cacheOccupied[i][j] = 0;
		}
	}

	// Our simulator is interactive
	// While 'run' is set to 'y'
	// it will continue.
	char run='y';

	// We run our program until we run out of addresses to
	// execute or the user terminates.
	while((run=='y'|| run=='a') && PC < ADDRESSES){
		printf("============================================================================\n\n");
		// (1) Check our cache and run our policy.
		checkCache();
		// (2) A visual display of our cache and our user interface
		drawCache();
		// (3) We execute one instruction (Increment the PC)
		stepSimulator();

		// Ask if we would like to continue stepping through
		// our simulation.
		if(run !='a'){
			printf("Would you like to continue? (y-yes | n-no | a-simulate to finish): ");
			scanf("%s",&run);
		}
	}

	// We end our simulation
	printf("Simulation Complete\n");
	return 0;
}
