#include <iostream>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <immintrin.h>

#include "omp.h"

using std::cout;
using std::cerr;
using std::endl;

// You may change this to test your code
// Note that your code will be tested with at least 131072 points,
// and so your code should be working regardless of the number of points
// (I chose this number because it is a power of 2, divisible by 4, 8, etc.)
const int N = 131072;

// Do not change the seed
const int SEED = 72;

const int NB_THREADS = 1;

// Structure to represent 2-D points
struct point
{
    double x;
    double y;
};

void generateDataset(struct point* data);

int main(int argc, char* argv[])
{
    // Need to specify an argument to the program: the distance threshold epsilon
    if (argc != 2)
    {
        cerr << "Incorrect number of parameters. Expected: 2, found: " << argc - 1 << endl;
        return 1;
    }

    // Read epsilon from the command line
    char inputEpsilon[16];
    strcpy(inputEpsilon, argv[1]);
    double epsilon = atof(inputEpsilon);

    // Create the data structure to store the points
    struct point* data = new struct point[N];
    cout << "Dataset size: " << (2.0 * sizeof(double) * N) / (1024.0 * 1024.0) << " MiB\n";
    generateDataset(data);

    // Start timer
    double start = omp_get_wtime();

    //
    // Compute the distances between the points, as best and as fast as you can!
    // Add +1 to the variable `counter` (that you need to declare) if the distance between two points is <= epsilon
    // Your basic solution will most likely be O(N^2), and you need to reduce this!
    // Although required, adding #pragma omp parallel for is not sufficient for this assignment,
    // you need to reduce the computational complexity, and to add every optimizations that you can
    // to improve the performance
    //

    int counter = 0;

    #pragma omp parallel for schedule(dynamic) reduction(+:counter)
    for (int i = 0; i < N; i++)
    {
      //printf("Current on loop: %d of %d\n", i, N);
      for (int j = 0; j < N; j++)
      {
        double distance = sqrt(pow((data[j].x - data[i].x), 2) + pow((data[j].y - data[i].y), 2));
        if (distance <= epsilon)
        {
          counter++;
        }
      }
    }

    // Stop timer
    double stop = omp_get_wtime();

    // Output the result (variable `counter` below, that you need to declare above)
    // Output the execution time
    cout << "Result: " << counter << '\n';
    cout << "Execution time: " << stop - start << "s\n";

    delete[] data;

    return 0;
}

// Generate a random dataset
// Do not change this function or the seed set above
void generateDataset(struct point* data)
{
    srand(SEED);

    for (int i = 0; i < N; ++i)
    {
        data[i].x = 1000.0 * ((double)(rand()) / RAND_MAX);
        data[i].y = 1000.0 * ((double)(rand()) / RAND_MAX);
    }
}
