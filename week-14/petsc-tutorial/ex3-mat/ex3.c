static char help[] = "Illustrate the use of MatResetPreallocation.\n";

#include "petscmat.h"

int main(int argc,char **argv)
{
  Mat             A;
  MPI_Comm        comm;
  PetscMPIInt     rank;
  PetscInt        n=5,m=5,*dnnz,*onnz,i,rstart,rend,M,N;

  PetscInitialize(&argc,&argv,0,help);
  comm = MPI_COMM_WORLD;
  MPI_Comm_rank(comm, &rank);
  PetscMalloc2(m,&dnnz,m,&onnz);
  for (i=0; i<m; i++) 
  {
    dnnz[i] = 1;
    onnz[i] = 1;
  }
  MatCreateAIJ(comm,m,n,PETSC_DETERMINE,PETSC_DETERMINE,PETSC_DECIDE,dnnz,PETSC_DECIDE,onnz,&A);
  MatSetFromOptions(A);
  MatSetUp(A);
  PetscFree2(dnnz,onnz);

  MatSetOption(A,MAT_NEW_NONZERO_ALLOCATION_ERR,PETSC_TRUE);
  MatGetOwnershipRange(A,&rstart,&rend);
  MatGetSize(A,&M,&N);
  PetscPrintf(comm, "Matrix size is %d by %d \n", M, N);
  PetscPrintf(PETSC_COMM_SELF, "rank [%d] rstart = %d , rend = %d \n", rank, rstart, rend);
  for (i=rstart; i<rend; i++) 
  {
    MatSetValue(A,i,i,2.0,INSERT_VALUES);
    if (rend<N) 
      MatSetValue(A,i,rend,1.0,INSERT_VALUES);
  }
  MatAssemblyBegin(A,MAT_FINAL_ASSEMBLY);
  MatAssemblyEnd(A,MAT_FINAL_ASSEMBLY);
  MatView(A,PETSC_VIEWER_STDOUT_WORLD);
  MatDestroy(&A);
  PetscFinalize();
  return 0;
}

// EOF
