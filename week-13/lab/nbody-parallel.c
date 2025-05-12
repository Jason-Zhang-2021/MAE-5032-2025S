#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <mpi.h>

#define N 5000
#define G 6.67430e-11
#define DT 1e-3
#define STEPS 10
#define SOFTENING 1e-9

typedef struct {
  double x, y;
  double vx, vy;
  double mass;
} Particle;

void init_particles_local(Particle *p, int offset, int count) {
  for (int i = 0; i < count; ++i) {
    p[i].x = rand() / (double)RAND_MAX;
    p[i].y = rand() / (double)RAND_MAX;
    p[i].vx = 0.0;
    p[i].vy = 0.0;
    p[i].mass = 1.0 + rand() / (double)RAND_MAX;
  }
}

void compute_forces(int start, int count, Particle *p_all, Particle *p_local, double *fx, double *fy) {
  for (int i = 0; i < count; ++i) {
    int idx_i = start + i;
    fx[i] = 0.0;
    fy[i] = 0.0;
    for (int j = 0; j < N; ++j) {
      if (idx_i != j) {
        double dx = p_all[j].x - p_local[i].x;
        double dy = p_all[j].y - p_local[i].y;
        double dist_sqr = dx * dx + dy * dy + SOFTENING;
        double dist = sqrt(dist_sqr);
        double force = G * p_local[i].mass * p_all[j].mass / dist_sqr;
        fx[i] += force * dx / dist;
        fy[i] += force * dy / dist;
      }
    }
  }
}

void update_particles(Particle *p, double *fx, double *fy, int count) {
  for (int i = 0; i < count; ++i) {
    p[i].vx += fx[i] / p[i].mass * DT;
    p[i].vy += fy[i] / p[i].mass * DT;
    p[i].x += p[i].vx * DT;
    p[i].y += p[i].vy * DT;
  }
}

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int base = N / size;
  int extra = N % size;
  int local_n = base + (rank < extra ? 1 : 0);
  int start_idx = rank * base + (rank < extra ? rank : extra);

  int *counts = (int *)malloc(size * sizeof(int));
  int *displs = (int *)malloc(size * sizeof(int));
  int offset = 0;
  for (int i = 0; i < size; ++i) {
    counts[i] = base + (i < extra ? 1 : 0);
    displs[i] = offset * sizeof(Particle);
    offset += counts[i];
  }

  Particle *all_particles = (Particle *)malloc(N * sizeof(Particle));
  Particle *local_particles = (Particle *)malloc(local_n * sizeof(Particle));
  double *fx = (double *)malloc(local_n * sizeof(double));
  double *fy = (double *)malloc(local_n * sizeof(double));

  srand(42 + rank);
  init_particles_local(local_particles, start_idx, local_n);

  MPI_Allgatherv(local_particles, local_n * sizeof(Particle), MPI_BYTE,
                 all_particles, counts, displs, MPI_BYTE, MPI_COMM_WORLD);

  for (int step = 0; step < STEPS; ++step) {
    compute_forces(start_idx, local_n, all_particles, local_particles, fx, fy);
    update_particles(local_particles, fx, fy, local_n);

    MPI_Allgatherv(local_particles, local_n * sizeof(Particle), MPI_BYTE,
                   all_particles, counts, displs, MPI_BYTE, MPI_COMM_WORLD);
  }

  if (rank == 0)
    printf("Simulation done.\n");

  free(all_particles);
  free(local_particles);
  free(fx);
  free(fy);
  free(counts);
  free(displs);

  MPI_Finalize();
  return 0;
}

