#include <iostream>
#include <iomanip>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <immintrin.h>
#include <vector>
#include <bits/stdc++.h>

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

const int NB_THREADS = 8;

// Structure to represent 2-D points
struct point
{
    double x;
    double y;
    // Distance from origin
    double dfo;
};

void generateDataset(struct point* data);
double dist(const point& lhs, const point& rhs);

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

    //<--- BEGIN SOLUTION --->

    // Establish variables
    int counter = 0;
    double epsilon_squared = epsilon * epsilon;
    int CHUNK = 16;

    double a, b, dx, dy, distance = 0;

    // Origin point
    point p;
    p.x = 0;
    p.y = 0;

    // Sort the input array by distance from origin
    std::sort(data,data+N,[p](const point& lhs, const point& rhs){ return dist(p, lhs) < dist(p, rhs); });

    // Assign each point its distance from origin
    for (int q = 0; q < N; ++q)
    {
      data[q].dfo = dist(p, data[q]);
    }

    // Check every point with every other point exactly one time, no repeats.
    #pragma omp parallel for schedule(dynamic, CHUNK) num_threads(NB_THREADS) reduction(+:counter) private(a, b, dx, dy, distance)
    for (int i = 0; i < N-1; ++i)
    {
      // Outer loop's current distance from origin
      a = data[i].dfo;
      for (int j = i+1; j < N; j = ++j)
      {
        // Inner loop's current distance from origin
        b = data[j].dfo;

        // Find distance squared
        dx = (data[i].x - data[j].x);
        dy = (data[i].y - data[j].y);
        distance = (dx*dx) + (dy*dy);

        // Compare distance squared to epsilon squared
        if (distance <= epsilon_squared)
        {
          // The loops only checks each element once
          // Thus, the reverse of each pair needs to be accounted for.
          // It is assumed Points A & B will have same distance as Points B & A
          counter = counter + 2;
        } else {
          // If the difference in distance from origin is greater than epislon,
          // no future points will be closer. We can break loop to save resources.
          if (abs(a-b)>epsilon)
          {
            break;
          }
        }
      }
    }

    // Add to counter for each pair consisting of a single element
    // Pairs which are made of two of the SAME element are not included in loop
    // Thus, this operation represents counting every pair where an element is
    // matched with itself.
    counter = counter + (N);

    //<--- END SOLUTION --->

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

double dist(const point& lhs, const point& rhs)
{
    // compute Euclidean distance or whatever
    double dx = (lhs.x - rhs.x);
    double dy = (lhs.y - rhs.y);
    double distance = sqrt((dx*dx) + (dy*dy));
    return(distance);
}
