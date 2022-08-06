#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>

struct arguments {
	int value;
	int* buffer;
	int* count;
	int* correct;
	int* otherCorrect;
	pthread_mutex_t* mutex;
	};

void* do_work(void* arg);
void* do_work2(void* arg);

int main(int argc, char* argv[]) {
	pthread_t worker_thread1;
	pthread_t worker_thread2;
	pthread_t worker_thread3;
	
	pthread_t worker_thread4;
	pthread_t worker_thread5;
	pthread_t worker_thread6;
	
	struct arguments *arg[6];
	int count = 0;
	int count2 = 0;
	
	int buffer = 0;
	int buffer2 = 0;
	
	int correct = 0;
	int correct2 = 0;
	
	pthread_mutex_t lock;
	pthread_mutex_init(&lock, nullptr);
	pthread_mutex_t lock2;
	pthread_mutex_init(&lock2, nullptr);
	

	// Build argument to threads: Work 1
	arg[0] = (struct arguments *) calloc(1, sizeof(struct arguments));
	arg[0]->value = 1;
	arg[0]->buffer = &buffer;
	arg[0]->count = &count;
	arg[0]->correct = &correct;
	arg[0]->otherCorrect = &correct2;
	arg[0]->mutex = &lock;
	
	arg[1] = (struct arguments *) calloc(1, sizeof(struct arguments));
	arg[1]->value = 2;
	arg[1]->buffer = &buffer;
	arg[1]->count = &count;
	arg[1]->correct = &correct;
	arg[1]->otherCorrect = &correct2;
	arg[1]->mutex = &lock;
	
	arg[2] = (struct arguments *) calloc(1, sizeof(struct arguments));
	arg[2]->value = 3;
	arg[2]->buffer = &buffer;
	arg[2]->count = &count;
	arg[2]->correct = &correct;
	arg[2]->otherCorrect = &correct2;
	arg[2]->mutex = &lock;
	
	// Build argument to threads: Work 2
	arg[3] = (struct arguments *) calloc(1, sizeof(struct arguments));
	arg[3]->value = 4;
	arg[3]->buffer = &buffer2;
	arg[3]->count = &count2;
	arg[3]->correct = &correct2;
	arg[3]->otherCorrect = &correct;
	arg[3]->mutex = &lock2;
	
	arg[4] = (struct arguments *) calloc(1, sizeof(struct arguments));
	arg[4]->value = 5;
	arg[4]->buffer = &buffer2;
	arg[4]->count = &count2;
	arg[4]->correct = &correct2;
	arg[4]->otherCorrect = &correct;
	arg[4]->mutex = &lock2;
	
	arg[5] = (struct arguments *) calloc(1, sizeof(struct arguments));
	arg[5]->value = 6;
	arg[5]->buffer = &buffer2;
	arg[5]->count = &count2;
	arg[5]->correct = &correct2;
	arg[5]->otherCorrect = &correct;
	arg[5]->mutex = &lock2;

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
	
	// Create thread4
	if (pthread_create(&worker_thread4, nullptr,
		do_work2, (void* ) arg[3])) {
		fprintf(stderr, "Error while creating thread 1\n");
		return 1;
	}

	// Create thread5
	if (pthread_create(&worker_thread5, nullptr,
		do_work2, (void* ) arg[4])) {
		fprintf(stderr, "Error while creating thread 2\n");
		return 1;
	}
	
	// Create thread6
	if (pthread_create(&worker_thread6, nullptr,
		do_work2, (void* ) arg[5])) {
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
		fprintf(stderr, "Error while joining with child thread 3\n");
		return 1;
	}
	
	if (pthread_join(worker_thread4, nullptr)) {
		fprintf(stderr, "Error while joining with child thread 4\n");
		return 1;
	}

	if (pthread_join(worker_thread5, nullptr)) {
		fprintf(stderr, "Error while joining with child thread 5\n");
		return 1;
	}
	
	if (pthread_join(worker_thread6, nullptr)) {
		fprintf(stderr, "Error while joining with child thread 6\n");
		return 1;
	}

	printf("Total sequences generated team1: %d\n", count);
	printf("Number of correct sequences team1: %d\n", correct);
	printf("Total sequences generated team2: %d\n", count2);
	printf("Number of correct sequences team2: %d\n", correct2);
	
	return 0;
}

void* do_work(void* arg) {
	struct arguments *argument;
	argument = (struct arguments*) arg;
	
	//Initialize arguments
	pthread_mutex_t* mutex = argument->mutex;
	int val = argument->value;
	int* correct = argument->correct;
	int* correct2 = argument->otherCorrect;
	int* count = argument->count;
	int* buffer = argument->buffer;
	
	HEAD:
	
	if (*correct2 == 10 or *correct == 10)
	{
		return nullptr;
	}
	
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
			if (*correct == 10)
			{
				printf("Team 1 won!\n");
			}
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

void* do_work2(void* arg) {
	struct arguments *argument;
	argument = (struct arguments*) arg;
	
	//Initialize arguments
	pthread_mutex_t* mutex2 = argument->mutex;
	int val = argument->value;
	int* correct2 = argument->correct;
	int* correct = argument->otherCorrect;
	int* count2 = argument->count;
	int* buffer2 = argument->buffer;
	
	HEAD:
	
	if (*correct == 10 or *correct2 == 10)
	{
		return nullptr;
	}
	
	//Add thread's value onto end of buffer
	pthread_mutex_lock(mutex2);
	printf("My id: %d\n", val);
	*buffer2 *= 10;
	*buffer2 += val;
	pthread_mutex_unlock(mutex2);
	
	//Sleep
	usleep(500000);
	
	//Check if buffer is full
	pthread_mutex_lock(mutex2);
	if (*buffer2 > 100)
	{
		
		//Increase count
		*count2 += 1;

		//If buffer is correct, print and increment count
		if (*buffer2 == 456)
		{
			printf("%d\n", *buffer2);
			*correct2 += 1;
			if (*correct2 == 10)
			{
				printf("Team 2 won!\n");
			}
		}
		
		//Reset buffer
		*buffer2 = 0;
	}
	pthread_mutex_unlock(mutex2);
	
	//Repeat until 10 correct are found
	if (*correct2 < 10)
	{
		goto HEAD;
	}

	return nullptr;
} 
