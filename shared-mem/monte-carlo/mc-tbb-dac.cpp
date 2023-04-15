#include <iostream>
#include <random>
#include <sys/time.h>
#include <tbb/tbb.h>

using namespace std;

// Function to estimate pi using the Monte Carlo method
double estimate_pi(int N) {
    int hits = 0;   // Counter for number of hits
    double x, y;    // Coordinates of each dart throw
    
    // Generate random number generator and seed it with current time
    mt19937_64 gen(time(nullptr));
    uniform_real_distribution<double> dis(-1.0, 1.0);
    
    // Generate random coordinates and count number of hits
    tbb::parallel_for(tbb::blocked_range<int>(0, N), [&](const tbb::blocked_range<int>& r) {
        int local_hits = 0;
        for (int i = r.begin(); i < r.end(); i++) {
            x = dis(gen);
            y = dis(gen);
            if (x * x + y * y <= 1) {
                local_hits++;
            }
        }
        hits += local_hits;
    });
    
    // Estimate pi and return the result
    double pi = 4.0 * hits / N;
    return pi;
}

// Recursive function to estimate pi using the Divide and Conquer method
double dac_pi(int N, int depth, int num_threads) {
    if (depth == 0) {   // Base case: use Monte Carlo method
        return estimate_pi(N);
    } else {            // Recursive case: divide problem into subproblems
        int M = N / 2;
        double pi1, pi2;
        tbb::task_scheduler_init init(num_threads);
        tbb::parallel_invoke(
            [&] { pi1 = dac_pi(M, depth - 1, num_threads); },
            [&] { pi2 = dac_pi(N - M, depth - 1, num_threads); }
        );
        return (pi1 + pi2) / 2.0;
    }
}

int main() {
    int N = 10000000;    // Total number of dart throws
    int depth = 4;      // Depth of recursion for Divide and Conquer method
    
    // Retrieve number of threads from environment variable
    char* num_threads_str = getenv("TBB_NUM_THREADS");
    int num_threads = (num_threads_str != nullptr) ? atoi(num_threads_str) : tbb::task_scheduler_init::default_num_threads();
    
    // Start timer
    timeval start;
    gettimeofday(&start, nullptr);
    
    // Estimate pi using Divide and Conquer method
    double pi = dac_pi(N, depth, num_threads);
    
    // Stop timer and calculate runtime
    timeval end;
    gettimeofday(&end, nullptr);
    double runtime = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    
    // Print estimate of pi and runtime
    cout << "Pi Estimate: " << pi << endl;
    cout << "Elapsed time: " << runtime << " seconds" << endl;
    
    return 0;
}
