# Lab 4

## Help Received

Please document any help you received in completing this lab. Note that the what you submit should be your own work. Refer to the syllabus for more details. 

[ANSWER HERE]

## Describe your work

Please provide a short description of each of the programs you completed in this lab

## Part 1: Task 1: Memory Leaks (15 points)

  1. Run valgrind on the memleak program, how many bytes does it say have been definitely lost?
  
It says that 60 bytes have definitely been lost.

  2. What line does valgrind indicate the memory leak has occurred?

The memory leaks occur on line 34 and 50.

  3. Describe the memory leak below.
  
In the main method on line 34 at the calloc(), new memory is allocated, and assigned to a pointer variable a. Then online 50 a is reassigned to the double up method, and new memory is allocated but none of the memory from the main method was freed so a memory leak occurred. 

  4. Try and fix the memory leak and verify your fix with valgrind. Describe how you fixed the memory leak below. 
I freed memory the memory that was allocated on line 34, then I freed the memory that was allocated on like 50. I freed it using the free(a) function.

## Part 1: Task 2: Memory Violations (15 points)

  1. Describe the output and execution of the program. Does it seem to be consistent?
  
The output of the program is "Hello World!". 

  2. Run the program under valgrind, identify the line of code that is
     causing the memory violation and its input. What line of code?

The memory violation is on line 11 and line 12. 

  3. Debug the memory violation and describe the programming bug below. 

The memory was allocated to the wrong size because it didn't take into account the termination value '\0' so the size was too small.

  4. Fix the memory violation and verify your fix with valgrind. What was the fix?

I fixed it by changing the size of the str variable to strlen(hello) + 1. And I changed the loop iteration to that aswell. 

## Part 2: simplefs (70 points)

(Provide a general description and any comments about your code below)

In this part of the lab we created a filesystem using linked lists where we can create and remove files in the file system using functions we write. And when we edit a new file we have to update the time stamp on it. 

## Part 2: Extra Credit (+5 points)

[ANSWER HERE]
