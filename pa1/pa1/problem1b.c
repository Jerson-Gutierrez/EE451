#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(void){
		int i, j, k;
		struct timespec start, stop; 
		double time;
		int n = 1024; // matrix size is n*n
		
		double **A = (double**) malloc (sizeof(double*)*n);
		double **B = (double**) malloc (sizeof(double*)*n);
		double **C = (double**) malloc (sizeof(double*)*n);
		for (i=0; i<n; i++) {
			A[i] = (double*) malloc(sizeof(double)*n);
			B[i] = (double*) malloc(sizeof(double)*n);
			C[i] = (double*) malloc(sizeof(double)*n);
		}
		
		for (i=0; i<n; i++){
			for(j=0; j< n; j++){
				A[i][j]=i;
				B[i][j]=i+j;
				C[i][j]=0;			
			}
		}
				
		if( clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime");}
		
		// Your code goes here //
		//*******************************//
		int b = 4; 
		int m = n/b; 
		int var;

		for(int l=0;l<n;l+= b){
        	for(int m=0;m<n;m+= b){
                for(int u=0;u<n;u++){
                        for(int v = l; v<((l+b)>n?n:(l+b)); v++){
                                var = 0;
                                for(int w = m; w<((m+b)>n?n:(m+b)); w++){
                                        var += A[u][w]*B[w][v];
                                }
                                C[u][v] += var;
                        }
                }
        	}
		}

		//*******************************//
		
		if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) { perror("clock gettime");}		
		time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;
		
		printf("Number of FLOPs = %lu, Execution time = %f sec,\n%lf MFLOPs per sec\n", 2*n*n*n, time, 1/time/1e6*2*n*n*n);		
		printf("C[100][100]=%f\n", C[100][100]);
		// release memory
		for (i=0; i<n; i++) {
			free(A[i]);
			free(B[i]);
			free(C[i]);
		}
		free(A);
		free(B);
		free(C);
		return 0;
}
