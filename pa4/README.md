# EE451

Name: Jerson Gutierrez (2833544170)
email: jersongu@usc.edu

Programming Assignment 4

To run the ring.c file: first setup using : "source /usr/usc/openmpi/default/setup.sh"
To COMPILE type: mpicc -o run -O3 ring.c 
To RUN type: srun -n4 ./run


To run the mm1.cu and mm2.cu fitst setup using:  "source /usr/usc/cude/default/setup.sh"
To COMPILE type: nvcc -o run1 -O3 mm1.cu (for mm1.cu)
				 nvcc -o run2 -O3 mm2.cu (for mm2.cu)

To RUN type: srun -n1 --ges=gpu:1 ./run1 (for mm1.cu)
			 srun -n1 --ges=gpu:1 ./run2 (for mm2.cu)


Screenshots of the execution time and performance for the assignment are included. Along with the output of the  C[451][451] value. 
