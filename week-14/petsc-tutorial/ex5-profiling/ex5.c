static char help[] = "Augmenting PETSc profiling by add events.\n\
                      Run this program with one of the\n\
                      following options to generate logging information:  -log, -log_view,\n\
                      -log_all.  The PETSc routines automatically log event times and flops,\n\
                      so this monitoring is intended solely for users to employ in application\n\
                      codes.\n\n";

#include <petscsys.h>
#include <petscviewer.h>

int main(int argc, char **argv)
{
  PetscMPIInt   rank;
  int           i, imax = 10000, icount;
  PetscLogEvent USER_EVENT, check_USER_EVENT;

  PetscFunctionBeginUser;
  PetscInitialize(&argc, &argv, NULL, help);

  // Create a new user-defined event.
  // - Note that PetscLogEventRegister() returns to the user a unique
  // integer event number, which should then be used for profiling
  // the event via PetscLogEventBegin() and PetscLogEventEnd().
  // - The user can also optionally log floating point operations
  // with the routine PetscLogFlops().
  PetscLogEventRegister("User event", PETSC_VIEWER_CLASSID, &USER_EVENT);
  PetscLogEventGetId("User event", &check_USER_EVENT);
  PetscCheck(USER_EVENT == check_USER_EVENT, PETSC_COMM_SELF, PETSC_ERR_PLIB, "Event Ids do not match");

  PetscLogEventBegin(USER_EVENT, 0, 0, 0, 0);
  icount = 0;
  for (i = 0; i < imax; i++) icount++;
  (void)icount;
  PetscLogFlops(imax);
  PetscSleep(0.5);
  PetscLogEventEnd(USER_EVENT, 0, 0, 0, 0);

  // We disable the logging of an event.
  PetscLogEventDeactivate(USER_EVENT);
  PetscLogEventBegin(USER_EVENT, 0, 0, 0, 0);
  PetscSleep(0.5);
  PetscLogEventEnd(USER_EVENT, 0, 0, 0, 0);

  // We next enable the logging of an event
  PetscLogEventActivate(USER_EVENT);
  PetscLogEventBegin(USER_EVENT, 0, 0, 0, 0);
  PetscSleep(0.5);
  PetscLogEventEnd(USER_EVENT, 0, 0, 0, 0);

  // We test event logging imbalance
  MPI_Comm_rank(PETSC_COMM_WORLD, &rank);
  if (rank == 0) PetscSleep(0.5);
  PetscLogEventSync(USER_EVENT, PETSC_COMM_WORLD);
  PetscLogEventBegin(USER_EVENT, 0, 0, 0, 0);
  MPI_Barrier(PETSC_COMM_WORLD);
  PetscSleep(0.5);
  PetscLogEventEnd(USER_EVENT, 0, 0, 0, 0);

  PetscFinalize();
  return 0;
}

// EOF
