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

    double elapsedTime;

    int a = 25;
    int i;

    #pragma omp parallel shared(a) private(i)
    {
      #pragma omp sections
      {
        #pragma omp section
        {
          for (int i = 0; i < a; ++i)  /* loop over the rows */
          {
              for (int j = 0; j < SIZE; ++j)   /* loop over the columns */
              {
                  mat[i][j] = do_crazy_computation(i, j);
                  fprintf(stdout, ".");
              }
          }
        }
        #pragma omp section
        {
          for (int i = 25; i < SIZE; ++i)  /* loop over the rows */
          {
              for (int j = 0; j < SIZE; ++j)   /* loop over the columns */
              {
                  mat[i][j] = do_crazy_computation(i, j);
                  fprintf(stdout, ".");
              }
          }
        }
      }
    }

    elapsedTime = omp_get_wtime() - startTime;

    printf("\n");
    std::cout << "Elapsed time: " << elapsedTime << " seconds." << std::endl;

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
