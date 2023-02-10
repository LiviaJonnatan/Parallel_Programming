[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-f059dc9a6f8d3a56e377f745f24479a46679e63a5d9fe6f495e02850cd0d8118.svg)](https://classroom.github.com/online_ide?assignment_repo_id=6074253&assignment_repo_type=AssignmentRepo)
# Lab 5 - OpenMP – Work Sharing/Parallel For

In this lab, you will work on the parallelization of code with OpenMP, specifically using the work-sharing directives. 

Regardless of where you develop and test your code, your solutions to both problems will need to be added to your repository, committed and pushed back upstream to GitHub.  Detailed instructions follow.  Review the marking rubric to ensure you have addressed all points required for each problem.  

| **Item**            | **Criteria** |
|----------------|---------------|
|**Assignment:** | Work will be done individually|
|**Assignment Submissions:**| All submissions will be done via GitHub Classroom. **Submit via GitHub**. **Submit only your .c files (Q1.c, Q2.c, Q3.c, and Q4.c) files (answer questions in comments in comment header).**|
|**Due Date:**| Electronic submission Friday, October 29th, 2021 – end of day (23:59).  GitHub Classroom is automatically configured to submit your repositories at this time.  Make sure that you have completed the assignment and pushed the changes upstream (back) to your repository.  **While lab 5 isn't due until October 29th, please start early as you will have a new lab next week!**|

**Rubric:** The assignment will be marked as follows:

| **Rubric**                          | **Max Score** | **Value**  |
|-------------------------------------|:-------------:|:----------:|
|*Question 1*                         |               |            |           |                                                                
|Functional operation (correct code for operation)        |       /5    |            |
|Parallelization (up to 4 marks may be deducted for not ‘reusing’ the same threads))       |       /4    |            |
|Timing of code (report on timing in comments) |       /1     |            |
|-------------------------------------|-------------|----------|
|*Question 2*                         |               |            |           |      
|Removal of data dependency                 |          |            |
|and parallelization/testing of code                 |       /5   |            |
|-------------------------------------|-------------|----------|
|*Question 3*                         |               |            |           |      
| Functional operation (correct code for operation) |   /5 |  | 
| Parallelization of code           |   /5    |   |
|-------------------------------------|-------------|----------|
|*Question 4*                         |               |         |
| Parallelization of function | /7| |
| Timing of code | /1 |
| Report the processing times for 2, 4, 8, 16 threads | /2 |   |
|-------------------------------------|-------------|----------|
|Total                                |       /35     |            |

Total possible marks 35/35

**Question 1 (10 marks)**

In this problem, you will write a C program to perform parallel matrix multiplication using OpenMP. You should first create three matrices `A`, `B`, and `C` then initialize `A` and `B` to some values of your choice (e.g., `a[i][j]=i+j` and `b[i][j]=i*j+1`). Then, perform parallel matrix multiplication, and finally print out the result matrix `C`. In your code, **try to improve the performance by (re)using the same set of threads for initializing `A` and `B` and for calculating `C`**. 

Search online for information about how to do matrix multiplication: https://en.wikipedia.org/wiki/Matrix_multiplication#Illustration.  Also review the course notes. 

Build your solution using the starter code in Q1.c.   Time your implementation and attempt improve the overall performance in terms of the time to compute results using the different techniques discussed in class.   Include your timing results as a comment in the header of your code.

Included in the code are the following statements that will configure the size of the matrix (you  may change the numbers):
```
#define NRA 20  /* number of rows in A */
#define NCA 30  /* number of columns in A = number of rows in B */
#define NCB 10  /* number of columns in matrix B */
```

Take the time to review this operation as it will be revisited when we start our discussion of GPUs.

**Notes:**

* Compare the execution time of the parallel block using omp_get_wtime() which returns the number of seconds that have passed since some time in the past. For details on taking timings, see Section 2.6.4 of the textbook PACHECO-11.

**Question 2 (5 marks)** (Based on Exercise 5.8, p. 264 in PACHECO-11) 

Consider the loop:

```
a[0] = 0;
for(i=1; i<n; i++) a[i] = a[i-1] + i;
```
There’s clearly a loop-carried dependence, as the value of `a[i]` can’t be computed without the value of `a[i-1]`. Can you see a way to eliminate this dependence and parallelize the loop?  Write out the iterations of the loop (try using actual values) and determine the relationship. Recall that to eliminate the dependency, the results of one interaction can't be used in another.   

Build your solution using Q2.c (provided in the repo, with the skeleton code). Test your code to ensure that it is working as expected.  

**Question 3 (10 marks)** (Based on Q 5.2, p. 267 in PACHECO-11)

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

Build your solution using Q3.c (provided in the repo, with the skeleton code). Test your code to ensure that it is working as expected (does it produce a reasonable value for `π`?).  

**Note:** 
* Use the functions in the two files `my_rand.c` and `my_rand.h` (available in repo) to generate a random number between -1 and 1 given a seed value (the seed value could be your thread number, the current time, etc. Note that there are two functions available in these two files: one for generating a random integer and the other for a random double in the range `[0,1]`. You need to read the functions' description and then call the correct function. Then, you need to come up with a mathematical formula that uses the generated random number from 0 to 1 in order to compute a random number from -1 to 1 (i.e., map the range `[0,1]` to the range `[-1,1]`).
* If you are compiling using the commandline, you will need to supply the included file to link to you program as: `gcc Q3.c my_rand.c -o Q3.a -fopenmp` 

**Question 4 (10 marks)**   

Examine the code in the folder src/Q4/ , specifically Q4.c.  You will be working to parallelize this code that transforms the image using the QDBMP - Quick n' Dirty BMP library. Read the “readme.txt” for copyright info and for some background about the library used.  You will only need to modify Q4.c (but during compilation, you will need to compile and link the library). 

The first three statement in the main function define the input and output images and the required processing. Play with the values of these constants and check the output. 

Your goal is to reduce the processing time by dividing the workload among several threads (e.g., 4 threads) using OpenMP (use `parallel for`). To verify the correctness of your code, check the output image as well as the processing time (printed out in the console). Report the processing times for 2, 4, 8, 16 threads as a comment in your code.

Would it be better to use nested parallel for loops (i.e., to parallelize both for x and for y loops)? Test using your code and explain.

**Note:**  
* If you are compiling using the command line, you will need to supply the included file to link to you program as: `gcc Q4.c qdbmp.c -o Q4.a -fopenmp` 

**Submission Details**

When you are complete with the assignment, ensure all files are added and committed to your repository and that your repository is pushed back upstream to GitHub.  You can @mention your respective TA which will let them know you have completed the assignment.  **You will then submit the URL to your repository via the lab submission link in Canvas.  This link will be used by the TA's to grade your submission**.  **Your submission must be pushed back to the GitHub classroom before the assignment due date and time**.  Your TA's will provide direct feedback (if required), via your repository. 
