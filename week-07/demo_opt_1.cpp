#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

double compute(const std::vector<double>& data) {
    double result = 0.0;
    for (size_t i = 1; i < data.size(); ++i) {
        result += std::sin(data[i]) * std::cos(data[i - 1]);
    }
    return result;
}

int main() {
    const size_t N = 10000000;
    std::vector<double> data(N);
    for (size_t i = 0; i < N; ++i) {
        data[i] = i * 0.000001;
    }

    auto start = std::chrono::high_resolution_clock::now();
    double result = compute(data);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Result: " << result << "\n";
    std::cout << "Elapsed time: " << duration.count() << " seconds\n";

    return 0;
}

// EOF
