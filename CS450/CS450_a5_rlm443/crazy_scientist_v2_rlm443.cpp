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
    omp_set_num_threads(2);

    double startTimeOne;
    double startTimeTwo;
    double finalTimeOne;
    double finalTimeTwo;
    double imbalance;

    double totalElapsed;

    int a = 25;
    int i;

    double currentThreadStartTime = omp_get_wtime();
    #pragma omp parallel shared(a) private(i)
    {
      #pragma omp sections
      {
        #pragma omp section
        {
          startTimeOne = omp_get_wtime();
          for (int i = 0; i < a; ++i)  /* loop over the rows */
          {
              for (int j = 0; j < 25; ++j)   /* loop over the columns */
              {
                  mat[i][j] = do_crazy_computation(i, j);
                  fprintf(stdout, ".");
              }
          }
          finalTimeOne = omp_get_wtime() - startTimeOne;
        }
        #pragma omp section
        {
          startTimeTwo = omp_get_wtime();
          for (int i = 25; i < SIZE; ++i)  /* loop over the rows */
          {
              for (int j = 0; j < SIZE; ++j)   /* loop over the columns */
              {
                  mat[i][j] = do_crazy_computation(i, j);
                  fprintf(stdout, ".");
              }
          }
          finalTimeTwo = omp_get_wtime() - startTimeOne;
        }
      }
    }

    double elapsed = omp_get_wtime() - currentThreadStartTime;
    totalElapsed = omp_get_wtime() - startTime;

    imbalance = std::max(finalTimeOne, finalTimeTwo) - std::min(finalTimeOne, finalTimeTwo);
    std::cout << "Total Time: " << totalElapsed << " s" << std::endl;
    std::cout << "Run Time: " << elapsed << " s" << std::endl;
    std::cout << "Time Thread1: " << finalTimeOne << " s" << std::endl;
    std::cout << "Time Thread2: " << finalTimeTwo << " s" << std::endl;
    std::cout << "Imbalance: " << imbalance << " s" << std::endl;

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
