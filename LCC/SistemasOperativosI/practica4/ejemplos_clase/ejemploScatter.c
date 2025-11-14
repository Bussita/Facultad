#include <stdio.h>
#include <mpi.h>

void main(int argc, char** argv){
	int MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
	
	int process_Rank, size_Of_Comm;
	int distro_Array[4] = {39,72,129,42};
	int scattered_data;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size_Of_Comm);
	MPI_Comm_rank(MPI_COMM_WORLD, &process_Rank);
	if(process_Rank == 0) printf("Se han creado %d procesos.\n",size_Of_Comm);

	MPI_Scatter(&distro_Array[0], 1, MPI_INT, &scattered_data, 1, MPI_INT, 0, MPI_COMM_WORLD);

	printf("Process %d has received: %d \n",process_Rank, scattered_data);
	MPI_Finalize();
}
