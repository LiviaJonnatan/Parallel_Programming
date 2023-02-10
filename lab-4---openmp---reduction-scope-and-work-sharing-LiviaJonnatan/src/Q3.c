/**
* Starter code for lab 4 - Q3
*
**/

/** ANSWER:
 * I cannot go higher than the value of 100000 with maximum number of threads 4
 * due to memory issues.
 * 
 * Execution time: 1.3490 ms
 * 
 * Performace in Q3 is better than Q2 due to the use of parallel for. It is easier
 * to create because the system parallelizes the for loop by dividing the
 * iterations of the loop among the threads, which means I don't have to slice it.
 * Also, I don't have to ensure that the array size is divisible by the number of
 * threads because by using the parallel for, the system will figure out by itself.
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

//this is the length of the slice (ARRAY_SIZE/NUM_THREADS)
int length;

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
    // each location of A and B (+4)
    for (int i = 0; i < ARRAY_SIZE; i ++)
    {

        A[i] = rand();
	    B[i] = rand();
    }
    
    /** Compare this to how this was accomplished with pThreads (or even OpenMP 
    * where we had to manually slice the array.  Parallel for is a very powerful
    * construction
    **/
    /** @todo add timing information for this call.  Compare this to Q2.*/
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
 **/
void add_vector(int* C, int* A, int* B, int size)
{
    int idx = 0;
    
    /** @todo parallel code goes here! **/
    #pragma omp parallel for num_threads (NUM_THREADS)
        for (idx = 0; idx < size; idx++)
            C[idx] = A[idx] + B[idx];
}
