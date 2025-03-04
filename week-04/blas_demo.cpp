#include <iostream>
#include <vector>
#include <chrono>
#include <cblas.h>  // BLAS header

#define N 1024 // Matrix size
#define Bsize 8 // Block size

// Naïve matrix multiplication
void matrix_mult_naive(const std::vector<double>& A,
                       const std::vector<double>& B,
                       std::vector<double>& C) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                C[i * N + j] += A[i * N + k] * B[k * N + j];  // Row-major
}

// Blocked matrix multiplication (cache-friendly)
void matrix_mult_blocked(const std::vector<double>& A,
                         const std::vector<double>& B,
                         std::vector<double>& C, int block_size) {
    for (int bi = 0; bi < N; bi += block_size)
        for (int bj = 0; bj < N; bj += block_size)
            for (int bk = 0; bk < N; bk += block_size)
                for (int i = bi; i < std::min(bi + block_size, N); i++)
                    for (int j = bj; j < std::min(bj + block_size, N); j++)
                        for (int k = bk; k < std::min(bk + block_size, N); k++)
                            C[i * N + j] += A[i * N + k] * B[k * N + j];  // Row-major
}

// BLAS DGEMM Implementation (FIXED)
void matrix_mult_blas(const std::vector<double>& A,
                      const std::vector<double>& B,
                      std::vector<double>& C) {
    // Ensure C is zero-initialized
    std::fill(C.begin(), C.end(), 0.0);

    // Use BLAS DGEMM
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                N, N, N, 1.0, A.data(), N, B.data(), N, 0.0, C.data(), N);
}

int main() {
    // Allocate matrices on the heap to prevent stack overflow
    std::vector<double> A(N * N, 1.0);
    std::vector<double> B(N * N, 1.0);
    std::vector<double> C(N * N, 0.0);

    // Naive multiplication
    auto start = std::chrono::high_resolution_clock::now();
    matrix_mult_naive(A, B, C);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Naive Matrix Multiplication Time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    // Reset C
    std::fill(C.begin(), C.end(), 0.0);

    // Blocked multiplication
    start = std::chrono::high_resolution_clock::now();
    matrix_mult_blocked(A, B, C, Bsize);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Blocked Matrix Multiplication Time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    // Reset C
    std::fill(C.begin(), C.end(), 0.0);

    // BLAS DGEMM multiplication
    start = std::chrono::high_resolution_clock::now();
    matrix_mult_blas(A, B, C);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "BLAS DGEMM Matrix Multiplication Time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    return 0;
}

