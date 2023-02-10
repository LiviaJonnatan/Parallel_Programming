4/**
 * Lab 3 - Q3.c 
 * Code for analyis of atomic/critical section behaviour
 **/


#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_RUNS 100        /** @todo adjust to run a number of times **/

int main(int argc, char* argv[])
{


    for (int i = 0; i < NUM_RUNS; i++)
    {
        int x = 0;
        #pragma omp parallel num_threads(100)
        {
            int id = omp_get_thread_num();
            if(id < 50){  //first 50 threads increment x
                # pragma omp atomic
                x++;
            }else{    //other 50 threads decrement x
                # pragma omp atomic  
                x--;
            }
        }
        printf("%d",x);
    }
}
