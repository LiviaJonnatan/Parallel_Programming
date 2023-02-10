/**
* Starter code for lab 4 - Q1
* @todo Please read the comments in the code to understand what needs to be done.
* use your code from last week's Q2!.  If you are having troubles getting
* the code running, please make sure you meet with your TA or instructor.
*
* This is the same problem as Lab 3 - Q3 but done with the reduction operator 
* Note:        
*   -return value should be added in to an OpenMP reduction variable for the total sum
*              
**/

/**
 * Number of threads    | Value     | Execution time (ms) 
 * --------------------------------------------------------
 * 1                    | 1000      | 0.2330
 *                      | 10000     | 0.3970
 *                      | 100000    | 0.7210
 *                      | 1000000   | 3.6170
 * --------------------------------------------------------
 * 2                    | 1000      | 0.2380
 *                      | 10000     | 0.3370
 *                      | 100000    | 0.6560
 *                      | 1000000   | 4.2190
 * --------------------------------------------------------
 * 4                    | 1000      | 0.2950
 *                      | 10000     | 0.4680 
 *                      | 100000    | 0.8690
 *                      | 1000000   | 5.8870
 * --------------------------------------------------------
 * 8                    | 1000      | 0.3980
 *                      | 10000     | 0.5080
 *                      | 100000    | 1.5630
 *                      | 1000000   | 11.8800
 * --------------------------------------------------------
 * 16                   | 1000      | 0.5610
 *                      | 10000     | 0.7600
 *                      | 100000    | 2.9110
 *                      | 1000000   | 23.9050
 * --------------------------------------------------------
 * Using reduction improves the overall performance compared to the previous
 * implementation using critical section. 
 * By using reduction, I don't have to use critical clause because the reduction
 * clause provides a private copy of the global_sum variable for each thread
 * which is private first then combined the results on exit. 
**/

#include <stdio.h>       
#include <stdlib.h>
#include <omp.h>     

//This defines the number of threads that will be used for the problem
/** @todo adjust this ! */
#define NUM_THREADS 16

// The array size must be a multiple of the number of thread (for this example)
// otherwise bad things will happen (ie one thread attempting to access data
// outside of the bounds of the array)
#define VALUE 1000  /** @todo adjust this value to increase number of elements */
#define ARRAY_SIZE (NUM_THREADS * VALUE)


/**
 * Function to run as an OpenMP parallel section 
 * 
 * Recall that each thread will work through only a portion of the array
 * Each thread, will process only a part of the global array and it's 
 * starting position will be controlled by thread number and range (size of 
 * array divided by number of available threads). The portion of the array
 * that is being processed is still determined by the thread number
 * and needs to be evenly divisible.
 * 
 * @todo this function needs to be called using a parallel directive using reduction.
 * This is similar to what we did in lab 3, but there, needed to manually reduce
 * the sum.
 * @param input - array A
 * @param size - the size of the array (ie number of elements)
 * 
 * @return the partial sum for the thread 
 **/
int add_vector(int * A, int size);

/* like any C program, program's execution begins in main */
int main(int argc, char* argv[])
{
    /** @todo declare A and global_sum in main (with correct type)*/
    int *A = (int*) malloc(ARRAY_SIZE * sizeof(int));
    int global_sum = 0;
    if (A != NULL){
        /** @todo Initial A with random values */
        // for a given array size, generated random values for 
        // each location of A
        for (int i = 0; i < ARRAY_SIZE; i ++)
        {
        	/** @todo Initial A with random values */
            A[i] = rand();
        }

        /** @todo launch your parallel code! 
        *           As you are now using the reduction operator,
        *           do we need to protect global_sum in a crtical section?
        *           timing!
        **/
        double timer = omp_get_wtime();
        #pragma omp parallel num_threads(NUM_THREADS) reduction(+:global_sum)
            global_sum = add_vector(A, ARRAY_SIZE);
        timer = (omp_get_wtime() - timer) * 1000;
    
        /** @todo 
         * Check the results to make sure the sums are working!
         * Print out sums and timing information with number of threads)
         * Use your code from last week - Lab 3 - Q2 
         **/
        printf("Using %d threads: ", NUM_THREADS);
        printf("\nSum: %d \n", global_sum);
        printf("Execution time: %.4f ms\n", timer);
    } else {
        printf("Not enough memory.");
    }
    
    free(A);   
    exit(0);
}


/** @todo complete this function */
int add_vector(int * A, int size)
{
    // this will work through only a portion of the array
    // Each thread, will process only a part of the global array 
    // and it's starting position will be controlled by thread
    // number and range.
    // 
    int tid = omp_get_thread_num();
    int n = size / NUM_THREADS;
    int start = tid * n;
    int end = start + n - 1;
    int local_sum = 0;
    for (int i = start; i <= end; i++)
        local_sum += A[i];
    return local_sum;
   
}