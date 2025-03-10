#include <iostream>
#include <vector>
#include <chrono>

#define N 1024 // Matrix size

// Naive matrix multiplication
void matrix_mult_naive(const std::vector<double> &A, 
                       const std::vector<double> &B, 
                       std::vector<double> &C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double sum = 0.0;
            for (int k = 0; k < N; k++)
                sum += A[i * N + k] * B[k * N + j];
            C[i * N + j] = sum;
        }
    }
}

// Transpose matrix B
void transpose(const std::vector<double> &B, std::vector<double> &B_T) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            B_T[j * N + i] = B[i * N + j];
}

// Matrix multiplication using transposed B
void matrix_mult_transposed(const std::vector<double> &A, 
                            const std::vector<double> &B_T, 
                            std::vector<double> &C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double sum = 0.0;
            for (int k = 0; k < N; k++)
                sum += A[i * N + k] * B_T[j * N + k]; // Access B_T row-wise
            C[i * N + j] = sum;
        }
    }
}

int main() {
    std::vector<double> A(N * N, 1.0);
    std::vector<double> B(N * N, 1.0);
    std::vector<double> B_T(N * N, 0.0);
    std::vector<double> C(N * N, 0.0);

    volatile double dummy = 0.0;

    // Naive multiplication benchmark
    auto start = std::chrono::high_resolution_clock::now();
    matrix_mult_naive(A, B, C);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Naive Matrix Multiplication Time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    dummy += C[0];

    // Reset C
    std::fill(C.begin(), C.end(), 0.0);

    // Transpose B
    start = std::chrono::high_resolution_clock::now();
    transpose(B, B_T);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Transpose Time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    // Multiplication using transposed B
    start = std::chrono::high_resolution_clock::now();
    matrix_mult_transposed(A, B_T, C);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Matrix Multiplication with Transposed B Time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    dummy += C[0];

    return 0;
}

// EOF
