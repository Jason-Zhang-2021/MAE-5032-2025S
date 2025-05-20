#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int tag = 42;
  int message;
  if(rank == 0)
  {
    for(int i=1; i<size; ++i)
    {
      message = i * i;
      MPI_Send(&message, 1, MPI_INT, i, tag, MPI_COMM_WORLD);
    }
  }
  else
  {
    MPI_Status status;
    MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, 
        MPI_COMM_WORLD, &status);
    printf("Rank %d received the following integer: %d from process %d with tag %d\n",
        rank, message, status.MPI_SOURCE, status.MPI_TAG);
  }

  MPI_Finalize();
  return 0;
}

// EOF
