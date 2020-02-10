#include <iostream>
// #include <stdlib.h>
// #include <stdio.h>
#include <time.h>
// #include <string>
using namespace std;
int main(int argc, char* argv[]){
	cout<<"4"<<endl;
	struct timespec start, stop;
	const int n = 4000;
	cout<<"5"<<endl;
	double A [n][n];
	double B [n][n];
	double C [n][n];
	cout<<"1"<<endl;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			A[i][j] = (double)i; 
			B[i][j] = (double)i + (double)j; 
			C[i][j] = (double)0; 
		}
	}
	double time;
	cout<<"2"<<endl; 
	if(clock_gettime(CLOCK_REALTIME, &start) == -1) perror("clock gettime");
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			for(int k = 0; k<n; k++){
				C[i][j] = C[i][j] + (A[i][k]* B[k][j] );
			}
		}
	}
	cout<<"3"<<endl;

	if(clock_gettime(CLOCK_REALTIME, &stop) ==-1) perror("clock gettime");
	//t holds the time it took the program to run in nanoseconds
	time = (stop.tv_sec - start.tv_sec) + (double)(stop.tv_nsec - start.tv_nsec)/1e9;
	cout<<"Number of FLOPS = "<<2*n<<", Execution time: "<<time<< " ns, "<<endl<<1/time/1e6*2*n<<" MFLOPS per sec"<<endl;;
	cout<<"C[100][100] = "<<C[100][100]<<endl;

	return -1;
}
