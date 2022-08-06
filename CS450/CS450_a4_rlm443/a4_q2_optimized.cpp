#include <iostream>
#include <list>
#include <random>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <math.h>

// Constant global variables
// You can modify these for test purposes
// But your code should be working with the default values
const int SIZE = 10000000;
const int NB_THREADS = 20;

// Seed and random number generator
// Do not modify this
const std::string randomSeed = "cs450_assignment4";
std::mt19937 genRandom;

// You can modify this if you want/need
pthread_barrier_t barrier;
sem_t semaphore;
sem_t semaphoreB;
sem_t semaphoreC;

// List that will contain random numbers
// You can modify this if you want/need
std::list<int> listA;
std::list<int> listB;
std::list<int> listC;
std::list<int> listResult;

// Iterators for the lists declared above
// You can modify this if you want/need
std::list<int>::iterator iteratorA;
std::list<int>::iterator iteratorB;
std::list<int>::iterator iteratorC;
std::list<int>::iterator iteratorResult;

clock_t t;

// Prototype for the functions
// Update checkResult in order to fit your own solution
// And optimize the doWork function
int checkResult();
void* doWork(void* args);

// You may need to change the main a bit, to fit your own solution
int main(int argc, char* argv[])
{
    std::seed_seq seedSeq (randomSeed.begin(), randomSeed.end());
    genRandom = std::mt19937 (seedSeq);

    pthread_t threadPool [NB_THREADS];

    // Initialize the barrier for all the threads
    if (pthread_barrier_init(&barrier, nullptr, NB_THREADS))
    {
        std::cerr << "Could not create the barrier" << std::endl;
        return 1;
    }

    // Initialize the semaphore that will be used by the threads
    sem_init(&semaphore, 0, 1);

    //
    // START MEASURING PERFORMANCE HERE
    //
    t = clock();

    // Initialize the threads, and indicate them to start the doWork function
    // We pass the threads' id as an argument
    for (int i = 0; i < NB_THREADS; ++i)
    {
        if (pthread_create(&threadPool[i], nullptr, doWork, (void*)(long)i))
        {
            std::cerr << "Error while creating thread " << i << std::endl;
            return 1;
        }
    }

    // Join with the newly created threads
    for (int i = 0; i < NB_THREADS; ++i)
    {
        if (pthread_join(threadPool[i], nullptr))
        {
            std::cerr << "Error while joining thread " << i << std::endl;
            return 1;
        }
    }
    // Free the memory used by the lists
    //listA.clear();
    //listB.clear();
    //listC.clear();
    //listResult.clear();

    //
    // STOP MEASURING PERFORMANCE HERE
    //
    t = clock() - t;
    printf ("Runtime was %f seconds.\n",((float)t)/CLOCKS_PER_SEC);

    // Check that the result of the computation is correct
    return checkResult();
}


// Function to optimize the performance
// You can also implement performance measurements here
void* doWork(void* arg)
{
    // Get the id of the thread
    long tid = (long)arg;

    // Fill listA with random numbers
    sem_wait(&semaphore);
    for (int i = 0; i < SIZE/20; ++i)
    {

        if (listA.size() < SIZE)
        {
            listA.push_back(genRandom());
            listB.push_back(genRandom());
            listC.push_back(genRandom());
        }

    }
    sem_post(&semaphore);

    // Synchronize all the threads, so we can make sure that all lists have been filled
    pthread_barrier_wait(&barrier);

    sem_wait(&semaphore);
    iteratorA = listA.begin();
    iteratorB = listB.begin();
    iteratorC = listC.begin();
    sem_post(&semaphore);

    // Wait here so the iterators are set at the beginning of the list for every thread
    pthread_barrier_wait(&barrier);

    // While the iterators do not reach the end of their list, threads can compute
    while (iteratorA != listA.end() && iteratorB != listB.end() && iteratorC != listC.end())
    {
        // Lock the access to all the lists
        sem_wait(&semaphore);

        // Make sure that we are still not accessing anything beyond the lists
        if (iteratorA != listA.end() && iteratorB != listB.end() && iteratorC != listC.end())
        {
            // Compute Result = A * B + C, and update the iterators
            listResult.push_back((*iteratorA) * (*iteratorB) + (*iteratorC));
            iteratorA++;
            iteratorB++;
            iteratorC++;
        }

        // Release the lock to the lists
        sem_post(&semaphore);
    }

    return nullptr;
}


// Function to check the result of the computation
// Change it, so it fits your own solution
int checkResult()
{
    // Check that all the lists have the same length and contain SIZE elements
    if (SIZE != listA.size())
    {
        std::cerr << "Error: listA does not contain " << SIZE << " elements!" << std::endl;
        std::cerr << "listA contains " << listA.size() << " elements" << std::endl;
        return 1;
    }
    if (SIZE != listB.size())
    {
        std::cerr << "Error: listB does not contain " << SIZE << " elements!" << std::endl;
        std::cerr << "listB contains " << listB.size() << " elements" << std::endl;
        return 1;
    }
    if (SIZE != listC.size())
    {
        std::cerr << "Error: listC does not contain " << SIZE << " elements!" << std::endl;
        std::cerr << "listC contains " << listC.size() << " elements" << std::endl;
        return 1;
    }
    if (SIZE != listResult.size())
    {
        std::cerr << "Error: listResult does not contain " << SIZE << " elements!" << std::endl;
        std::cerr << "listResult contains " << listResult.size() << " elements" << std::endl;
        return 1;
    }

    iteratorA = listA.begin();
    iteratorB = listB.begin();
    iteratorC = listC.begin();

    // Iterate over all the results
    for (iteratorResult = listResult.begin(); iteratorResult != listResult.end(); iteratorResult++)
    {
        // If the result is not correct, display a message and then return (we do not need to continue to check the rest of the results)
        if ((*iteratorResult) != ((*iteratorA) * (*iteratorB) + (*iteratorC)))
        {
            std::cerr << "Error: you computed the wrong result!" << std::endl;
            return 1;
        }

        // The current result is correct, so increase the iterators of the lists
        iteratorA++;
        iteratorB++;
        iteratorC++;
    }

    std::cout << "The result is correct!" << std::endl;

    return 0;
}
