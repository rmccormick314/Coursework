#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <omp.h>

const int SIZE = 50;
const int totalThreads = 2;

struct arguments {
    pthread_mutex_t* lock;
    int tid;
    int* counterOne;
    int* counterTwo;
    double* endTime;
};

double mat[SIZE][SIZE];


double do_crazy_computation(int i, int j);
void* do_work(void* arg);

int main(int argc, char* argv[])
{

    pthread_mutex_t lock;
    pthread_mutex_init(&lock, nullptr);

    struct arguments *args[totalThreads];

    pthread_t worker_thread[totalThreads];

    double startTime = omp_get_wtime();

    double endTimeOne;
    double endTimeTwo;

    int counterOne = 0;
    int counterTwo = 0;

    // Creating arguments
    for (int i = 0; i < totalThreads; ++i)
    {
      args[i] = (struct arguments *) calloc(1, sizeof(struct arguments));
      args[i]-> lock = &lock;
      args[i]-> tid = i;
      args[i]-> counterOne = &counterOne;
      args[i]-> counterTwo = &counterTwo;
      if (i == 0) {args[i]-> endTime = &endTimeOne;}
      if (i == 1) {args[i]-> endTime = &endTimeTwo;}
    }

    // Creating child threads
    for (int i = 0; i < totalThreads; ++i)
    {
      if (pthread_create(&worker_thread[i], nullptr,
             do_work, (void* ) args[i])) {
          fprintf(stderr, "Error while creating thread %d\n", i);
          return 1;
      }
    }

    // Joining with child threads
    for (int i = 0; i < totalThreads; ++i)
      {
      if (pthread_join(worker_thread[i], nullptr))
      {
          fprintf(stderr, "Error while joining with child thread %d\n", i);
          return 1;
      }
    }

    double startTimeThreads;
    double finalTimeOne;
    double finalTimeTwo;
    double imbalance;

    double totalElapsed;
    double currentStartTime;

    int tid;
    int i;
    int j;



    double finishTime = omp_get_wtime() - startTime;
    imbalance = std::max(endTimeOne, endTimeTwo) - std::min(endTimeOne, endTimeTwo);
    printf("\n");
    printf("Elapsed time: %f\n", finishTime);
    printf("Time Thread1: %f\n", endTimeOne);
    printf("Time Thread2: %f\n", endTimeTwo);
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

void* do_work(void* args)
{
    // Initialize arguments structure
    struct arguments *argument;
    argument = (struct arguments*) args;

    // Create and assign all arguments
    int tid = argument->tid;
    pthread_mutex_t* lock = argument->lock;
    int* counterOne = argument->counterOne;
    int* counterTwo = argument->counterTwo;
    double* endTime = argument->endTime;
    int myCounter = 0;

    double threadStart = omp_get_wtime();

    while (*counterOne < SIZE)
    {
      if (*counterTwo < SIZE)
      {
        pthread_mutex_lock(lock);
        if (*counterOne == SIZE)
        {
          *endTime = omp_get_wtime() - threadStart;
          printf("Thread%d iterations: %d\n", tid, myCounter);
          pthread_mutex_unlock(lock);
          return 0;
        }
        mat[*counterOne][*counterTwo] = do_crazy_computation(*counterOne, *counterTwo);
        fprintf(stdout, ".");
        ++*counterTwo;
        pthread_mutex_unlock(lock);

        if (*counterTwo == SIZE)
        {
          pthread_mutex_lock(lock);
          ++*counterOne;
          *counterTwo = 0;
          pthread_mutex_unlock(lock);
        }
      }

      ++myCounter;
    }

    *endTime = omp_get_wtime() - threadStart;
    printf("\n");
    printf("Thread%d iterations: %d\n", tid, myCounter);

    pthread_mutex_unlock(lock);
    return 0;
}
