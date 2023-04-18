#include <iostream>
#include <sys/time.h>
#include <cilk/cilk.h>

using namespace std;

double estimate_pi(int num_samples) {
    int num_inside = 0;
    for(int i = 0; i < num_samples; i++) {
        double x = static_cast<double>(rand()) / RAND_MAX;
        double y = static_cast<double>(rand()) / RAND_MAX;
        if (x * x + y * y <= 1.0) {
            num_inside++;
        }
    }
    return 4.0 * static_cast<double>(num_inside) / num_samples;
}

double monte_carlo(int num_samples, int chunk_size) {
    if (num_samples <= chunk_size) {
        return estimate_pi(num_samples);
    } else {
        double pi1, pi2;
        pi1 = cilk_spawn monte_carlo(num_samples / 2, chunk_size);
        pi2 = monte_carlo(num_samples - num_samples / 2, chunk_size);
        cilk_sync;
        return (pi1 + pi2) / 2.0;
    }
}

int main() {
    int num_samples = 10000000;
    int chunk_size = 1000;
    timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    double pi = monte_carlo(num_samples, chunk_size);
    gettimeofday(&end_time, NULL);
    double duration = ((end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0);
    cout << "Pi estimate: " << pi << endl;
    cout << "Elapsed time: " << duration << " seconds" << endl;
    return 0;
}
