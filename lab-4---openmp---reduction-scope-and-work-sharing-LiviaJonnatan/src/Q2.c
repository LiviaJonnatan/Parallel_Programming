/**
* Starter code for lab 4 - Q2
* @todo Please read the comments in the code to understand what needs to be done
* Note: 
*       -use can use slicing method of lab 3 - Q2
*       -time with omp_get_wtime() which returns the number of seconds that have passed since some 
*       time in the past. For details on taking timings, see Section 2.6.4 of the textbook PACHECO-11. 
**/

/** ANSWER:
 * I can't successfully handle the allocation of the required memory because
 * the skeleton code initialize the arrays with stack instead of heap (mallo/calloc).
 * 
 * I cannot go any higher than the value of 100000 with maximum number of threads 4 
 * due to memory issues.
 * 
 * Execution time: 1.7280 ms
**/

#include <stdio.h>       
#include <stdlib.h>
#include <omp.h>

//This defines the number of threads that will be used for the problem
/** @todo adjust this ! */
#define NUM_THREADS 4

// The array size must be a multiple of the number of thread (for this example)
// otherwise bad things will happen (ie one thread attempting to access data
// outside of the bounds of the array)
#define VALUE 100000  /** @todo adjust this value to increase number of elements */
#define ARRAY_SIZE (NUM_THREADS * VALUE)


/** 
 * make sure size is shared across all threads,
 * and idx is private (each thread will need it's own copy)
 **/
void add_vector(int* C, int* A, int* B, int size);

/* like any C program, program's execution begins in main */
int main(int argc, char* argv[])
{

    int A[ARRAY_SIZE];
    int B[ARRAY_SIZE];
    int C[ARRAY_SIZE];
    
    // for a given array size, generated random values for 
    // each location of A and B 
    for (int i = 0; i < ARRAY_SIZE; i ++)
    {
        A[i] = rand();
	    B[i] = rand();
    }
    
    /** Compare this to how this was accomplished with pThreads.
    **/
    /** @todo add timing information for this call*/
    double timer = omp_get_wtime();
    add_vector(C, A, B, ARRAY_SIZE);
    timer = (omp_get_wtime() - timer) * 1000;
    for (int i = 0; i<10; i++){
        printf("%d ", C[i]);
    }
    printf("\nExecution time: %.4f ms \n", timer);
    //check results
    char bad = 0;

    for (int i = 0; i < ARRAY_SIZE; i ++)
    {
	    if (A[i] + B[i] != C[i])
	    {
	    	    printf("Error at %d\n",i);
		    bad |= 1;	
	    }
    }
    if (bad)
    {
	    printf("Sums failed\n");
    }
    else
    { 
	    printf("Sums all good!\n");
    }

    exit(0);
}

/** 
 * make sure size is shared across all threads,
 * and idx is private (each thread will need it's own copy)
 * *parallelize the slicing and addition inside! 
 * @todo based on the thread id and number of threads, you will need to slice up the array so that each thread is working on its own section.
 * @todo make sure to use private for idx to ensure that each thread gets its own copy
 * @todo make sure to use set the number of threads for the parallel section
 * @todo make sure to use only the parallel directive (NOT the parallel for; that's the next question)
 **/
void add_vector(int* C, int* A, int* B, int size)
{
    int idx = 0;    //use this for the array index, but make sure that each thread gets its own private copy!
    /** @todo parallelize the addition of c = a + b across the threads*/ 
    #pragma omp parallel num_threads(NUM_THREADS) private(idx) shared(size)
    {
        int tid = omp_get_thread_num();
        int n = size / NUM_THREADS;
        int start = tid * n;
        int end = start + n - 1;
            for (idx = start; idx <= end; idx++){
                C[idx] = A[idx] + B[idx];
            }

    }
	
}