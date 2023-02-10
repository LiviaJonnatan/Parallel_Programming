# Lab 3 - OpenMP - Parallelization, Critical Sections, Atomics and Locks

In this lab, you will work on the parallelization of code with OpenMP, specifically the `#pragma omp parallel` directive.  You will also investigate the performance and operation of `critical` and `atomic` directives to protect critical sections of code. 



**Question 1**
Develop a C function that returns an `int*` pointer to a vector A initialized as `A[i]=i`, or returns NULL if the function fails.

Write the sequential code for the function. Use the header: 

`int* vecCreate (int size)`

Write the OpenMP implementation of the function. Use the header: 

`int* vecCreateOpenMP(int size, int num_thread)`

Here, you will try to speed up the vector initialization by dividing the work among several threads where each thread will initialize a segment of the vector. For example, if num_thread = 2 and size = 10, thread 0 will initialize elements 0 to 4 and thread 1 will initialize elements 5 to 9. Using #pragma omp parallel num_threads( num_thread ). This is similar to the problem from last week where you have to divide the array across a number of threads.   Your function should only work if the vector size is divisible by the number of threads. If not, your function should display an error message and return NULL. The parallelization needs to use the `#pragma omp parallel` directive

Test both functions with a 50-million element vector (and 4 threads for the second function). Your test code should print the value of the last element in the vector along with the time taken for each function to complete.  Each function needs to allocate the array on the heap (hint: `malloc`) and then return the pointer (as per the function prototype in the starter code) (see Q2 - lab 2).  Your code also needs to handle the situation where it can't successfully handle the allocation of the required memory; ensure to handle this condition as well.  

**Sample run 1: (successful)**

```Using serial code
v[49999999] = 49999999
Time: 144.00 ms

Using OpenMP with 4 threads:
v[49999999] = 49999999
Time: 59.00 ms
```

***Sample run 2: (num_thread not divisible by size)***
```Using serial code
v[49999999] = 49999999
Time: 144.00 ms

Using OpenMP with 3 threads: Error: number of threads must be divisible by vector size.
```

**Sample run 3: (unsuccessful memory allocation)**
```Not enough memory.
Not enough memory.
```

**Question 2**
In this question, you will use OpenMP to parallelize the summation of values in an array.  Build your solution using Q2.c (provided in the repo, with the function prototype). 

In the code there are a series of `@todo` statements that need to be completed:
1. The size of the array (as previous) must be a multiple of the number of threads.
2. Initialize A as noted in the code using rand() (see `@todo` in code comments).
3. Add code to properly sum up the entire array.  The function will take in a pointer to `A` and sum up a portion of the array based on the thread number. Use the function prototype provided.  The partial sum (as an int) must be stored in a local variable and added to the global variable `global_sum` (int).  Initialize `global_sum` to be `0` before starting the summation
4. Parallelize the code using only the `#pragma omp parallel` directive, adding the ability to change the number of threads created in the team (the function needs to be able to adjust to a different number of threads)
5. In the parallel function, you will need to protect the update of the `global_sum` using the appropriate mutex.  The goal is to have the function run concurrently as much as possible (only protect the updating of the final value).  Here you can choose to use the `critical` or `atomic` directive.  Start by protecting with the `critical` directive.
6. Add timing information for thread creation, addition and cleanup to the code; have it print the results out for a given run.  (see `@todo` in code comments) and compare the results with the serial implementation summing the same array.  
7. Experiment by increasing the number of threads using 2, 4, 8 and 16 threads and increase the size from (1000 to 1 million) * the number of threads (`ARRAY_SIZE`) and record the times in the comments in your code.  Repeat the experiment replacing the `critical` directive with `atomic` and comment on any differences you notice. 

**In there a difference in terms of performance time using the two different strategies?**



**Question 3**

In this question, you will examine the behaviour of a code sample that is using `critical` to protect the read-modify-write of a shared variable in one group of threads and `atomic` in another group. Examine the code in Q4 and understand what it is doing.  You will need to build and run this code.  Modify this code to run multiple times and examine the output.
