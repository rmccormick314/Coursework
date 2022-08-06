#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

struct arguments {
    sem_t* sem;
    int* scoreA;
    int* scoreB;
    int* counterTeamA;
    int* counterTeamB;
    pthread_mutex_t* scoreLock;
    int tid;
};

sem_t sems [10] = {};

// Prototype functions
int randThread(int team, int min, int max);
void* do_work(void* arg);

int main(int argc, char* argv[])
{
    //Seed rng
    //Do not change seed
    srand(42);

    // Arguments and number of threads
    const int totalThreads = 10;
    struct arguments *args[totalThreads];

    pthread_t worker_thread[totalThreads];

  	int scoreA = 0;
  	int scoreB = 0;
  	int counterTeamA = 0;
  	int counterTeamB = 0;
  	pthread_mutex_t lock;
  	pthread_mutex_init(&lock, nullptr);

  	// Creating arguments
  	for (int i = 0; i < totalThreads; ++i)
  	{
      args[i] = (struct arguments *) calloc(1, sizeof(struct arguments));
  		args[i]-> sem = &sems[i];
  		args[i]-> scoreA = &scoreA;
  		args[i]-> scoreB = &scoreB;
  		args[i]-> counterTeamA = &counterTeamA;
  		args[i]-> counterTeamB = &counterTeamB;
  		args[i]-> scoreLock = &lock;
  		args[i]-> tid = i;
  	}

    sem_init(&sems[0], 0, 1);
    for (int i = 1; i < totalThreads; ++i)
    {
      sem_init(&sems[i], 0, 0);
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

    //free(args);
    printf("\n\n");
    exit(0);
}


void* do_work(void* args)
{
    // Initialize arguments structure
    struct arguments *argument;
    argument = (struct arguments*) args;

    // Create and assign all arguments
    sem_t* sem = argument->sem;
    int* scoreA = argument->scoreA;
  	int* scoreB = argument->scoreB;
    int* counterTeamA = argument->counterTeamA;
    int* counterTeamB = argument->counterTeamB;
    pthread_mutex_t* lock = argument->scoreLock;
    int tid = argument->tid;
    int team;
    int otherTeam;
    int target;
    bool targetOnTeam;

    // Assign each thread to a team
    if (tid == 5 || tid == 6 || tid == 7 || tid == 8 || tid == 9)
    {
      team = 1;
      otherTeam = 0;
    }

    if (tid == 0 || tid == 1 || tid == 2 || tid == 3 || tid == 4)
    {
      team = 0;
      otherTeam = 0;
    }

    HEAD:
      sem_wait(&sems[tid]);

      if ((*scoreA == 10) || (*scoreB == 10)){return nullptr;}

      target = randThread(team, 0, 9);

      if (team == 0)
      {
        if (target == 5 || target == 6 || target == 7 || target == 8 || target == 9)
        {
          targetOnTeam = false;
        } else {
          targetOnTeam = true;
        }
      }

      if (team == 1)
      {
        if (target == 0 || target == 1 || target == 2 || target == 3 || target == 4)
        {
          targetOnTeam = false;
        } else {
          targetOnTeam = true;
        }
      }

      if (targetOnTeam)
      {
        if (team == 0)
        {
          ++*counterTeamA;
          if (*counterTeamB != 0)
          {
            *counterTeamB = 0;
          }
          printf("[Pass: Team: %d] Thread: %d, Pass to Thread: %d, Counter Team 0: %d\n", team, tid, target, *counterTeamA);
          if (*counterTeamA > 4)
          {
            ++*scoreA;
            printf("[Team 0 Scored A Goal!] Score Team 0: %d, Score Team 1: %d, Counter Team 0: %d\n", *scoreA, *scoreB, *counterTeamA);
            *counterTeamA = 0;
            printf("[Team 0] Counter Reset: %d\n", *counterTeamA);
          }
        }

        if (team == 1)
        {
          {
            ++*counterTeamB;
            if (*counterTeamA != 0)
            {
              *counterTeamA = 0;
            }
            printf("[Pass: Team: %d] Thread: %d, Pass to Thread: %d, Counter Team 1: %d\n", team, tid, target, *counterTeamB);
            if (*counterTeamB == 5)
            {
              ++*scoreB;
              printf("[Team 1 Scored A Goal!] Score Team 0: %d, Score Team 1: %d, Counter Team 1: %d\n", *scoreA, *scoreB, *counterTeamB);
              *counterTeamB = 0;
              printf("[Team 1] Counter Reset: %d\n", *counterTeamB);
            }
          }
        }
      }

      if (!targetOnTeam) {
        if (team == 0)
        {
          *counterTeamA = 0;
          printf("[Interception: Team: 0] Thread: %d, Intercepted by Thread: %d, Counter Team 0: %d\n", tid, target, *counterTeamA);
        }

        if (team == 1)
        {
          *counterTeamB = 0;
          printf("[Interception: Team: 1] Thread: %d, Intercepted by Thread: %d, Counter Team 1: %d\n", tid, target, *counterTeamB);
        }
      }

      //usleep(2000000);

      if ((*scoreA != 10) && (*scoreB != 10))
      {
        sem_post(&sems[target]);
        goto HEAD;
      } else {
        for (int i = 0; i < 10; ++i)
        {
          sem_post(&sems[i]);
        }
        return nullptr;
      }
}


// Do not modify
// Team must be 0 or 1
// 0 for team 0
// 1 for team 1
// min: minimum thread id to generate
// max: maximum thread id to generate
// Min = 0
// Max = 10
// Generated in [0, 10)
int randThread(int team, int min, int max)
{
    double randNum = (double)rand() / (double)RAND_MAX;

    // Generate random semaphore to send the ball/puck/etc. to
    // On the team
    if (randNum < 0.6)
    {
        double randNum = ((double)rand() / (double)RAND_MAX)*(max*1.0/2*1.0);
        //send to teammate
        if (0 == team)
        {
            return (int)randNum;
        }
        if (1 == team)
        {
            return (int)randNum + 5;
        }
    } else {
        //Interception by other team
        double randNum = 5.0 * ((double)rand() / (double)RAND_MAX);

        //send to other team
        if (1 == team)
        {
            return (int)randNum;
        }
        if (0 == team)
        {
            return (int)randNum + 5;
        }
    }

    return 0;
}
