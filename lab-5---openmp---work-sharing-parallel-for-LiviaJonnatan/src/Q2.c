
/**
 * Starter code for Lab #5 - Q2
 * 
 **/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_THREADS 4

int main(void){
    int n = 100;
    int i;
    int a[n];

    a[0] = 0; //rewriting the sequence: a_i = 0.5i^2 + 0.5i
    #pragma omp parallel for num_threads(NUM_THREADS) shared(a,n) private(i)
        for (i=1; i<n; i++){
            a[i] = (0.5*i*i) + (0.5*i);
        }

    //for testing purpose
    for (i=1; i<n; i++){
        printf("%d ", a[i]);
    }
}