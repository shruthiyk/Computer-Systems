## Section 1 - Cache Simulator

For this assignment, you will be extending the diretly mapped cache simulator that we previously saw. Caches are a large part of programming, so properly understanding them will be helpful.

I have provided a 'compile script' that can help you iterate faster.

You can just run `python compile.py` which will compile your trace program, and your simulator. Then you may individually run them with `./trace` and `./simulator some_trace_file.txt`

### Part 1 E-Way Set Associative Cache Simulator

#### Task 1

Your first task will be to update the Cache Simulator to have the following attributes. This should merely involve changing a few `#define` and `const int` statements.

- 4 Cache Sets
- 4 Blocks(i.e. 4 cachelines per set)

#### Task 2

Your second task is to implement a new cache replacement and/or eviction policy. The current policy that is implemented is directly mapped. That is, we know exactly where information will be mapped in the cache based on the block offset and set.

You might implement a policy that is 'least recently used (LRU)' or 'random' for example. You are allowed to make any changes necessary to the code provided to implement your cache. If you bring more blocks of memory in at once, you should account for that in your latency to be fair (That is, whatever the cache miss penalty is).

### Part 2 - Cache Friendly Code

1. Generate one additional trace file, that is very cache friendly. The criteria is there are more cache hits than cache misses.
2. Generate one additional trace file, that is cache adverse. The criteria is there are more cache misses than cache hits.

**Discussion**

For task two, write a paragraph describing why your cache replacement and eviction policy may be good in the real world. That is what workloads will it work well for.

- Implemented FIFO cache replacement policy for the assignment.  
- FIFO is better in time complexity as compared to LRU because only the first element that came in is popped
  whereas in LRU , one needs to traverse through the entire data structure to find the lease recently used page. 
- The first-in , fisrt-out page replacement algorithm is a low-overhead algorithm as it requires little bookkeeping on part of the    OS.The OS keeps track of all pages in the memory in the queue, with the most recent arrival at the back and the oldest in the front. 
Hence it is economical. 
- It is used in VAX/VMS operating system used for general-purpose computing with some modifications.


## Rubric

1. 40% for section 1 - Cache Simulator
     1. 10% for updating the cache attributes
     2. 30% for changing the replacement and/or eviction policy from my directly mapped implementation.
4. 10% for section 2 - Cache Friendly Code and discussion
     
# Resources to help

This serious of videos(1-6) from the University of Washington will be a nice refresher on caches: [https://www.youtube.com/watch?v=b5v9aElYU2I]

### Glossary and Tips
1. Commit your code changes to the repository often, this is best practice.
2. Do not commit your .o file or your executable file to the repository, this is considered bad practice!
3. On Functionality/Style
	1. You should have comments in your code to explain what is going on, and use good style (80 characters per line maximum for example, functions that are less than 50 lines, well named variables, well named functions etc.).
     
# Going Further

You might consider implementing multiple replacement and eviction policies to find the optimal one.

# Feedback Loop

(An optional task that will reinforce your learning throughout the semester)

* Make yourself a little cheat sheet for what types of data structures and algorithms you belive to be cache friendly.
* You might additionally watch this talk by Mike Acton on "Data-Oriented Design" https://www.youtube.com/watch?v=rX0ItVEVjHc&t=1s
