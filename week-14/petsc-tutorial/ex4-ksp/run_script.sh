#!/bin/bash

~/lib/petsc-3.22.2-debug/bin/mpiexec -np 2 ./ex4.out \
  -n 10000 \
  -ksp_type gmres \
  -ksp_gmres_restart 30 \
  -ksp_rtol 1.0e-10 \
  -ksp_atol 1.0e-50 \
  -ksp_max_it 1500 \
  -pc_type hypre \
  -ksp_monitor_short \
  -ksp_converged_reason \
  -ksp_view \
  -log_view

