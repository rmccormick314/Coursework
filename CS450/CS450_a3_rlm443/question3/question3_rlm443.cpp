#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>

const int NUM_THREADS = 10;

struct arguments {
	int value;
	int* prev;
	int* total;
	pthread_mutex_t* mutex;
	};

void* do_work(void* arg);

int main(int argc, char* argv[]) {
	pthread_t worker_thread[NUM_THREADS];
	
	struct arguments *arg[NUM_THREADS];
	
	int total = 0;
	int prev = 0;
	
	pthread_mutex_t lock;
	pthread_mutex_init(&lock, nullptr);
	
	// Creating arguments
	for (int i = 0; i < NUM_THREADS; ++i)
	{
		arg[i] = (struct arguments *) calloc(1, sizeof(struct arguments));
		arg[i]-> value = i;
		arg[i]-> prev = &prev;
		arg[i]-> total = &total;
		arg[i]-> mutex = &lock;
	}
	
	// Creating child threads
	for (int i = 0; i < NUM_THREADS; ++i)
	{
		if (pthread_create(&worker_thread[i], nullptr,
				   do_work, (void* ) arg[i])) {
		    fprintf(stderr, "Error while creating thread %d\n", i);
		    return 1;
		}
	}

	// Joining with child threads
	for (int i = 0; i < NUM_THREADS; ++i)
		{
		if (pthread_join(worker_thread[i], nullptr))
		{
		    fprintf(stderr, "Error while joining with child thread %d\n", i);
		    return 1;
		}
	}

	printf("Total: %d\n", total);
	return 0;
}

void* do_work(void* arg) {
	struct arguments *argument;
	argument = (struct arguments*) arg;
	
	//Initialize arguments
	int val = argument->value;
	int* prev = argument->prev;
	int* total = argument->total;
	pthread_mutex_t* mutex = argument->mutex;
	
	HEAD:
	
	if (*total >= 990)
	{
		return nullptr;
	}
	
	if (val == *prev)
	{
		pthread_mutex_lock(mutex);
	} else {
		goto HEAD;
	}
	
	*total += val;
	printf("my num: %d, total: %d\n", val, *total);
	
	if (*prev == 9)
	{
		*prev = 0;
	} else {
		*prev += 1;
	}
	
	pthread_mutex_unlock(mutex);
	
	goto HEAD;

	return nullptr;
} 
