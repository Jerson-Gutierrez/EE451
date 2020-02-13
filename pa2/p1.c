#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <float.h>

#define h  1024 
#define w  1024

#define input_file  "input.raw"
#define output_file "output.raw"
#define num_clusters 6
#define iterations 30



double m [num_clusters] = {0, 65, 100, 125, 190, 255};

struct  thread_data{
   	double sum[num_clusters];
   	int count[num_clusters]; 
   	int start;
   	int end;
   	unsigned char * data;
};

void *kMeans(void *threadarg){
	struct  thread_data * my_data;
	my_data = (struct thread_data *) threadarg;
	int start = my_data->start;
	int end = my_data->end;
	for(int i =0; i < num_clusters; i ++){
		my_data->sum[i] = 0; 
		my_data->count[i] = 0;
	}
	
	double dist[6] = {0,0,0,0,0,0}; 
	for(int k = start; k <= end; k++){

		double minimum = DBL_MAX;
		int index = 0;  
		for(int z = 0; z < 6; z++){
			dist[z] = abs(((int)my_data->data[k]) -m[z]);
			if(dist[z] < minimum ){
				minimum = dist[z];
				index = z; 
			}
		}
		
		my_data->sum[index] += (double) my_data->data[k]; 
		my_data->count[index]+=1; 
	}

	pthread_exit(NULL);
}
int main(int argc, char** argv){
	if(argc< 2 || argc >2){
		printf("Invalid commandline arguements" );
		return 0;
	}
	int numPthreads = *(argv[1]) - '0';
	struct  thread_data  thread_data_array[numPthreads];
	int numElementsPerThread = (h*w)/ numPthreads;
	int rc, i, j; 
    FILE *fp;
    struct timespec start, stop;
  	unsigned char *a = (unsigned char*) malloc (sizeof(unsigned char)*h*w);
  	pthread_t  threads[numPthreads];
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

	for(int j = 0;j < 30 ; j++){

		for(i=0; i<numPthreads; i++) {	  
			thread_data_array[i].start = i* numElementsPerThread ;
			thread_data_array[i].end =  (i* numElementsPerThread) + numElementsPerThread -1;
			thread_data_array[i].data = a; 
			//printf("start: %d, end: %d\n", thread_data_array[i].start, thread_data_array[i].end);
			rc = pthread_create(&threads[i], NULL, kMeans, (void *) &thread_data_array[i] );
			if (rc) { printf("ERROR; return code from pthread_create() is %d\n", rc); exit(-1);}
		}
		for(i=0; i<numPthreads; i++) {	  
			rc = pthread_join(threads[i], NULL);
			if (rc) { printf("ERROR; return code from pthread_join() is %d\n", rc); exit(-1);}
		}
		
		for(int y = 0; y < num_clusters; y++){
			double sum_total= 0;
			int count_total = 0;
			for(int r = 0; r< numPthreads ;r++){
				sum_total += thread_data_array[r].sum[y];
				count_total += thread_data_array[r].count[y]; 
			}
			printf("sum total: %f, count_total: %d\n", sum_total, count_total);
			if(sum_total == 0) {
				sum_total = m[y];
				 
			}
			m[y] = sum_total/ count_total;
		}
		printf("At Iteration: %d\n", j);
		for(int e = 0; e < 6; e++){
			printf("\tcluster %d's new mean: %f\n", e, m[e]);
		}
	}

	
	// measure the end time here
	if(clock_gettime(CLOCK_REALTIME, &stop) ==-1) perror("clock gettime");
	//t holds the time it took the program to run in nanoseconds
	time = (stop.tv_sec - start.tv_sec) + (double)(stop.tv_nsec - start.tv_nsec)/1e9;
	// print out the execution time here
	double dist[6] = {0,0,0,0,0,0};
	for(int i = 0 ; i < h*w; i++){
		double minimum = DBL_MAX;
		int index = 0;  
		for(int z = 0; z < 6; z++){
			dist[z] = abs(((int)a[i]) -m[z]);
			if(dist[z] < minimum ){
				minimum = dist[z];
				index = z; 
			}
		}
		a[i] = (char)m[index];
	}
	
	if (!(fp=fopen(output_file,"wb"))) {
		printf("can not opern file\n");
		return 1;
	}	
	fwrite(a, sizeof(unsigned char),w*h, fp);
    fclose(fp);
    
    return 0;
}