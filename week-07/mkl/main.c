#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <mkl.h>

#define FLOAT_TYPE double

int main(int argc, char* argv[])
{
    struct timeval stime, etime, diff;
    double timeinsec, perf;

    FLOAT_TYPE* A;
    FLOAT_TYPE* B;
    FLOAT_TYPE* C;
    FLOAT_TYPE  alpha = 1.0, beta = 1.0;

    int m = 4096;
    int n = 4096;
    int k = 4096;
    int LOOP_COUNT = 10;
    int i;

    if (argc >= 2) m = atoi(argv[1]);
    if (argc >= 3) n = atoi(argv[2]);
    if (argc >= 4) k = atoi(argv[3]);
    if (argc >= 5) LOOP_COUNT = atoi(argv[4]);

    char transa='N';
    char transb='N';

    A = (FLOAT_TYPE*) malloc(sizeof(double)*m*k);
    B = (FLOAT_TYPE*) malloc(sizeof(double)*k*n);
    C = (FLOAT_TYPE*) malloc(sizeof(double)*m*n);

    printf("Size of Matrix A(mxk): %d x %d\n", m, k);
    printf("Size of Matrix B(kxn): %d x %d\n", k, n);
    printf("Size of Matrix C(mxn): %d x %d\n", m, n);
    printf("LOOP COUNT           : %d \n", LOOP_COUNT);

    for (i=0; i<m*k ; ++i)
    {
      A[i] = 1.0;
    }

    for (i=0; i<k*n ; ++i)
    {
      B[i] = 2.0;
    }

    for (i=0; i<m*n ; ++i)
    {
      C[i] = 1.0;
    }

    /* first call for
     * thread/buffer
     * initialization */
    dgemm(&transa, &transb, &m, &n, &k, &alpha, A, &m, B, &k, &beta, C, &m);

    gettimeofday(&stime, NULL);
    double time_st  = dsecnd();
    for (i=0; i<LOOP_COUNT; ++i)
    {
      dgemm(&transa, &transb, &m, &n, &k, &alpha, A, &m, B, &k, &beta, C, &m);
    }
    double time_end = dsecnd() ;
    gettimeofday(&etime,NULL);
    timersub(&etime, &stime, &diff);
    timeinsec  = (diff.tv_sec*1000+diff.tv_usec/1000)/1000.0/ LOOP_COUNT;
    printf("Average time:%f secs from gettiemeofday \n", timeinsec);

    double time_avg = (time_end - time_st)/LOOP_COUNT;

    double gflop = (2.0*m*n*k + 1.0*m*n)*1E-9;

    printf("Average time:%e secs \n", time_avg);
    printf("GFlop       :%.5f \n", gflop);
    printf("GFlop/sec   :%.5f \n", gflop/time_avg);
    printf("GFlop/sec gettimeofday  :%.5f \n", gflop/timeinsec);

    return 0;
}

