#include <iostream>
#include <vector>
#include <chrono>

#define ARRAY_SIZE (256 * 1024 * 1024) // 256MB array to test L1, L2 effects
#define NUM_ACCESSES 10000000 // Fixed number of accesses

int main() {
  std::vector<int> arr(ARRAY_SIZE, 1);
  volatile int sum = 0;

  std::cout << "Testing cache effects with fixed number of accesses:\n";

  for (size_t stride = 1; stride <= 1024; stride *= 2) 
  {
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0, j = 0; i < NUM_ACCESSES; i++) 
    {
      sum += arr[j];
      j = (j + stride) % arr.size(); // Wrap around when exceeding array size
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Stride: " << stride << ", Time: "
      << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
      << " us" << std::endl;
  }

  return sum; // Prevent compiler optimization
}

// EOF
