#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char const *argv[])
{
	int npes, myrank;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &npes);  // total number of processes
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	printf("From process %d out of %d, Hello World!\n",myrank, npes);

	int msg = 451;
	if (myrank == 0) {
		// send to 1
		printf("MSG = %d\n", msg);
		MPI_Send(&msg, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	} else if (myrank == 1) {
		// recv from 1
		MPI_Recv(&msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("MSG = %d\n", msg);
		msg++;
		// send to 2
		MPI_Send(&msg, 1, MPI_INT, 2, 1, MPI_COMM_WORLD);
	} else if (myrank == 2) {
		// recv from 2
		MPI_Recv(&msg, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE );
		printf("MSG = %d\n", msg);
		msg++;
		// send to 3
		MPI_Send(&msg, 1, MPI_INT, 3, 2, MPI_COMM_WORLD);
	} else if (myrank == 3) {
		// recv from 3
		MPI_Recv(&msg, 1, MPI_INT, 2, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		// print msg
		printf("MSG = %d\n", msg);
	}
	MPI_Finalize();
	return 0;
}