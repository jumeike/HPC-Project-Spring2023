#include <iostream>
#include <cmath>
#include <random>
#include <sys/time.h>
#include <omp.h>
#include <cstdlib>

using namespace std;

// Function to estimate pi using the Monte Carlo method
double estimate_pi(int N, int num_threads) {
    int hits = 0;   // Counter for number of hits
    double x, y;    // Coordinates of each dart throw
    
    // Generate random number generator and seed it with current time
    mt19937_64 gen(time(nullptr));
    uniform_real_distribution<double> dis(-1.0, 1.0);
    
    // Set number of threads
    omp_set_num_threads(num_threads);
    
    // Generate random coordinates and count number of hits using OpenMP
    #pragma omp parallel for reduction(+:hits)
    for (int i = 0; i < N; i++) {
        x = dis(gen);
        y = dis(gen);
        if (x * x + y * y <= 1) {
            #pragma omp atomic update
            hits++;
        }
    }
    
    // Estimate pi and return the result
    double pi = 4.0 * hits / N;
    return pi;
}

int main() {
    int N = 10000000;        // Total number of dart throws
    int num_threads;    // Number of OpenMP threads
    
    // Retrieve number of threads from environment variable
    char* env_var = getenv("OMP_NUM_THREADS");
    if (env_var != NULL) {
        num_threads = atoi(env_var);
    } else {
        num_threads = 4;  // Default to 4 threads
    }
    
    // Start timer
    timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    
    // Estimate pi using the Monte Carlo method with OpenMP
    double pi = estimate_pi(N, num_threads);
    
    // Stop timer and calculate runtime
    gettimeofday(&end_time, NULL);
    double duration = ((end_time.tv_sec - start_time.tv_sec) * 1000.0) + ((end_time.tv_usec - start_time.tv_usec) / 1000.0);
    duration /= 1000.0;  // convert to seconds
    
    // Print estimate of pi, number of threads, and runtime
    cout << "Pi Estimate: " << pi << endl;
    cout << "Number of threads: " << num_threads << endl;
    cout << "Elapsed time: " << duration << " seconds" << endl;
    
    return 0;
}
