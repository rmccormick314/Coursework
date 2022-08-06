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

    double startTimeThreads;
    double finalTimeOne;
    double finalTimeTwo;
    double imbalance;

    double totalElapsed;
    double currentStartTime;

    int tid;
    int i;
    int j;

    #pragma omp parallel private(i, j, tid) shared(startTimeThreads)
    {
      tid = omp_get_thread_num();

      #pragma omp for schedule(guided)
      for (i = 0; i < SIZE; ++i)  /* loop over the rows */
      {
          for (j = 0; j < SIZE; ++j)   /* loop over the columns */
          {
              mat[i][j] = do_crazy_computation(i, j);
              fprintf(stdout, ".");
          }
      }

      if (tid == 0) {finalTimeOne = omp_get_wtime() - startTime;}
      if (tid == 1) {finalTimeTwo = omp_get_wtime() - startTime;}
    }

    double finishTime = omp_get_wtime() - startTime;
    imbalance = std::max(finalTimeOne, finalTimeTwo) - std::min(finalTimeOne, finalTimeTwo);
    printf("\n");
    printf("Elapsed time: %f\n", finishTime);
    printf("Time Thread1: %f\n", finalTimeOne);
    printf("Time Thread2: %f\n", finalTimeTwo);
    printf("Imbalance: %f\n", imbalance);

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
