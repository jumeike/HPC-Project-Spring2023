#include <iostream>
#include <cstdlib>
#include <cmath>
#include <sys/time.h>
#include <cilk/cilk.h>

using namespace std;

int main()
{
    int N = 10000000; // number of darts to throw
    double x, y; // coordinates of the dart
    int hits = 0; // number of darts that hit the circle

    // seed the random number generator
    srand(time(0));

    // throw the darts
    timeval start_time, end_time;
    gettimeofday(&start_time, NULL); // start timing the program
    cilk_for (int i = 0; i < N; i++) {
        // generate a random coordinate for the dart
        x = (double)rand() / RAND_MAX * 2 - 1;
        y = (double)rand() / RAND_MAX * 2 - 1;
        
        // check if the dart hit the circle
        if (x * x + y * y <= 1) {
            hits++;
        }
    }
    gettimeofday(&end_time, NULL); // end timing the program

    // estimate pi as the ratio of hits to total darts thrown
    double pi = 4.0 * hits / N;

    // calculate the runtime of the program
    double duration = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

    // print the result and the runtime of the program
    cout << "Pi estimate: " << pi << endl;
    cout << "Elapsed time: " << duration << " seconds" << endl;

    return 0;
}