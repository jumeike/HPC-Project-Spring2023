#include <iostream>
#include <random>
#include <sys/time.h>
#include <tbb/parallel_for.h>
#include <tbb/task_scheduler_init.h>

using namespace std;

// Function to estimate pi using the Monte Carlo method
double estimate_pi(int N, int num_threads) {
    int hits = 0;   // Counter for number of hits
    double x, y;    // Coordinates of each dart throw
    
    // Generate random number generator and seed it with current time
    mt19937_64 gen(time(nullptr));
    uniform_real_distribution<double> dis(-1.0, 1.0);
    
    // Initialize TBB task scheduler with the given number of threads
    tbb::task_scheduler_init init(num_threads);
    
    // Generate random coordinates and count number of hits
    tbb::parallel_for(tbb::blocked_range<int>(0, N), [&](const tbb::blocked_range<int>& range) {
        for (int i = range.begin(); i != range.end(); ++i) {
            x = dis(gen);
            y = dis(gen);
            if (x * x + y * y <= 1) {
                hits++;
            }
        }
    });
    
    // Estimate pi and return the result
    double pi = 4.0 * hits / N;
    return pi;
}

int main() {
    int N = 10000000;    // Total number of dart throws
    int num_threads = tbb::task_scheduler_init::default_num_threads(); // Get default number of threads
    
    // Read number of threads from environment variable if set
    char* env_var = std::getenv("TBB_NUM_THREADS");
    if (env_var != nullptr) {
        num_threads = std::atoi(env_var);
    }
    
    // Start timer
    timeval start;
    gettimeofday(&start, nullptr);
    
    // Estimate pi using Monte Carlo method
    double pi = estimate_pi(N, num_threads);
    
    // Stop timer and calculate runtime
    timeval end;
    gettimeofday(&end, nullptr);
    double runtime = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0;
    
    // Print estimate of pi and runtime
    cout << "Pi Estimate: " << pi << endl;
    cout << "Elapsed time: " << runtime << " seconds" << endl;
    
    return 0;
}
