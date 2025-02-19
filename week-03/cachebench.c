#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VECTOR_LENGTH 1000000

// Function to perform the cache benchmark
void cache_benchmark(int max_vector_length) {
    int *memory;
    long long r = 0;
    clock_t start_time, end_time;
    double average_time;

    // Loop over different vector lengths
    for (int vl = 1; vl <= max_vector_length; vl *= 2) {
        // Allocate and initialize memory
        memory = (int *)malloc(vl * sizeof(int));
        for (int i = 0; i < vl; i++) {
            memory[i] = i;
        }

        // Start the timer
        start_time = clock();

        // Run the benchmark for a number of iterations
        for (int iteration = 0; iteration < 100; iteration++) {
            for (int i = 0; i < vl; i++) {
                r += memory[i];  // Access each element
            }
        }

        // Stop the timer
        end_time = clock();
        average_time = (double)(end_time - start_time) / CLOCKS_PER_SEC / 100;  // Time per iteration

        // Calculate bandwidth in bytes per word per average time
        double bw = (double)(vl * sizeof(int)) / average_time;
        printf("Vector length: %d, Bandwidth: %.2f bytes/word\n", vl, bw);

        // Free the allocated memory
        free(memory);
    }
}

int main() {
    // Set the maximum vector length for the benchmark
    int max_vector_length = MAX_VECTOR_LENGTH;

    // Print program title
    printf("Memory Benchmark (CacheBench)\n");
    printf("Microbenchmark for memory system performance\n\n");

    // Run the cache benchmark
    cache_benchmark(max_vector_length);

    return 0;
}

// EOF
