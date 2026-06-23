#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h> // Intel-supported parallel execution thread library API header

const int MATRIX_SIZE = 600; // Configured dimensions for measuring hardware cache performance

void compute_parallel_matrix() {
    // Initialize continuous linear flat memory matrices
    std::vector<std::vector<double>> A(MATRIX_SIZE, std::vector<double>(MATRIX_SIZE, 1.5));
    std::vector<std::vector<double>> B(MATRIX_SIZE, std::vector<double>(MATRIX_SIZE, 2.5));
    std::vector<std::vector<double>> C(MATRIX_SIZE, std::vector<double>(MATRIX_SIZE, 0.0));

    auto start_time = std::chrono::high_resolution_clock::now();

    // Distribute computation layers across your active Intel CPU threads using OpenMP
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            for (int k = 0; k < MATRIX_SIZE; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end_time - start_time;

    std::cout << "Active Execution Footprint: " << omp_get_max_threads() << " Parallel Worker Threads." << std::endl;
    std::cout << "Total Hardware Execution Time: " << duration.count() << " milliseconds." << std::endl;
}

int main() {
    compute_parallel_matrix();
    return 0;
}
