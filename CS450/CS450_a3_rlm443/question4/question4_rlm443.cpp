#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>

sem_t sem_inc;
sem_t sem_dec;

struct arguments {
	int* count;
	int* total;
	};

void* do_work_inc(void* arg);
void* do_work_dec(void* arg);

int main(int argc, char* argv[]) {
	pthread_t worker_thread1;
	pthread_t worker_thread2;
	
	struct arguments *arg[2];
	int count = 0;
	int total = 0;

	sem_init(&sem_inc, 0, 0);
	sem_init(&sem_dec, 0, 0);

	// Build argument to threads
	arg[0] = (struct arguments *) calloc(1, sizeof(struct arguments));
	arg[0]->count = &count;
	arg[0]->total = &total;
	
	arg[1] = (struct arguments *) calloc(1, sizeof(struct arguments));
	arg[1]->count = &count;
	arg[1]->total = &total;

	// Create thread1
	if (pthread_create(&worker_thread1, nullptr,
		do_work_inc, (void* ) arg[0])) {
		fprintf(stderr, "Error while creating thread 1\n");
		return 1;
	}

	// Create thread2
	if (pthread_create(&worker_thread2, nullptr,
		do_work_dec, (void* ) arg[1])) {
		fprintf(stderr, "Error while creating thread 2\n");
		return 1;
	}

	// Join with thread
	if (pthread_join(worker_thread1, nullptr)) {
		fprintf(stderr, "Error while joining with child thread 1\n");
		return 1;
	}

	if (pthread_join(worker_thread2, nullptr)) {
		fprintf(stderr, "Error while joining with child thread 2\n");
		return 1;
	}
		
	return 0;
}

void* do_work_inc(void* arg) {
	struct arguments *argument;
	argument = (struct arguments*) arg;
	
	//Initialize arguments
	int* count = argument->count;
	int* total = argument->total;
	
	sem_post(&sem_inc);
	
	HEAD:

	sem_wait(&sem_inc);
	
	if (*total == 50) 
	{
		sem_post(&sem_dec);
		return nullptr;
	}
	
	while (*count < 10 and *total < 50)
	{
		*count += 1;
		*total += 1;
		printf("Count is now (inc fn): %d\n", *count);
	}
	
	sem_post(&sem_dec);
	
	goto HEAD;
	
	return nullptr;
} 

void* do_work_dec(void* arg) {
	struct arguments *argument;
	argument = (struct arguments*) arg;
	
	//Initialize arguments
	int* count = argument->count;
	int* total = argument->total;
	
	HEAD:
	
	sem_wait(&sem_dec);
	
	if (*total == 50) 
	{
		sem_post(&sem_inc);
		return nullptr;
	}
	
	while (*count > 0)
	{
		*count -= 1;
		*total += 1;
		printf("Count is now (dec fn): %d\n", *count);
	}
	
	sem_post(&sem_inc);
	
	goto HEAD;
	
	//goto HEAD;
	
	return nullptr;
}
