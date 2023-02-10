# Lab 4 - OpenMP – Reduction, Scope and Work Sharing
© 2021 Dr. Scott Fazackerley, Dr. Abdallah Mohamed


In this lab, you will work on the parallelization of code with OpenMP, specifically the `#pragma omp parallel for` directive as well as looking at variable scope. 


**Question 1**
In this question, you will use OpenMP to parallelize the summation of values in an array building off your code from Lab 3 - Q2.  The difference here is that instead of manually reducing the results, you will use the OpenMP `reduction` operator.   

In the code there are a series of `@todo` statements that need to be completed:
1. The size of the array (as previous) must be a multiple of the number of threads.
2. Initialize A as noted in the code using rand() (see `@todo` in code comments).
3. Add code to properly sum up the entire array.  The function will take in a pointer to `A` and sum up a portion of the array based on the thread number (see question 4 - lab 2 for how this was accomplished previously) (see `@todo` in code comments). Use the function prototype provided.  The partial sum (as an int) must be stored in a local variable and returned as an `int`.  The results of the function all will then be added to `global_sum`  Initialize `global_sum` to be `0` before starting the summation
4. Parallelize the function call to `add_vector`  using only the `#pragma omp parallel` with the appropriate reduction operator, ensuring the ability to change the number of threads created in the team (the function needs to be able to adjust to a different number of threads)
5. In the parallel function, you will need to determine how to slice the array so that each thread in the team will be summing their own part (see previous labs for this technique).
6. Add timing information for thread creation, addition and cleanup to the code; have it print the results out for a given run.  (see `@todo` in code comments) and compare the results with the serial implementation summing the same array.  
7. Experiment by increasing the number of threads using 2, 4, 8 and 16 threads and increase the size from (1000 to 1 million) * the number of threads (`ARRAY_SIZE`) and record the times in the comments in your code. 

**Question:** How does this performance compare to the previous implementation using a critical section?  What is the key difference when using `reduction`?

**Question 2**
Write a C function that sequentially adds 2 vectors `A` and `B` as `C[i]=A[i]+B[i]` (see lab 2 Q1/Q2 - pthreads). Use this function header: `void addVec(int* C, int* A, int* B, int size)`, where size is the number of elements in a vector. The goal with the exercise is to parallelize the addition inside the call to `addVec` (meaning that you will need to use OpenMP to create a thread team INSIDE the function call).  In the function there is a single index variable that needs to be properly shared between the thread team.  You CANNOT use `parallel for` for this problem.  Parallelize the code using only the #pragma omp parallel directive, adding the ability to change the number of threads created in the team (the function needs to be able to adjust to a different number of threads).

In the function you will need to 
1. Slice the arrays so that each thread in the team is working on a different part, based on the thread id and number of threads.
2. Make sure to use private for idx to ensure that each thread gets its own copy of idx (recall variable scope)
3. Make sure to use set the number of threads for the parallel section
4. Make sure to use only the parallel directive (nor parallel for; that's the next question)

Add timing information to time how long it takes to call the function `addVec`.  

Test your function with two vectors, each having 50 million integers. Note that memory allocation for A, B, and C is done within your test code for you (the `main` function). Print the first 10 elements of C as well as the total time the function took to complete. Report the timing results as a comment in your code.  Your code also needs to handle the situation where it can't successfully handle the allocation of the required memory; ensure to handle this condition as well.  When you are developing this solution, if you run into a memory allocation issue when allocating 50 million integers, test with a smaller value.   Report your timing results in a comment in your code. 

The sample runs of your code should look like:

**Sample run 1**

    0 0 0 0 0 0 0 0 0 0
    Execution time: 281.0 ms

**Sample run 2** (unsuccessful memory allocation)
    
    Not enough memory.

**Question 3**

Building off question 2, implement the function `addVec` using `parallel for`.  You will need to think about how to implement this (you won't need to slice the array manually, but you will have a variable that is shared and one that is private for each thread in the team).

Time the results and compare to your outcome in question 2 using the same test conditions.  Is this implementation easier to create and why?

**Question 4**

Question 4 is based on (PACHECO-11 Q5.3(a,b,d) p. 268) which presents a count sort which is a simple serial sorting algorithm. Review the comments in the code as well for further details.  

The basic idea is that for each element `a[i]` in the list a, we count the number of elements in the list that are less than `a[i]`. Then we insert `a[i]` into a temporary list using the subscript determined by the count. There’s a slight problem with this approach when the list contains equal elements, since they could get assigned to the same slot in the temporary list. The code deals with this by incrementing the count for equal elements on the basis of the subscripts. If both `a[i]==a[j]` and `j<i`, then we count `a[j]` as being “less than” `a[i]`. After the algorithm has completed, we overwrite the original array with the temporary array using the memcpy (in the serial version).

Build your solution using Q4.c (provided in the repo, with the function prototype and skeleton code), you will need to create a parallel implementation of the sort (use the serial implementation and parallelize key components using the OpenMP directives).  You will need to consider the following items:
1. If we try to parallelize the `for i` loop (the outer loop in the serial count sort function), which variables should be private and which should be shared within the parallel implementation? Answer specifically in the comments in the header.
2. If we parallelize the `for i` loop using the scoping you specified in the previous part, are there any loop-carried dependences? Explain your answer in the comments in the header.
3.  Write a C program that includes a parallel implementation of called `count_sort_parallel` using the code provided.  The parallelization needs to occur within the function call; using the `parallel for` construct to implement the parallel sections.  Ensure to set the number of threads in the team to use the define `NUM_THREADS`.  There are two different distinct operations that can benefit from parallelization.
4.  Add timing code to time both the serial and parallel implementations.  Report the timing for both the serial and parallel implementation with n=10,000 and 8 threads.   Report the results in the comments in your code.  In the starter code is a section that compares the results for the serial and parallel implementations.  Don't time this section. 
5. What is the advantage to using the `parallel for` implementation as compared to the manual slicing that was done in previous questions/labs?  Think about the size of the input and relationship to the number of threads in terms of a successful parallelization.  Does this hold true for the `parallel for` implementation? Test your assumption. 


