#include <iostream>
#include <vector>
#include <chrono>

#define N 2048 // Matrix size
#define Bsize 8 // Block size

void matrix_mult_naive(std::vector<std::vector<double>> &A,
                       std::vector<std::vector<double>> &B,
                       std::vector<std::vector<double>> &C) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
}

void matrix_mult_blocked(std::vector<std::vector<double>> &A,
                         std::vector<std::vector<double>> &B,
                         std::vector<std::vector<double>> &C, int block_size) {
    for (int bi = 0; bi < N; bi += block_size)
        for (int bj = 0; bj < N; bj += block_size)
            for (int bk = 0; bk < N; bk += block_size)
                for (int i = bi; i < std::min(bi + block_size, N); i++)
                    for (int j = bj; j < std::min(bj + block_size, N); j++)
                        for (int k = bk; k < std::min(bk + block_size, N); k++)
                            C[i][j] += A[i][k] * B[k][j];
}

int main() {
    std::vector<std::vector<double>> A(N, std::vector<double>(N, 1.0));
    std::vector<std::vector<double>> B(N, std::vector<double>(N, 1.0));
    std::vector<std::vector<double>> C(N, std::vector<double>(N, 0.0));

    auto start = std::chrono::high_resolution_clock::now();
    matrix_mult_naive(A, B, C);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Naive Matrix Multiplication Time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    C.assign(N, std::vector<double>(N, 0.0)); // Reset C

    start = std::chrono::high_resolution_clock::now();
    matrix_mult_blocked(A, B, C, Bsize);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Blocked Matrix Multiplication Time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    return 0;
}

// EOF
