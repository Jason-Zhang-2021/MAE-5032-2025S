#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <cstdlib>

// Define constants
constexpr size_t MAX_VL = 64 * 1024 * 1024; // Max vector length (64MB)
constexpr size_t ITERATIONS = 100;          // Number of iterations for averaging

int main() {
  std::vector<size_t> test_sizes = {1024, 8192, 65536, 524288, 4194304, 16777216, MAX_VL}; // Different vector sizes

  std::cout << "Vector Length (VL), Bandwidth (MB/s)" << std::endl;

  for (size_t vl : test_sizes) {
    std::vector<double> memory(vl, 1.0); // Allocate memory and initialize
    double sum = 0.0;

    // Measure time
    auto start_time = std::chrono::high_resolution_clock::now();
    for (size_t iter = 0; iter < ITERATIONS; ++iter) {
      for (size_t i = 0; i < vl; ++i) {
        sum += memory[i]; // Simulate memory access
      }
    }
    auto end_time = std::chrono::high_resolution_clock::now();

    // Compute elapsed time
    std::chrono::duration<double> elapsed = end_time - start_time;
    double avg_time = elapsed.count() / ITERATIONS; // Average time per iteration

    // Compute bandwidth (BW = bytes per word × vl / time)
    double bytes_per_word = sizeof(double);
    double bandwidth = (bytes_per_word * vl) / (avg_time * 1e6); // MB/s

    // Print result
    std::cout << vl << ", " << bandwidth << std::endl;
  }

  return 0;
}

// EOF
