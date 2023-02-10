/**
* Starter code for lab 3 - Q2
* @todo Please read the comments in the code to understand what needs to be done
**/

/** SERIAL
 * Value        | Time
 * ----------------------------
 * 1000         | 0.0120 ms
 * 10000        | 0.0830 ms
 * 100000       | 0.7120 ms
 * 1000000      | 6.8820 ms
 * ----------------------------
 * Comparing the execution time between serial and parallel implementation,
 * parallel definitely runs significantly faster compared to serial.
**/

/** PARALLEL
 * Threads  | Value         | Critical Time | Atomic Time
 * -------------------------------------------------------
 * 2        | 1000          | 0.0003 ms     | 0.0003 ms
 *          | 10000         | 0.0006 ms     | 0.0006 ms
 *          | 100000        | 0.0008 ms     | 0.0008 ms
 *          | 1000000       | 0.0062 ms     | 0.0045 ms
 * -------------------------------------------------------
 * 4        | 1000          | 0.0004 ms     | 0.0004 ms
 *          | 10000         | 0.0007 ms     | 0.0004 ms
 *          | 100000        | 0.0013 ms     | 0.0011 ms
 *          | 1000000       | 0.0067 ms     | 0.0061 ms
 * -------------------------------------------------------
 * 8        | 1000          | 0.0004 ms     | 0.0004 ms
 *          | 10000         | 0.0007 ms     | 0.0007 ms
 *          | 100000        | 0.0025 ms     | 0.0016 ms
 *          | 1000000       | 0.0153 ms     | 0.0126 ms
 * -------------------------------------------------------
 * 16       | 1000          | 0.0006 ms     | 0.0006 ms
 *          | 10000         | 0.0008 ms     | 0.0008 ms
 *          | 100000        | 0.0040 ms     | 0.0030 ms
 *          | 1000000       | 0.0322 ms     | 0.0316 ms
 * -------------------------------------------------------
 * Looking at the result and comparing between using critical and atomic directive,
 * in this function (adding vector), atomic generally runs faster compared to critical directive,
 * which I think is logical as the operation following the directive is a load-modify-store.
 * Atomic directive perform better in load-modify-store operation compared to critical directive.
**/

#include <stdio.h>       
#include <stdlib.h>
#include <omp.h>   
#include <time.h>

//This defines the number of threads that will be used for the problem
/** @todo adjust this ! */
#define NUM_THREADS 2

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
 * array divided by number of available threads).
 **/
void add_vector(int * A, int size, int * global_sum){
    int tid = omp_get_thread_num();
    int n = size / NUM_THREADS;
    int start = tid * n;
    int end = start + n - 1;
    int local_sum = 0;
    for (int i = start; i <= end; i++){
        local_sum += A[i];
    }
    #pragma omp atomic
        *global_sum += local_sum;
}

void add_vector_serial(int * A, int size, int * global_sum_serial){
    int local_sum = 0;
    for (int i = 0; i < size; i++){
        local_sum += A[i];
    }
    *global_sum_serial += local_sum;
}

/* like any C program, program's execution begins in main */
int main(int argc, char* argv[])
{
    /** @todo declare A and global_sum in main (with correct type)*/
    int *A = (int*)malloc(ARRAY_SIZE * sizeof(int));
    int global_sum = 0;
    int global_sum_serial = 0;

    /** @todo Initial A with random values */
    // for a given array size, generated random values for 
    // each location of A
    if ((ARRAY_SIZE % NUM_THREADS == 0)){
        if (A != NULL){
            for (int i = 0; i < ARRAY_SIZE; i++) {
                A[i] = rand();
            }
            /** @todo launch your parallel code! **/
            /** +2, +1 (timing) */
            double timer = omp_get_wtime();
            #pragma omp parallel num_threads(NUM_THREADS)
            {
                add_vector(A, ARRAY_SIZE, &global_sum);
            }
            timer = omp_get_wtime() - timer;
            double timerms = timer*1000;

            /** @todo calculate sum serially and check results.
            * print out sums and timing information with number of threads)
            **/
            double time2 = clock();
            add_vector_serial(A, ARRAY_SIZE, &global_sum_serial);
            time2 = clock()-time2;
            double time2ms = time2/CLOCKS_PER_SEC*1000;

            printf("Using %d threads: ", NUM_THREADS);
            printf("\nSum: %d \n", global_sum);
            printf("Execution time: %.4f ms\n", timer);

            printf("\nUsing serial implementation: \n");
            printf("Sum: %d \n", global_sum_serial);
            printf("Execution time: %.4f ms\n", time2ms);
        } else {
            printf("Not enough memory.");
        }
    } else {
        printf("Error: array size must be divisible by the number of threads.");
    }
    exit(0);
}