#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

void init_particles(Particle *p) 
{
  for (int i = 0; i < N; ++i) {
    p[i].x = rand() / (double)RAND_MAX;
    p[i].y = rand() / (double)RAND_MAX;
    p[i].vx = 0.0;
    p[i].vy = 0.0;
    p[i].mass = 1.0 + rand() / (double)RAND_MAX;
  }
}

void info_print(Particle *p) 
{
  double x_sum = 0.0, y_sum = 0.0;
  for (int i = 0; i < N; ++i) {
    x_sum += p[i].x;
    y_sum += p[i].y;
  }
  printf("Center of mass (rough): (%e, %e)\n", x_sum / N, y_sum / N);
}

void compute_forces(Particle *p, double *fx, double *fy) 
{
  for (int i = 0; i < N; ++i) {
    fx[i] = 0.0;
    fy[i] = 0.0;
    for (int j = 0; j < N; ++j) {
      if (i != j) {
        double dx = p[j].x - p[i].x;
        double dy = p[j].y - p[i].y;
        double dist_sqr = dx * dx + dy * dy + SOFTENING;
        double dist = sqrt(dist_sqr);
        double force = G * p[i].mass * p[j].mass / dist_sqr;
        fx[i] += force * dx / dist;
        fy[i] += force * dy / dist;
      }
    }
  }
}

void update_particles(Particle *p, double *fx, double *fy) 
{
  for (int i = 0; i < N; ++i) {
    p[i].vx += fx[i] / p[i].mass * DT;
    p[i].vy += fy[i] / p[i].mass * DT;
    p[i].x += p[i].vx * DT;
    p[i].y += p[i].vy * DT;
  }
}

int main() 
{
  Particle *particles = (Particle *)malloc(N * sizeof(Particle));
  double *fx = (double *)malloc(N * sizeof(double));
  double *fy = (double *)malloc(N * sizeof(double));

  init_particles(particles);

  info_print(particles);

  for (int step = 0; step < STEPS; ++step) {
    compute_forces(particles, fx, fy);
    update_particles(particles, fx, fy);
  }

  printf("Simulation done.\n");

  free(particles);
  free(fx);
  free(fy);
  return 0;
}

// EOF
