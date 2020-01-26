#include <iostream>
#include <time.h>
#include <string>
using namespace std;
// struct timespec{
// 	time_t tv_sec;
// 	long tv_nsec;
// }

int main(int argc, char*argv[]){

	struct timespec start, stop;
	if(argc != 2) {
		cerr<<"Insufficient inputs"<<endl; 
		return -1;
	}
	int n = stoi(argv[1]);
	cout<<n<<endl;
	if(n ==0){
		cerr<<"0 is not a valid input"<<endl;
		return -1;
	}
	if(n %4 != 0){
		cerr<<"The size of the matrix is not factor of 4."<<endl;
	}

	double A [n][n];
	double B [n][n];
	double C [n][n];
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			A[i][j] = (double)i; 
			B[i][j] = (double)i + j; 
			C[i][j] = (double)0; 
		}
	}
	double time; 
	if(clock_gettime(CLOCK_REALTIME, &start) == -1) perror("clock gettime");
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			for(int k = 1; k<n; k++){
				C[i][j] = C[i][j] + (A[i][k]* B[k][j] );
			}
		}
	}

	if(clock_gettime(CLOCK_REALTIME, &stop) ==-1) perror("clock gettime");
	//t holds the time it took the program to run in nanoseconds
	time = (stop.tv_sec - start.tv_sec) + (double)(stop.tv_nsec - start.tv_nsec)/1e9;
	cout<<"Number of FLOPS = "<<2*n*n*n<<", Execution time: "<<time<< " ns, "<<endl<<1/time/1e6*2*n*n*n<<" MFLOPS per sec"<<endl;;

}