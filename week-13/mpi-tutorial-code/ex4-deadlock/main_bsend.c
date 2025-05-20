#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int tag1 = 42, tag2 = 43;
  int sendMessage, recvMessage;
  
  int bufsize = 2 * (MPI_BSEND_OVERHEAD + sizeof(int));
  void *buffer = malloc(bufsize);
  MPI_Buffer_attach(buffer, bufsize);
  
  if(rank == 0)
  {
    sendMessage = 7;
    MPI_Bsend(&sendMessage, 1, MPI_INT, 1, tag1, MPI_COMM_WORLD);
    MPI_Recv(&recvMessage, 1, MPI_INT, 1, tag2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }
  else if(rank == 1)
  {
    sendMessage = 14;
    MPI_Bsend(&sendMessage, 1, MPI_INT, 0, tag2, MPI_COMM_WORLD);
    MPI_Recv(&recvMessage, 1, MPI_INT, 0, tag1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  printf("Rank %d received the following integer: %d\n", rank, recvMessage);
  
  void *detach_buffer;
  int detach_size;
  MPI_Buffer_detach(&detach_buffer, &detach_size);
  free(detach_buffer);

  MPI_Finalize();
  return 0;
}

// EOF
