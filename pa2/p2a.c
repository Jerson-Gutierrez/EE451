#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <pthread.h>


int main(int argc, char** argv){
	
    struct timespec start, stop;
    double time;
	// the matrix is stored in a linear array in row major fashion
	if(clock_gettime(CLOCK_REALTIME, &start) == -1) perror("clock gettime");
	//  Your code goes here (you may define functions outside of main)

	
	// measure the end time here
	if(clock_gettime(CLOCK_REALTIME, &stop) ==-1) perror("clock gettime");
	//t holds the time it took the program to run in nanoseconds
	time = (stop.tv_sec - start.tv_sec) + (double)(stop.tv_nsec - start.tv_nsec)/1e9;
	// print out the execution time here
    
    return 0;
}