#include <iostream>
#include <vector>
#include <chrono>
#include <immintrin.h>  // SIMD Intrinsics for AVX
#include <cstdlib>      // For aligned memory allocation

using namespace std;
using namespace std::chrono;

const int N = 32768; 
const int REPEATS = 100000;

// Allocate aligned memory (32-byte aligned for AVX)
float* aligned_alloc(int size) {
    void* ptr = nullptr;
    posix_memalign(&ptr, 32, size * sizeof(float));  // POSIX aligned allocation
    return (float*)ptr;
}

// Scalar (regular) vector addition
void scalar_add(const float* A, const float* B, float* C, int n) {
  for(int r =0; r<REPEATS; r++)  
    for (int i = 0; i < n; i++)
      C[i] = A[i] + B[i];
}

// SIMD vector addition using AVX with aligned memory
void simd_add(const float* A, const float* B, float* C, int n) {
  for(int r =0; r<REPEATS; r++)  
  {
    for (int i = 0; i < n; i += 8) {  // AVX processes 8 floats at a time
      __m256 a = _mm256_load_ps(&A[i]);  // Aligned load
      __m256 b = _mm256_load_ps(&B[i]);
      __m256 c = _mm256_add_ps(a, b);    // SIMD parallel addition
      _mm256_store_ps(&C[i], c);         // Aligned store
    }
  }
}

int main() {
  // Allocate 32-byte aligned memory
  float* A = aligned_alloc(N);
  float* B = aligned_alloc(N);
  float* C = aligned_alloc(N);

  // Initialize vectors
  for (int i = 0; i < N; i++) {
    A[i] = i * 1.0f;
    B[i] = (N - i) * 1.0f;
  }

  // Measure scalar addition time
  auto start = high_resolution_clock::now();
  scalar_add(A, B, C, N);
  auto end = high_resolution_clock::now();
  cout << "Scalar time: " 
    << duration<double>(end - start).count() << " sec" << endl;

  // Measure SIMD addition time
  start = high_resolution_clock::now();
  simd_add(A, B, C, N);
  end = high_resolution_clock::now();
  cout << "SIMD time: " 
    << duration<double>(end - start).count() << " sec" << endl;

  // Free aligned memory
  free(A); free(B); free(C);
  return 0;
}

