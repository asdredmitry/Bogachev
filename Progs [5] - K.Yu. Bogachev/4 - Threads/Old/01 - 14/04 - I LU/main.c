#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "help.h"
#include "task.h"

#define INPUT_FILE "data.dat"

typedef struct
{
	int n;
	double *a;
	double *x;
	int my_rank;
	int total_threads;
} ARGS;

long int thread_time = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *Inversion(void *p_arg)
{
	ARGS *arg = (ARGS*)p_arg;
	long int t1;

	t1 = get_time();
	InvMatrix(arg->n, arg->a, arg->x, arg->my_rank, arg->total_threads);
	t1 = get_time() - t1;

	pthread_mutex_lock(&mutex);
	thread_time += t1;
	pthread_mutex_unlock(&mutex);

	return NULL;
}

int main(int argc, char **argv)
{
	int i;
	int n;
	double *a;
	double *x;
	int mode;
	FILE *input;
	long int t_full;
	int total_threads;
	pthread_t *threads;
	ARGS *args;

	if (argc > 1)
		total_threads = atoi(argv[1]);
	else
	{
		printf("Incorrect usage!\n");
		return -1;
	}

	mode = 2; /* Change this for inputing from file */

	switch (mode)
	{
	case 1:
		if ((input = fopen(INPUT_FILE, "r")) == NULL)
		{
			printf("Can't open file \"%s\"!\n", INPUT_FILE);
			return -2;
		}
		else fscanf(input, "%d", &n);
		break;
	case 2:
		input = NULL;
/*
		printf("Matrix size: ");
		scanf("%d", &n);
*/
		if (argc == 3)
			n = atoi(argv[2]);
		else
		{
			printf("Incorrect usage!\n");
			return -3;
		}

		if (n <= 0)
		{
			printf("Incorrect n!\n");
			return -4;
		}
		break;
	default:
		printf("Unknown mode.\n");
		return -5;
	}

	a = (double*)malloc(n * n * sizeof(double));
	x = (double*)malloc(n * n * sizeof(double));
	threads = (pthread_t*)malloc(total_threads * sizeof(pthread_t));
	args = (ARGS*)malloc(total_threads * sizeof(ARGS));

	if (!(a && x && threads && args))
	{
		printf("Not enough memory!\n");

		if (a) free(a);
		if (x) free(x);
		if (threads) free(threads);
		if (args) free(args);

		return -4;
	}

	InputMatrix(n, a, mode, input);

	printf("Matrix A:\n");
	OutputMatrix(n, a);

	printf("\nCalculating...\n");

	for (i = 0; i < total_threads; i++)
	{
		args[i].n = n;
		args[i].a = a;
		args[i].x = x;
		args[i].my_rank = i;
		args[i].total_threads = total_threads;
	}

	t_full = get_full_time();

	for (i = 0; i < total_threads; i++)
		if (pthread_create(threads + i, 0, Inversion, args + i))
		{
			printf("Cannot create thread %d!\n", i);

			if (a) free(a);
			if (x) free(x);
			if (threads) free(threads);
			if (args) free(args);

			return -7;
		}

	for (i = 0; i < total_threads; i++)
		if (pthread_join(threads[i], 0))
		{
			printf("Cannot wait thread %d!\n", i);

			if (a) free(a);
			if (x) free(x);
			if (threads) free(threads);
			if (args) free(args);

			return -8;
		}

	t_full = get_full_time() - t_full;

	if (t_full == 0)
		t_full = 1;

	printf("\nMatrix A^{-1}:\n");
	OutputMatrix(n, x);

	printf("\n\nInversion time = %ld\nTotal threads time = %ld"\
		" (%ld%%)\nPer thread = %ld\n",
		t_full, thread_time, thread_time * 100/t_full,
		thread_time);

	if (mode == 1)
	{
		input = fopen(INPUT_FILE, "r");
		fscanf(input, "%d", &n);
	}
	InputMatrix(n, a, mode, input);

	printf("\n||A*A^{-1} - E|| = %e\n", TestMatrix(n, a, x));

	free(a);
	free(x);
	free(threads);
	free(args);

	return 0;
}
