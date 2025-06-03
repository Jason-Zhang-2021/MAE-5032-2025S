static char help[] = "Introductory example that illustrates printing.\n\n";

// Concepts: introduction to PETSc;
// Concepts: printing in parallel
// Processors: n

#include <petscsys.h>
int main(int argc,char **argv)
{
  PetscErrorCode ierr;
  PetscMPIInt    rank,size;

  // Every PETSc routine should begin with the PetscInitialize() routine.
  // argc, argv - These command line arguments are taken to extract the options
  //              supplied to PETSc and options supplied to MPI.
  // help       - When PETSc executable is invoked with the option -help,
  //              it prints the various options that can be applied at
  //              runtime.  The user can use the "help" variable place
  //              additional help messages in this printout.
  PetscInitialize(&argc,&argv,(char*)0,help);

  MPI_Comm_size(PETSC_COMM_WORLD,&size);
  MPI_Comm_rank(PETSC_COMM_WORLD,&rank);

  // Here we would like to print only one message that represents
  // all the processes in the group.  We use PetscPrintf() with the
  // communicator PETSC_COMM_WORLD.  Thus, only one message is
  // printed representng PETSC_COMM_WORLD, i.e., all the processors.
  ierr = PetscPrintf(PETSC_COMM_WORLD,"Number of processors = %d, rank = %d\n",size,rank);CHKERRQ(ierr);

  MPI_Barrier(PETSC_COMM_WORLD);

  // Here we simply use PetscPrintf() with the communicator PETSC_COMM_SELF,
  // where each process is considered separately and prints independently
  // to the screen.  Thus, the output from different processes does not
  // appear in any particular order.
  PetscPrintf(PETSC_COMM_SELF,"Hello World from rank %d \n",rank);

  MPI_Barrier(PETSC_COMM_WORLD);
  
  PetscInt number = 0;
  PetscOptionsGetInt(NULL, NULL, "-number", &number, NULL);
  PetscPrintf(PETSC_COMM_WORLD, "User number is %d\n", number);

  // Always call PetscFinalize() before exiting a program.  This routine
  //   - finalizes the PETSc libraries as well as MPI
  //   - provides summary and diagnostic information if certain runtime
  //     options are chosen (e.g., -log_view).  See PetscFinalize()
  // manpage for more information.
  ierr = PetscFinalize();
  return ierr;
}

// EOF
