
/**
 * Starter code for Lab #5 - Q3
 * 
 * Review the @todo and complete.s
 * 
 * To compile from cmdline:  gcc Q3.c my_rand.c -o Q3.a -fopenmp 
 * 
 **/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/** added include for random generator */
#include "my_rand.h"

#define NUM_THREADS 4

int main(void){
    double pi_estimate;

	long long int number_in_circle = 0;
	int seed = 4;
	/** @todo correctly declare and initialize number_of_tosses and set it to a reasonable number of flips*/
	int number_of_tosses = 10000000;
	/** @todo correctly declare toss, x, y, distance_squared */
	int toss = 0;
	double x, y, distance_squared = 0;
	
	#pragma omp parallel for num_threads(NUM_THREADS) shared(number_of_tosses) private(toss,x,y,distance_squared) reduction(+:number_in_circle)
		for (toss = 0; toss < number_of_tosses; toss++) {
			/** @todo x = random double between -1 and 1; */
			x = (my_drand(&seed)*2)-1;
			/** @todo y = random double between -1 and 1; */
			y = (my_drand(&seed)*2)-1;
			distance_squared = x * x + y * y;
			if (distance_squared <= 1)
				number_in_circle++;
		}

	pi_estimate = 4 * number_in_circle / ((double) number_of_tosses);

	printf("Estimated pi: %e\n", pi_estimate);

	return 0;

}