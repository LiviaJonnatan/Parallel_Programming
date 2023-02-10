[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-f059dc9a6f8d3a56e377f745f24479a46679e63a5d9fe6f495e02850cd0d8118.svg)](https://classroom.github.com/online_ide?assignment_repo_id=5905908&assignment_repo_type=AssignmentRepo)
# Lab 3 - OpenMP - Parallelization, Critical Sections, Atomics and Locks

In this lab, you will work on the parallelization of code with OpenMP, specifically the `#pragma omp parallel` directive.  You will also investigate the performance and operation of `critical` and `atomic` directives to protect critical sections of code. 

Regardless of where you develop and test your code, your solutions to both problems will need to be added to your repository, committed and pushed back upstream to GitHub.  Detailed instructions follow.  Review the marking rubric to ensure you have addressed all points required for each problem.  

| **Item**            | **Criteria** |
|----------------|---------------|
|**Assignment:** | Work will be done individually|
|**Assignment Submissions:**| All submissions will be done via GitHub Classroom. **Submit via GitHub**. **Submit only your .c files (Q1.c, Q2.c, Q3.c and Q3.txt) files.**|
|**Due Date:**| Electronic submission Friday, October 15th, 2021 – end of day (23:59).  GitHub Classroom is automatically configured to submit your repositories at this time.  Make sure that you have completed the assignment and pushed the changes upstream (back) to your repository.  **While lab 3 isn't due until October 15th, please start early as you will have a new lab next week!**|

**Rubric:** The assignment will be marked as follows:

| **Rubric**                          | **Max Score** | **Value**  |
|-------------------------------------|:-------------:|:----------:|
|*Question 1*                         |               |            |
|Serial Code                 |       /3     |            |
|Parallel Code                 |       /6     |            |
|Testing (and error checking) of code (up to -4 for not handling/checking errors)  |       /5      |            |
|Reporting correct results as a comment|       /1      |            |
|-------------------------------------|-------------|----------|
|*Question 2*                         |               |            |                                                                
|Function operation (4 for add_vector, 4 setup main/parallel call, +1 timing)                      |       /9     |            |
|Testing of code  |       /3      |            |
|Reporting results as a comment/question answer|       /3      |            |
|-------------------------------------|-------------|----------|
|*Question 3*                         |               |            |                                                                
|Running and output in text file  |       /3      |            |
|-------------------------------------|-------------|----------|
|Total                                |       /33     |            |

Total possible marks 30/30

**Question 1 (15 marks)**
Develop a C function that returns an `int*` pointer to a vector A initialized as `A[i]=i`, or returns NULL if the function fails.   Build your solution using Q1.c (provided in the repo, with the function prototype).  You can either open this and build it with Eclipse or use the command line (don't forget to use -fopenmp).  

Write the sequential code for the function. Use the header: 

`int* vecCreate (int size)`

Write the OpenMP implementation of the function. Use the header: 

`int* vecCreateOpenMP(int size, int num_thread)`

Here, you will try to speed up the vector initialization by dividing the work among several threads where each thread will initialize a segment of the vector. For example, if num_thread = 2 and size = 10, thread 0 will initialize elements 0 to 4 and thread 1 will initialize elements 5 to 9. Using #pragma omp parallel num_threads( num_thread ). This is similar to the problem from last week where you have to divide the array across a number of threads.   Your function should only work if the vector size is divisible by the number of threads. If not, your function should display an error message and return NULL. The parallelization needs to use the `#pragma omp parallel` directive

Test both functions with a 50-million element vector (and 4 threads for the second function). Your test code should print the value of the last element in the vector along with the time taken for each function to complete.  Each function needs to allocate the array on the heap (hint: `malloc`) and then return the pointer (as per the function prototype in the starter code) (see Q2 - lab 2).  Your code also needs to handle the situation where it can't successfully handle the allocation of the required memory; ensure to handle this condition as well.  When you are developing this solution, if you run into a memory allocation issue when allocating 50 million integers, test with a smaller value.  Report the results as a comment in your code.

**Sample run 1: (successful)**

```Using serial code
v[49999999] = 49999999
Time: 144.00 ms

Using OpenMP with 4 threads:
v[49999999] = 49999999
Time: 59.00 ms
```

***Sample run 2: (num_thread not divisible by size)***
```Using serial code
v[49999999] = 49999999
Time: 144.00 ms

Using OpenMP with 3 threads: Error: number of threads must be divisible by vector size.
```

**Sample run 3: (unsuccessful memory allocation)**
```Not enough memory.
Not enough memory.
```

**Note:**
* Lookup the function `clock()` from `time.h`.

**Question 2 (15 marks)**
In this question, you will use OpenMP to parallelize the summation of values in an array.  Build your solution using Q2.c (provided in the repo, with the function prototype).   You can either open this and build it with Eclipse or use the command line (don't forget to use -fopenmp).  Unlike the pthreads example, you will need to write more code, handling the slicing of the array (use a similar approach as discussed in class example). 

In the code there are a series of `@todo` statements that need to be completed:
1. The size of the array (as previous) must be a multiple of the number of threads.
2. Initialize A as noted in the code using rand() (see `@todo` in code comments).
3. Add code to properly sum up the entire array.  The function will take in a pointer to `A` and sum up a portion of the array based on the thread number (see question 4 - lab 2 for how this was accomplished previously) (see `@todo` in code comments). Use the function prototype provided.  The partial sum (as an int) must be stored in a local variable and added to the global variable `global_sum` (int).  Initialize `global_sum` to be `0` before starting the summation
4. Parallelize the code using only the `#pragma omp parallel` directive, adding the ability to change the number of threads created in the team (the function needs to be able to adjust to a different number of threads)
5. In the parallel function, you will need to protect the update of the `global_sum` using the appropriate mutex.  The goal is to have the function run concurrently as much as possible (only protect the updating of the final value).  Here you can choose to use the `critical` or `atomic` directive.  Start by protecting with the `critical` directive.
6. Add timing information for thread creation, addition and cleanup to the code; have it print the results out for a given run.  (see `@todo` in code comments) and compare the results with the serial implementation summing the same array.  
7. Experiment by increasing the number of threads using 2, 4, 8 and 16 threads and increase the size from (1000 to 1 million) * the number of threads (`ARRAY_SIZE`) and record the times in the comments in your code.  Repeat the experiment replacing the `critical` directive with `atomic` and comment on any differences you notice. 

**In there a difference in terms of performance time using the two different strategies?** Please answer in your comments.

Commit your Q2.c file to the lab 2 repository with the results as a comment in the code. 

**Note:**
- The operation is a Reduction operator that reduces the elements of an array into a single element (see https://en.wikipedia.org/wiki/Reduction_operator).  In the coming lectures will we look an OpenMP directive that will assist in reduction for us.
- Compare the execution time of the parallel block using omp_get_wtime() which returns the number of seconds that have passed since some time in the past. For details on taking timings, see Section 2.6.4 of the textbook PACHECO-11. 

Commit your Q2.c file to the lab 2 repository. 

**Question 3 (3 marks)**

In this question, you will examine the behaviour of a code sample that is using `critical` to protect the read-modify-write of a shared variable in one group of threads and `atomic` in another group.  Open Q3.c from the repository. You can either open this and build it with Eclipse or use the command line (don't forget to use -fopenmp). Examine the code in Q4 and understand what it is doing.  You will need to build and run this code.  Modify this code to run multiple times and examine the output.   Answer the following questions in a file called Q3.txt:
1. Are you surprised with the outcomes of this code?  What did you expect to happen?
2. In looking at this code, what do you think the programmer was attempting to do with the `critical` and `atomic` directives? Was it successful?
3. What conclusion can you draw from this? (what can you conclude about the behaviour of `atomic` and `critical`)?

Commit your Q3.txt file along with the corrected running code to the lab 3 repository

**Submission Details**

When you are complete with the assignment, ensure all files are added and committed to your repository and that your repository is pushed back upstream to GitHub.  You can @mention your respective TA which will let them know you have completed the assignment.  **You will then submit the URL to your repository via the lab submission link in Canvas.  This link will be used by the TA's to grade your submission**.  **Your submission must be pushed back to the GitHub classroom before the assignment due date and time**.  Your TA's will provide direct feedback (if required), via your repository. 

