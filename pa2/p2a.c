#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#define bufferSize 10
#define numThreads 3

struct  thread_data{
   	int thread_ID;
};

// int array[bufferSize] = {0,0,0,0,0,0,0,0,0,0};
int numCookies = 0;
pthread_mutex_t mutex;  

void *producer(void *threadarg){

	struct  thread_data * my_data;
	my_data = (struct thread_data *) threadarg;
	int placedCookies = 0; 
	while(placedCookies<30){
		pthread_mutex_lock(&mutex);
		if(numCookies == 10) pthread_mutex_unlock(&mutex);
		else if(numCookies == 9){
			int currentCookies = numCookies;
			numCookies+=1;
			placedCookies+=1;
			printf("Producer %d placed 1 cookie on the shelf. # of cookies on the shelf changes from %d to %d\n", my_data->thread_ID, currentCookies, numCookies);
			pthread_mutex_unlock(&mutex);
		}
		else{
			int currentCookies = numCookies;
			numCookies += 2;
			placedCookies += 2;
			printf("Producer %d placed 2 cookies on the shelf. # of cookies on the shelf changes from %d to %d\n", my_data->thread_ID, currentCookies, numCookies);
			pthread_mutex_unlock(&mutex);
		}
	}
	pthread_exit(NULL);
}

void *consumer(void *threadarg){

	struct  thread_data * my_data;
	my_data = (struct thread_data *) threadarg;
	int takenCookies = 0; 
	while(takenCookies < 15){
		pthread_mutex_lock(&mutex);
		if(numCookies ==0) pthread_mutex_unlock(&mutex);
		else{
			int currentCookies = numCookies;
			numCookies-= 1;
			takenCookies+=1;
			printf("Consumer removed 1 cookie from the shelf. # of cookies on the shelf changes from %d to %d\n",currentCookies, numCookies);
			pthread_mutex_unlock(&mutex);
		}
	}
	pthread_exit(NULL);
}

int main(int argc, char** argv){
	int rc; 
    struct timespec start, stop;
    double time;
    pthread_t  threads[numThreads];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_mutex_init(&mutex, NULL);
    struct  thread_data  thread_data_array[numThreads];
    thread_data_array[0].thread_ID = 1; 
    thread_data_array[1].thread_ID = 2;
    thread_data_array[2].thread_ID = 1;
	// the matrix is stored in a linear array in row major fashion
	if(clock_gettime(CLOCK_REALTIME, &start) == -1) perror("clock gettime");
	//  Your code goes here (you may define functions outside of main)
	rc = pthread_create(&threads[0], NULL, producer, (void *) &thread_data_array[0] );
	if (rc) { printf("ERROR; return code from pthread_create() is %d\n", rc); exit(-1);}
	rc = pthread_create(&threads[1], NULL, consumer, (void *) &thread_data_array[1] );
	if (rc) { printf("ERROR; return code from pthread_create() is %d\n", rc); exit(-1);}
	rc = pthread_create(&threads[2], NULL, consumer, (void *) &thread_data_array[2] );
	if (rc) { printf("ERROR; return code from pthread_create() is %d\n", rc); exit(-1);}

	rc = pthread_join(threads[0], NULL);
	if (rc) { printf("ERROR; return code from pthread_join() is %d\n", rc); exit(-1);}
	rc = pthread_join(threads[1], NULL);
	if (rc) { printf("ERROR; return code from pthread_join() is %d\n", rc); exit(-1);}
	rc = pthread_join(threads[2], NULL);
	if (rc) { printf("ERROR; return code from pthread_join() is %d\n", rc); exit(-1);}
	// measure the end time here
	if(clock_gettime(CLOCK_REALTIME, &stop) ==-1) perror("clock gettime");
	//t holds the time it took the program to run in nanoseconds
	time = (stop.tv_sec - start.tv_sec) + (double)(stop.tv_nsec - start.tv_nsec)/1e9;
	// print out the execution time here
    pthread_mutex_destroy(&mutex);
    return 0;
}