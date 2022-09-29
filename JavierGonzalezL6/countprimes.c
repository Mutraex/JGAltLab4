/*
Name: Javier Gonzalez
ID: 5754068
I affirm that I wrote this program myself without any help from any
other people or sources from the internet
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <mpi.h>


int main (int argc, char *argv[]) 
{
	int count;            /* Solutions found by this proc */
	double elapsed_time;  /* Time to find, count solutions */
	int global_count;     /* Total number of solutions */
	long int i;
	long int j;
	int id;               /* Process rank */
	int p;                /* Number of processes */
	char hostname[1024];

	MPI_Init (&argc, &argv);

	MPI_Comm_rank (MPI_COMM_WORLD, &id);
	MPI_Comm_size (MPI_COMM_WORLD, &p);

	hostname[1023] = '\0';
	gethostname(hostname, 1023);
	printf("MPI rank %d on host %s\n", id, hostname);

	/* Start timer */
	MPI_Barrier (MPI_COMM_WORLD);
	elapsed_time = - MPI_Wtime();

	count = 0;
	for (i = id; i <= 50000; i ++){
		for(j=2;j<=i; j++){
			if(i==j){
				printf("Prime Found: %d in Process %d\n",i,id);
				count ++;
			}
			else if(i%j == 0)
				break;
		}
	}

	MPI_Reduce (&count, &global_count, 1, MPI_INT, MPI_SUM, 0,
		MPI_COMM_WORLD); 

	/* Stop timer */
	elapsed_time += MPI_Wtime();

	if (!id) {
		printf ("Execution time %8.6f\n", elapsed_time);
		fflush (stdout);
	}
	MPI_Finalize();
	if (!id) printf ("Total prime numbers: %d\n",
		global_count);
	return 0;
}