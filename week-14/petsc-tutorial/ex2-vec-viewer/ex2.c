static char help[] = "Parallel vector layout.\n\n";

// Include "petscvec.h" so that we can use vectors.  Note that this file
// automatically includes:
// petscsys.h       - base PETSc routines   petscis.h     - index sets
// petscviewer.h - viewers
#include <petsc.h>

int main(int argc,char **argv)
{
  PetscMPIInt    rank;
  PetscInt       i,istart,iend,n = 6,nlocal;
  PetscScalar    v,*array;
  Vec            x;

  PetscInitialize(&argc,&argv,(char*)0,help);
  MPI_Comm_rank(PETSC_COMM_WORLD,&rank);

  // enable passing -n as a command line argument
  PetscOptionsGetInt(NULL,NULL,"-n",&n,NULL);

  // Create a vector, specifying only its global dimension.
  // When using VecCreate(), VecSetSizes() and VecSetFromOptions(),
  // the vector format (currently parallel or sequential) is
  // determined at runtime.  Also, the parallel partitioning of
  // the vector is determined by PETSc at runtime.
  VecCreate(PETSC_COMM_WORLD,&x);
  VecSetSizes(x,PETSC_DECIDE,n);
  VecSetFromOptions(x);

  // PETSc parallel vectors are partitioned by
  // contiguous chunks of rows across the processors.  Determine
  // which vector are locally owned.
  VecGetOwnershipRange(x,&istart,&iend);

  PetscPrintf(PETSC_COMM_SELF, "rank [%d]: istart = %d iend = %d \n", rank, istart, iend );

  // Set the vector elements.
  // - Always specify global locations of vector entries.
  // - Each processor can insert into any location, even ones it does not own
  // - In this case each processor adds values to all the entries,
  // this is not practical, but is merely done as an example
  if( rank == 0 )
  {
    for (i=0; i<n; i++) 
    {
      v    = (PetscReal)(i);
      VecSetValues(x,1,&i,&v,INSERT_VALUES);
    }
  }

  // Assemble vector, using the 2-step process:
  // VecAssemblyBegin(), VecAssemblyEnd()
  // Computations can be done while messages are in transition
  // by placing code between these two statements.
  VecAssemblyBegin(x);
  VecAssemblyEnd(x);

  // View the vector
  VecView(x,PETSC_VIEWER_STDOUT_WORLD);

  // Access the vector values directly. Each processor has access only
  // to its portion of the vector. For default PETSc vectors VecGetArray()
  // does NOT involve a copy
  VecGetLocalSize(x,&nlocal);
  PetscPrintf(PETSC_COMM_SELF, "rank [%d]: nlocal = %d \n", rank, nlocal );
  VecGetArray(x,&array);
  for (i=0; i<nlocal; i++) array[i] = rank + 1;
  VecRestoreArray(x,&array);

  // View the vector
  VecView(x, PETSC_VIEWER_STDOUT_WORLD);

  // Viewer to output in HDF5 format
  PetscViewer pv;
  PetscViewerCreate(PETSC_COMM_WORLD,&pv);
  PetscViewerASCIIOpen(PETSC_COMM_WORLD,"vector.dat",&pv);
  VecView(x, pv);
  PetscViewerDestroy(&pv);

  // Free work space.  All PETSc objects should be destroyed when they
  // are no longer needed.
  VecDestroy(&x);

  PetscFinalize();
  return 0;
}

// EOF
