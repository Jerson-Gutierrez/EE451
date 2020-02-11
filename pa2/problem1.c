#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define h  1024 
#define w  1024

#define input_file  "input.raw"
#define output_file "output.raw"
#define num_clusters 6
#define iterations 30



struct  thread_data{
   	int	thread_id;
   	int sum[num_clusters];
   	int count[num_clusters]; 
   	int start;
   	int end;
};

void *kMeans(void *threadarg){
	struct  thread_data * my_data;
	my_data = (struct thread_data *) threadarg;

	for(int i =0; i < num_clusters; i ++){
		my_data->sum[i] = 0; 
		my_data->count[i] = 0;
	}
	pthread_exit(NULL);
}

int m [num_clusters] = {0, 65, 100, 125, 190, 255};
int main(int argc, char** argv){
	if(arc< 2 || argc >2){
		printf("Invalid commandline arguements" );
		return 0;
	}
	int numPthreads = *(argv[1]) - '0';
	struct  thread_data  thread_data_array[numPthreads];
	int numElementsPerThread = (h*w)/ numPthreads;
    FILE *fp;
    struct timespec start, stop;
  	unsigned char *a = (unsigned char*) malloc (sizeof(unsigned char)*h*w);
    double time;
	// the matrix is stored in a linear array in row major fashion
	if (!(fp=fopen(input_file, "rb"))) {
		printf("can not opern file\n");
		return 1;
	}
	fread(a, sizeof(unsigned char), w*h, fp);
	fclose(fp);
	// measure the start time here

	if(clock_gettime(CLOCK_REALTIME, &start) == -1) perror("clock gettime");
	//  Your code goes here (you may define functions outside of main)

	
	// measure the end time here
	if(clock_gettime(CLOCK_REALTIME, &stop) ==-1) perror("clock gettime");
	//t holds the time it took the program to run in nanoseconds
	time = (stop.tv_sec - start.tv_sec) + (double)(stop.tv_nsec - start.tv_nsec)/1e9;
	// print out the execution time here
	
	
	if (!(fp=fopen(output_file,"wb"))) {
		printf("can not opern file\n");
		return 1;
	}	
	fwrite(a, sizeof(unsigned char),w*h, fp);
    fclose(fp);
    
    return 0;
}