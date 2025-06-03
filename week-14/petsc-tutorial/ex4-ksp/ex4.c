static char help[] = "Solves a tridiagonal linear system.\n\n";

// Include "petscksp.h" so that we can use KSP solvers.  Note that this file
// automatically includes:
//    petscsys.h       - base PETSc routines
//    petscvec.h       - vectors
//    petscmat.h       - matrices
//    petscis.h        - index sets
//    petscksp.h       - Krylov subspace methods
//    petscviewer.h    - viewers
//    petscpc.h        - preconditioners

#include <petscksp.h>

int main(int argc,char **args)
{
  Vec            x, b, u;          // approx solution, RHS, exact solution
  Mat            A;                // linear system matrix
  KSP            ksp;              // linear solver context
  PC             pc;               // preconditioner context
  PetscReal      norm;  // norm of solution error
  PetscInt       i,n = 10,col[3],its,rstart,rend,nlocal;
  PetscScalar    one = 1.0,value[3];

  PetscInitialize(&argc,&args,(char*)0,help);
  PetscOptionsGetInt(NULL,NULL,"-n",&n,NULL);

  // Compute the matrix and right-hand-side vector that define the linear system, 
  // Ax = b.

  // Create vectors.  Note that we form 1 vector from scratch and
  // then duplicate as needed. For this simple case let PETSc decide how
  // many elements of the vector are stored on each processor. The second
  // argument to VecSetSizes() below causes PETSc to decide.
  VecCreate(PETSC_COMM_WORLD, &x);
  VecSetSizes(x, PETSC_DECIDE, n);
  VecSetFromOptions(x);
  VecDuplicate(x, &b);
  VecDuplicate(x, &u);

  // Identify the starting and ending mesh points on each
  // processor for the interior part of the mesh.
  VecGetOwnershipRange(x, &rstart, &rend);
  VecGetLocalSize(x,&nlocal);

  // Create matrix.
  // We pass in nlocal as the "local" size of the matrix to force it
  // to have the same parallel layout as the vector created above.
  MatCreate(PETSC_COMM_WORLD,&A);
  MatSetSizes(A, nlocal, nlocal, n, n);
  MatSetType(A, MATMPIAIJ); 
  //MatMPIAIJSetPreallocation(A, 2, PETSC_NULLPTR, 0, PETSC_NULLPTR);
  //MatSetOption(A, MAT_NEW_NONZERO_ALLOCATION_ERR, PETSC_FALSE); 
  MatSetFromOptions(A);
  MatSetUp(A);

  // Assemble matrix.
  // The linear system is distributed across the processors by
  // chunks of contiguous rows, which correspond to contiguous
  // sections of the mesh on which the problem is discretized.
  if (rstart == 0) 
  {
    rstart = 1;
    i      = 0; col[0] = 0; col[1] = 1; value[0] = 2.0; value[1] = -1.0;
    MatSetValues(A, 1, &i, 2, col, value, INSERT_VALUES);
  }
  
  if (rend == n) 
  {
    rend = n-1;
    i    = n-1; col[0] = n-2; col[1] = n-1; value[0] = -1.0; value[1] = 2.0;
    MatSetValues(A,1,&i,2,col,value,INSERT_VALUES);
  }

  // Set entries corresponding to the mesh interior
  value[0] = -1.0; value[1] = 2.0; value[2] = -1.0;
  for (i=rstart; i<rend; i++) 
  {
    col[0] = i-1; col[1] = i; col[2] = i+1;
    MatSetValues(A,1,&i,3,col,value,INSERT_VALUES);
  }

  // Assemble the matrix
  MatAssemblyBegin(A,MAT_FINAL_ASSEMBLY);
  MatAssemblyEnd(A,MAT_FINAL_ASSEMBLY);

  // MatView(A,PETSC_VIEWER_STDOUT_WORLD);

  // Set exact solution; then compute right-hand-side vector.
  VecSet(u,one);

  // VecView(u,PETSC_VIEWER_STDOUT_WORLD);

  MatMult(A, u, b);

  // Create the linear solver and set various options
  KSPCreate(PETSC_COMM_WORLD, &ksp);

  // Set operators. Here the matrix that defines the linear system
  // also serves as the preconditioning matrix.
  KSPSetOperators(ksp, A, A);

  // Set linear solver defaults for this problem (optional).
  // - By extracting the KSP and PC contexts from the KSP context,
  //   we can then directly call any KSP and PC routines to set
  //   various options.
  // - The following four statements are optional; all of these
  //   parameters could alternatively be specified at runtime via
  //   KSPSetFromOptions();
  KSPGetPC(ksp, &pc);
  PCSetType(pc, PCJACOBI);
  KSPSetTolerances(ksp, 1.e-7, PETSC_DEFAULT, PETSC_DEFAULT, PETSC_DEFAULT);

  // Set runtime options, e.g.,
  //     -ksp_type <type> -pc_type <type> -ksp_monitor -ksp_rtol <rtol>
  // These options will override those specified above as long as
  // KSPSetFromOptions() is called _after_ any other customization routines.
  KSPSetFromOptions(ksp);

  // Solve the linear system
  KSPSolve(ksp,b,x);

  // Check solution and clean up
  // Check the error
  VecAXPY(x, -1.0, u);
  VecNorm(x, NORM_2, &norm);
  KSPGetIterationNumber(ksp, &its);
  
  PetscPrintf(PETSC_COMM_WORLD,"Norm of error %g, Iterations %D\n",(double)norm,its);

  // Free work space.  All PETSc objects should be destroyed when they
  // are no longer needed.
  VecDestroy(&x); VecDestroy(&u);
  VecDestroy(&b); MatDestroy(&A);
  KSPDestroy(&ksp);

  // Always call PetscFinalize() before exiting a program.  This routine
  //   - finalizes the PETSc libraries as well as MPI
  //   - provides summary and diagnostic information if certain runtime
  //     options are chosen (e.g., -log_view).
  PetscFinalize();
  return 0;
}

// EOF
