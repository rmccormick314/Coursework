#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>

struct arguments {
	int value;
	int* buffer;
	int* count;
	int* correct;
	pthread_mutex_t* mutex;
	};

void* do_work(void* arg);

int main(int argc, char* argv[]) {
	pthread_t worker_thread1;
	pthread_t worker_thread2;
	pthread_t worker_thread3;
	
	struct arguments *arg[3];
	int count = 0;
	int buffer = 0;
	int correct = 0;
	
	pthread_mutex_t lock;
	pthread_mutex_init(&lock, nullptr);
	

	// Build argument to threads
	arg[0] = (struct arguments *) calloc(1, sizeof(struct arguments));
	arg[0]->value = 1;
	arg[0]->buffer = &buffer;
	arg[0]->count = &count;
	arg[0]->correct = &correct;
	arg[0]->mutex = &lock;
	
	arg[1] = (struct arguments *) calloc(1, sizeof(struct arguments));
	arg[1]->value = 2;
	arg[1]->buffer = &buffer;
	arg[1]->count = &count;
	arg[1]->correct = &correct;
	arg[1]->mutex = &lock;
	
	arg[2] = (struct arguments *) calloc(1, sizeof(struct arguments));
	arg[2]->value = 3;
	arg[2]->buffer = &buffer;
	arg[2]->count = &count;
	arg[2]->correct = &correct;
	arg[2]->mutex = &lock;

	// Create thread1
	if (pthread_create(&worker_thread1, nullptr,
		do_work, (void* ) arg[0])) {
		fprintf(stderr, "Error while creating thread 1\n");
		return 1;
	}

	// Create thread2
	if (pthread_create(&worker_thread2, nullptr,
		do_work, (void* ) arg[1])) {
		fprintf(stderr, "Error while creating thread 2\n");
		return 1;
	}
	
	// Create thread3
	if (pthread_create(&worker_thread3, nullptr,
		do_work, (void* ) arg[2])) {
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
	
	if (pthread_join(worker_thread3, nullptr)) {
		fprintf(stderr, "Error while joining with child thread 2\n");
		return 1;
	}

	printf("Total sequences generated: %d\n", count);
	printf("Number of correct sequences: %d\n", correct);	
	return 0;
}

void* do_work(void* arg) {
	struct arguments *argument;
	argument = (struct arguments*) arg;
	
	//Initialize arguments
	pthread_mutex_t* mutex = argument->mutex;
	int val = argument->value;
	int* correct = argument->correct;
	int* count = argument->count;
	int* buffer = argument->buffer;
	
	HEAD:
	
	//Add thread's value onto end of buffer
	pthread_mutex_lock(mutex);
	printf("My id: %d\n", val);
	*buffer *= 10;
	*buffer += val;
	pthread_mutex_unlock(mutex);
	
	//Sleep
	usleep(500000);
	
	//Check if buffer is full
	pthread_mutex_lock(mutex);
	if (*buffer > 100)
	{
		
		//Increase count
		*count += 1;
		
		//If buffer is correct, print and increment count
		if (*buffer == 123)
		{
			printf("%d\n", *buffer);
			*correct += 1;
		}
		
		//Reset buffer
		*buffer = 0;
	}
	pthread_mutex_unlock(mutex);
	
	//Repeat until 10 correct are found
	if (*correct < 10)
	{
		goto HEAD;
	}

	return nullptr;
} 
