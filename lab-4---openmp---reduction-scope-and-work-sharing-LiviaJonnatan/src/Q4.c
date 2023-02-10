/**
* Starter code for lab 4 - Q4 - based on PACHECO-11 Q5.3(a,b,d) p. 268): 
* @todo develop a function called count_sort_parallel that will be the 
* parallel implementation of the serial version.  Inside the function
* you will need to use the appropriate omp directives. 
**/

/** ANSWER:
 * Q1: variable i, j, and count should be private. Variable a, n,
 * and temp should be shared.
 * 
 * Q2: There is no loop-carried dependencies because each thread has its
 * own copy of i, j, and count. So, each iteration doesn't depend on the
 * results from previous iteration.
 * 
 * Q3: in the code below.
 * 
 * Q4 (n=10,000 and 8 threads):
 * Execution time using serial implementation: 693.6050 ms
 * Execution time using parallel implementation: 308.3820 ms 
 * 
 * Q5: Using the parallel for slicing is much easier than manually slicing
 * the array because by using the parallel for, the system will handle it, which
 * means the programmer does not have to ensure that the array size is divisible
 * by the number of threads. The parallel for will figure it out by itself and
 * even if the array size is not divisible by the number of threads, the code will
 * work perfectly (no bugs).
 * 
**/

#include <stdio.h>       
#include <stdlib.h>
#include <omp.h>
#include <string.h>             //need for memcpy
#include <time.h>

#define ARRAY_SIZE 10000
#define NUM_THREADS 8

/**
 * @param a[] - the input array to sort
 * @param n - the number of elements in the array
 */
void count_sort_serial(int a[], int n);

/**
 * @param a[] - the input array to sort
 * @param n - the number of elements in the array
 */
void count_sort_parallel(int a[], int n);

/* like any C program, program's execution begins in main */
int main(int argc, char* argv[])
{

    //Create two arrays - sort one with parallel sort, sort the other with serial sort
    int A[ARRAY_SIZE];      
    int B[ARRAY_SIZE];

     // for a given array size, generated random values for 
    // each location of A and B 
    for (int i = 0; i < ARRAY_SIZE; i ++)
    {
    	/** Initialize A, B with random values (A and B should be the same) */
        A[i] = rand();
        B[i] = A[i];
    }
    
    /** @todo add timing information **/
    double timer_serial = clock();
    count_sort_serial(A, ARRAY_SIZE);
    timer_serial = ((clock() - timer_serial)/CLOCKS_PER_SEC)*1000;
    printf("Execution time using serial implementation: %.4f ms\n", timer_serial);

    double timer_parallel = omp_get_wtime();
    count_sort_parallel(B, ARRAY_SIZE);
    timer_parallel = (omp_get_wtime() - timer_parallel) * 1000;
    printf("Execution time using parallel implementation: %.4f ms\n", timer_parallel);

    //compare your results - will print message if the serial sort and parallel sort
    //produce different results. 
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        if (A[i] != B[i]) 
        {
            printf("Bad value at idx:%d A:%d B:%d \n", i, A[i], B[i]);
        }         
    }

}

void count_sort_serial(int a[], int n) 
{
	int i, j, count;
	int* temp = malloc(n * sizeof(int));
	for (i = 0; i < n; i++){
		//count all elements < a[i]
		count = 0;
		for (j = 0; j < n; j++)
			if(a[j]<a[i] ||(a[j]==a[i] && j<i))	
				count++;
		//place a[i] at right order
		temp[count] = a[i];
	}
    //this copies the temp results back into the original array
	memcpy(a, temp, n * sizeof(int));
	free(temp);
}

/** @todo complete this function */
void count_sort_parallel(int a[], int n) 
{
	int i, j, count;
	int* temp = malloc(n * sizeof(int));
    #pragma omp parallel for num_threads(NUM_THREADS) private(i,j,count) shared(n)
	    for (i = 0; i < n; i++){
            //count all elements < a[i]
            count = 0;
		    for (j = 0; j < n; j++)
			    if(a[j]<a[i] ||(a[j]==a[i] && j<i))	
				    count++;
		    //place a[i] at right order
		    temp[count] = a[i];
	    }

    //this copies the temp results back into the original array
	memcpy(a, temp, n * sizeof(int));
	free(temp);
}


