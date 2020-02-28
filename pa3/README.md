# EE451

Name: Jerson Gutierrez (2833544170)
email: jersongu@usc.edu

Programming Assignment 3

To compile type: “gcc -O3 -o run openmp example.c -fopenmp 
Type: “srun -n1 -c8 ./run (to run on hpc, where -c is the number of threads. Ran with 
-c1, -c2, -c4, -c8)



Currently the Sub-blocks of the matrix are set to size 16( b value);
Change the variable b to 8, and 4 to test with different sub-block sizes.

