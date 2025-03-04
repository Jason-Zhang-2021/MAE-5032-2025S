#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

#define ARRAY_SIZE (1024 * 1024 * 64) // 64MB array

int main() {
  std::vector<int> arr(ARRAY_SIZE, 1); // Allocate a large array
  volatile int sum = 0;

  // Measure sequential access time
  auto start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < arr.size(); i++) {
    sum += arr[i];
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "Sequential Access Time: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    << " ms" << std::endl;

  // Shuffle indices for random access
  std::vector<size_t> indices(arr.size());
  for (size_t i = 0; i < indices.size(); i++) indices[i] = i;
  std::random_shuffle(indices.begin(), indices.end());

  // Measure random access time
  start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < arr.size(); i++) {
    sum += arr[indices[i]];
  }
  end = std::chrono::high_resolution_clock::now();
  std::cout << "Random Access Time: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    << " ms" << std::endl;

  return sum;
}

// EOF
