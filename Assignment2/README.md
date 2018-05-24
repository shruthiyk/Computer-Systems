# Due Date: May 23, 2018 at 11:59 PM.

TODO Please edit the following information in your assignment

- Name: Shruthi Kulkarni
- How many hours did it take you to complete this assignment? 8 hours
- Did you collaborate with any other students/TAs/Professors? none
- Did you use any external resources? (Cite them below)  yes
  - C Programming Language - GeeksforGeeks
  - mycodeschool - DS videos
- (Optional): understanding concept
- (Optional) How would you improve the assignment?



# Building Data Structures - Queue
<img align="right" src="https://upload.wikimedia.org/wikipedia/commons/thumb/5/52/Data_Queue.svg/450px-Data_Queue.svg.png" alt="Queue picture">

We have previously learned the Linked List Data Structure. Now we will introduce another data structure, known as the 'queue'.

A 'queue' data structure is analogous to waiting in line at a grocery store. The first person to the checkout counter is served, followed by the next person, and then the next until the line is empty. A queue is what is known as a 'first-in first-out' (FIFO) data structure. Thus queues have a strict policy about how information is stored and accessed.

For this assignment, you are going to implement a specific implementation of a queue using an array. This data structure is also called a circular queue (specifically a ring buffer when the maximum storage size is fixed).

Provided for you is a skeleton of the implementation queue_array.c that you will implement and test.

## Part 1 - Queue implementation as an array (Ring Buffer).

A circular buffer has a fixed sized, or maximum number of elements that it can hold. This is advantageous if we know how many elements are typically stored in a data structure (If we do not know, then a queue with a linked list implemetation is needed). 

For more information on the Circular buffer, see here: https://en.wikipedia.org/wiki/Circular_buffer

This animation below gives an idea about how the data structure 'wraps' around. Think about what mathematical operator could be useful in your implementation when enqueuing and dequeuing items in your queue.

![](https://upload.wikimedia.org/wikipedia/commons/thumb/f/fd/Circular_Buffer_Animation.gif/400px-Circular_Buffer_Animation.gif)

Your task will be to implement the functions in the queue_array.c to have a working implementation of queue.

You *may* also consider writing some unit tests to test your implementation. You can include those in your submission, but we will have our own test suite.

## Part 2 - Why is a ring buffer/circular queue useful?

Queues are used quite a bit in operating systems and high performance systems, especially when performance matters. Do a little outside research, and edit test section of the Readme. Answer specifically: Why is a ring buffer useful and/or when should it be used?

# TODO: Put your answer here

Queue is a linear data structure.  The operations, Enqueue() ,Dequeue(), front() , isEmpty(), isFull() insert and remove one data at a time. Their time complexity is constant and is defined by O(1); 

Queue has a certain limitations: 
The data has to be inserted at one end and can be removed from the other end only. The allocation can be from either left or right but the rear and front end remain fixed once the memory is allocated for the queue array. 
Since the size of the queue and the operations are fixed, there is a possibility of memory wastage. 
Consider an example: say we fix the queue size to 5. add five elements, and delete two elements. 
As per the data structure design and implementation, the elements are removed but the other elements do not shift towards the front end. 
This causes two spaces to go unused. If it was integers, then 8 bytes remains unused until the entire queue is deleted. 

The concept of Circular queue can be used to address the aboved mentioned problem.
Circular queue is implementation of queue with rear and front end forming a loop instead of regular linear endings. This is just a logical implementation and the allocation of the meomory is always linear. 
Circular queue is implemented as circular array concept. This is best suited when the maximum size for queue is fixed. For dynamic allocation LinkedList implementation is preferred.

Some of the advantages of circular queue: 
It is memory efficient. Because when the an element is deleted, it is utilized again when needed.
Insertion and deletion are performed at constant time
This has less memmory consumption.
The memory of any deleted process can be used by a new process
Buffering, rebuffering issue in multimedia is addressed using circular queue.
Useful in multiprocess synchronization. Best example is Producer-Consumer problem.

Cons:
It is slightly difficult to implement circular queue than the linear queue.
This is useful only when the maximum size for queue is fixed.



# Resources to help

- This is a nice interactive tutorial for learning C
  - http://www.learn-c.org/
- Queue Data Type High level description
  - https://en.wikipedia.org/wiki/Queue_(abstract_data_type)

# Rubric

- 80% Correct Queue implementation
  - All functions should be implemented
  - There should be no memory leaks
  - There should be no bugs in your functions 
  - Your implementation will be graded by our set of unit tests
- 20% Correct writeup on the importance of queues/ring buffers as related to OS
  - I expect this to be in the range of 2-3 paragraphs (Can include complexity, example usage, pros/cons, etc).

# Feedback Loop

(An optional task that will reinforce your learning throughout the semester)

- Investigate/Review more data strutures on this webpage: https://www.cs.usfca.edu/~galles/visualization/Algorithms.html
  - There are visuals for the linked list and array based queue here!

