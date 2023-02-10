# Lab 5 - OpenMP – Work Sharing/Parallel For
© 2021 Dr. Scott Fazackerley, Dr. Abdallah Mohamed

In this lab, you will work on the parallelization of code with OpenMP, specifically using the work-sharing directives. 

**Question 1**

In this problem, you will write a C program to perform parallel matrix multiplication using OpenMP. You should first create three matrices `A`, `B`, and `C` then initialize `A` and `B` to some values of your choice (e.g., `a[i][j]=i+j` and `b[i][j]=i*j+1`). Then, perform parallel matrix multiplication, and finally print out the result matrix `C`. In your code, **try to improve the performance by (re)using the same set of threads for initializing `A` and `B` and for calculating `C`**. 

Search online for information about how to do matrix multiplication: https://en.wikipedia.org/wiki/Matrix_multiplication#Illustration.  Also review the course notes. 

Build your solution using the starter code in Q1.c.   Time your implementation and attempt improve the overall performance in terms of the time to compute results using the different techniques discussed in class.   Include your timing results as a comment in the header of your code.

Included in the code are the following statements that will configure the size of the matrix (you  may change the numbers):
```
#define NRA 20  /* number of rows in A */
#define NCA 30  /* number of columns in A = number of rows in B */
#define NCB 10  /* number of columns in matrix B */
```

**Question 2** (Based on Exercise 5.8, p. 264 in PACHECO-11) 

Consider the loop:

```
a[0] = 0;
for(i=1; i<n; i++) a[i] = a[i-1] + i;
```
There’s clearly a loop-carried dependence, as the value of `a[i]` can’t be computed without the value of `a[i-1]`. Can you see a way to eliminate this dependence and parallelize the loop?  Write out the iterations of the loop (try using actual values) and determine the relationship. Recall that to eliminate the dependency, the results of one interaction can't be used in another.   

**Question 3** (Based on Q 5.2, p. 267 in PACHECO-11)

Suppose we toss darts randomly at a square dartboard, whose bullseye is at the origin, and whose sides are 2 feet in length. Suppose also that there’s a circle inscribed in the square dartboard. The radius of the circle is 1 foot, and it’s area is `π` square feet. If the points that are hit by the darts are uniformly distributed (and we always hit the square), then the number of darts that hit inside the circle should approximately satisfy the equation 
```
  (number in circle)/(total number of tosses) = π/4
```
since the ratio of the area of the circle to the area of the square is `π/4`. 

We can use this formula to estimate the value of `π` with a random number generator:
```
number_in_circle = 0;
for(toss = 0; toss < number_of_tosses; toss++) {
    x = random double between -1 and 1;
    y = random double between -1 and 1;
    distance_squared = x * x + y * y;
    if (distance_squared <= 1) number_in_circle++;
}
pi_estimate = 4*number_in_circle/((double) number_of_tosses);
```
This is called a “Monte Carlo” method, since it uses randomness (the dart tosses).

Write an OpenMP program that uses a Monte Carlo method to estimate `π`. Read in the total number of tosses before forking any threads. Use a reduction clause to find the total number of darts hitting inside the circle. Print the result after joining all the threads. You may want to use `long long int` for the number of hits in the circle and the number of tosses, since both may have to be very large to get a reasonable estimate of `π`.


**Note:** 
* Use the functions in the two files `my_rand.c` and `my_rand.h` (available in repo) to generate a random number between -1 and 1 given a seed value (the seed value could be your thread number, the current time, etc. Note that there are two functions available in these two files: one for generating a random integer and the other for a random double in the range `[0,1]`. You need to read the functions' description and then call the correct function. Then, you need to come up with a mathematical formula that uses the generated random number from 0 to 1 in order to compute a random number from -1 to 1 (i.e., map the range `[0,1]` to the range `[-1,1]`).
* If you are compiling using the commandline, you will need to supply the included file to link to you program as: `gcc Q3.c my_rand.c -o Q3.a -fopenmp` 

**Question 4**   

Examine the code in the folder src/Q4/ , specifically Q4.c.  You will be working to parallelize this code that transforms the image using the QDBMP - Quick n' Dirty BMP library. Read the “readme.txt” for copyright info and for some background about the library used.  You will only need to modify Q4.c (but during compilation, you will need to compile and link the library). 

The first three statement in the main function define the input and output images and the required processing. Play with the values of these constants and check the output. 

Your goal is to reduce the processing time by dividing the workload among several threads (e.g., 4 threads) using OpenMP (use `parallel for`). To verify the correctness of your code, check the output image as well as the processing time (printed out in the console). Report the processing times for 2, 4, 8, 16 threads as a comment in your code.

Would it be better to use nested parallel for loops (i.e., to parallelize both for x and for y loops)? Test using your code and explain.
