
/**
 * Lab 3 - Q1.c
 * Starter Code
 *
 * Notes: 
 *  @todo use clock() from time.h to time the code
 *  @todo make sure to use malloc inside each function
 *  @todo make sure you free resources when done.
 * 
 * Useful things:
 *      Get time:               double t = clock();
 *      Convert time to ms:     (1000 * t / CLOCKS_PER_SEC)
 * 
 **/

/** OUTPUT 2 THREADS, 50 MILLION SIZE
 * v[49999999] = 49999999
 * Time: 246.66 ms
 * Using OpenMP with 2 threads: 
 * v[49999999] = 49999999
 * Time: 405.27 ms
**/

/** OUTPUT 4 THREADS, 50 MILLION SIZE
 * v[49999999] = 49999999
 * Time: 252.91 ms
 * Using OpenMP with 4 threads: 
 * v[49999999] = 49999999
 * Time: 458.53 ms
**/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

#define numThreads 2
#define array_size 50000000

/** Serial Code **/
int* vecCreate(int size);

/** Parallel Code **/
int* vecCreateOpenMP(int size, int num_thread);

/** Main method
 * -Make sure to include testing!
 **/
int main() {
    int *AS = NULL;
    int *AO = NULL;

    double ts = clock();
    AS = vecCreate(array_size);
    ts = clock() - ts;
    double tsms = ts/CLOCKS_PER_SEC*1000;
    
    if (AS != NULL){
        printf("v[%d] = %d\n", (array_size-1), AS[array_size-1]);
        printf("Time: %.2f ms\n", tsms);
    } else {
        printf("Not enough memory.");
    }
    
    printf("Using OpenMP with %d threads: ", numThreads);

    if ((array_size % numThreads == 0)){
        double to = clock();
        AO = vecCreateOpenMP(array_size, numThreads);
        to = clock() - to;
        double toms = to/CLOCKS_PER_SEC*1000;
    
        if (AO != NULL){
            printf("\nv[%d] = %d\n", (array_size-1), AO[array_size-1]);
            printf("Time: %.2f ms\n", toms);
        } else {
            printf("Not enough memory.");
        }
    } else {
        printf("Error: vector size must be divisible by number of threads.\n");
    }
}

int* vecCreate(int size) {
    int *A = (int*) malloc(size*sizeof(int));
    if (A != NULL){
        for (int i = 0; i < size; i++){
            A[i] = i;
        }
        return A;
    } else {
        return NULL;
    }
}

int* vecCreateOpenMP(int size, int num_thread){
    int n = size / num_thread;
    int *A = (int*) malloc(size * sizeof(int));
    if (A != NULL){
        #pragma omp parallel num_threads(num_thread)
        {
            int tid = omp_get_thread_num();
            int start = n * tid;
            int end = start + n - 1;
            for (int i = start; i <= end; i++){
                A[i] = i;
            }
        }
        return A;
    } else {
        return NULL;
    }
}