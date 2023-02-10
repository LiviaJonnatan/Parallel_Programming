/**
 * Starter code for Lab #5 - Q1
 * 
 **/

/** ANSWER:
 * Serial implementation: 0.7790 ms.
 * 
 * Reusing the same set of threads for initialization and 
 * calculation and using collapse: 0.5160 ms.
 * 
**/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define NUM_THREADS 4        /** number of threads to request **/

#define NRA 20                  /** number of rows in matrix A **/
#define NCA 30                  /** number of columns in matrix A **/
#define NCB 10                  /** number of columns in matrix B **/

int main(void){
	
    int my_rank, num_threads, i, j, k, chunk;
	
    double a[NRA][NCA];         /** matrix A to be multiplied **/
	double b[NCA][NCB];         /** matrix B to be multiplied **/
	double c[NRA][NCB];         /** result matrix C **/
	


    /*** Spawn a parallel region explicitly scoping all variables 
     * Be mindful of what needs to be shared and what needs to be private 
     **/
	/** @todo complete the operations for the matrix multiplication (start with serial implementation first)
    /** @todo initialization of matrix can be parallelized!! 
    * using parallel for as well! **/

    double timer = omp_get_wtime();
	#pragma omp parallel num_threads(NUM_THREADS) shared(a,b,c) private(i,j,k)
	{
		#pragma omp for collapse (2)
			for (i = 0; i < NRA; i++) {
				for (j = 0; j < NCA; j++){
					a[i][j] = i*j;
				}
			}
		#pragma omp for collapse (2)
			for (i = 0; i < NCA; i++) {
				for (j = 0; j < NCB; j++){
					b[i][j] = i*j+1;
				}
			}
		#pragma omp for collapse (2)
			for (i = 0; i < NRA; i++) {
				for (j = 0; j < NCB; j++){
					c[i][j] = 0;
				}
			}
		#pragma omp for collapse(3)
			for (i = 0; i < NRA; i++)
				for (j = 0; j < NCB; j++)
					for (k = 0; k < NCA; k++)
						c[i][j] += a[i][k] * b[k][j]; 
	}
	timer = (omp_get_wtime() - timer) * 1000;

	printf("Execution time: %.4f ms.\n", timer);

	/*** Print results ***/
	printf("Result Matrix:\n");
	for (i = 0; i < NRA; i++) {
		for (j = 0; j < NCB; j++)
			printf("%6.2f   ", c[i][j]);
		printf("\n");
	}
return 0;
}
