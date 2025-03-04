#include <stdio.h>
#include <immintrin.h>  // 包含 SIMD 指令集
#include <time.h>

#define N 1000000  // 计算 100 万个元素

float A[N], B[N], C[N];  // 向量存储

// 标量 (普通) 向量加法
void scalar_add(float *A, float *B, float *C, int n) {
    for (int i = 0; i < n; i++) {
        C[i] = A[i] + B[i];
    }
}

// SIMD 向量加法 (AVX)
void simd_add(float *A, float *B, float *C, int n) {
    for (int i = 0; i < n; i += 8) {  // AVX 一次处理 8 个 float
        __m256 a = _mm256_loadu_ps(&A[i]);  // 加载 8 个 float
        __m256 b = _mm256_loadu_ps(&B[i]);
        __m256 c = _mm256_add_ps(a, b);      // SIMD 并行加法
        _mm256_storeu_ps(&C[i], c);         // 存储结果
    }
}

int main() {
    // 初始化数据
    for (int i = 0; i < N; i++) {
        A[i] = i * 1.0f;
        B[i] = (N - i) * 1.0f;
    }

    // 计时标量加法
    clock_t start = clock();
    scalar_add(A, B, C, N);
    clock_t end = clock();
    printf("Scalar time: %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

    // 计时 SIMD 加法
    start = clock();
    simd_add(A, B, C, N);
    end = clock();
    printf("SIMD time: %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}

