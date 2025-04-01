#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 512

void compute(double A[N][N], double B[N][N], double C[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            double sum = 0.0;
            for (int k = 0; k < N; ++k) {
                // Inner loop that might benefit from unrolling/vectorization
                sum += sin(A[i][k]) * exp(B[k][j]);
            }
            C[i][j] = sqrt(fabs(sum));
        }
    }
}

int main() {
    static double A[N][N], B[N][N], C[N][N];
    
    // Initialize matrices
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            A[i][j] = (i + j) * 0.0001;
            B[i][j] = (i - j) * 0.0001;
        }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    compute(A, B, C);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = (end.tv_sec - start.tv_sec)
                   + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Finished computation. Sample output: %.6f\n", C[N/2][N/2]);
    printf("Elapsed time: %.6f seconds\n", elapsed);
    return 0;
}

