#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) 
{
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (size != 4) 
  {
    if (rank == 0)
      printf("This example requires exactly 4 processes.\n");
    
    MPI_Finalize();
    return 1;
  }

  int sendbuf[4];
  int recvbuf;

  if (rank == 0) 
  {
    sendbuf[0] = 1;
    sendbuf[1] = 2;
    sendbuf[2] = 3;
    sendbuf[3] = 4;
  }

  MPI_Scatter(sendbuf, 1, MPI_INT, &recvbuf, 1, MPI_INT, 0, MPI_COMM_WORLD);
  printf("[No in-place] Rank %d received %d\n", rank, recvbuf);

  MPI_Barrier(MPI_COMM_WORLD);

  // use MPI_IN_PLACE for the root process
  if (rank == 0) 
  {
    sendbuf[0] = 11;
    sendbuf[1] = 12;
    sendbuf[2] = 13;
    sendbuf[3] = 14;

    recvbuf = sendbuf[0];

    MPI_Scatter(sendbuf, 1, MPI_INT, MPI_IN_PLACE, 1, MPI_INT, 0, MPI_COMM_WORLD);
  }
  else 
    MPI_Scatter(NULL, 1, MPI_INT, &recvbuf, 1, MPI_INT, 0, MPI_COMM_WORLD);

  printf("[In-place]    Rank %d received %d\n", rank, recvbuf);

  MPI_Finalize();
  return 0;
}

// EOF
