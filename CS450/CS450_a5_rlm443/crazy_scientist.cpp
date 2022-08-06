#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <omp.h>

const int SIZE = 50;

double do_crazy_computation(int i, int j);

int main(int argc, char* argv[])
{
    double mat[SIZE][SIZE];

    double startTime = omp_get_wtime();

    // Modify code here
    for (int i = 0; i < SIZE; ++i)  /* loop over the rows */
    {
        for (int j = 0; j < SIZE; ++j)   /* loop over the columns */
        {
            mat[i][j] = do_crazy_computation(i, j);
            fprintf(stdout, ".");
        }
    }

    double stopTime = omp_get_wtime();
    double elapsed = stopTime - startTime;
    std::cout << "Elapsed time: " << elapsed << " s" << std::endl;

    return 0;
}

//Crazy computation
double do_crazy_computation(int x, int y)
{
    double value = 0.0;

    for (int iter = 0; iter < 5*x*x*x+1 + y*y*y+1; ++iter)
    {
        value += (cos(x * value) + sin(y * value));
    }
    return value;
}

