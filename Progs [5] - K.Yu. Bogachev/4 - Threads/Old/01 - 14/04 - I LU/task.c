#include <pthread.h>
#include <math.h>

#include "task.h"

void synchronize(int total_threads)
{
	static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	static pthread_cond_t condvar_in = PTHREAD_COND_INITIALIZER;
	static pthread_cond_t condvar_out = PTHREAD_COND_INITIALIZER;
	static int threads_in = 0;
	static int threads_out = 0;

	pthread_mutex_lock(&mutex);

	threads_in++;
	if (threads_in >= total_threads)
	{
		threads_out = 0;
		pthread_cond_broadcast(&condvar_in);
	} else
		while (threads_in < total_threads)
			pthread_cond_wait(&condvar_in,&mutex);

	threads_out++;
	if (threads_out >= total_threads)
	{
		threads_in = 0;
		pthread_cond_broadcast(&condvar_out);
	} else
		while (threads_out < total_threads)
			pthread_cond_wait(&condvar_out,&mutex);

	pthread_mutex_unlock(&mutex);
}

int InvMatrix(int n, double *a, double *x, int my_rank, int total_threads)
{
	int i, j, k;
	int first_row;
	int last_row;
	double tmp;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			x[i * n + j] = (double)(i == j);

	for (i = 0; i < n; i++)
	{
		first_row = (n - i) * my_rank;
		first_row = first_row/total_threads + i;
		last_row = (n - i) * (my_rank + 1);
		last_row = last_row/total_threads + i;

		for (j = first_row; j < last_row; j++)
		{
			tmp = a[j * n + i];
			for (k = 0; k < i; k++)
				tmp -= a[j * n + k] * a[k * n + i];
			a[j * n + i] = tmp;
		}
		synchronize(total_threads);

		first_row = (n - i - 1) * my_rank;
		first_row = first_row/total_threads + i + 1;
		last_row = (n - i - 1) * (my_rank + 1);
		last_row = last_row/total_threads + i + 1;

		for (j = first_row; j < last_row; j++)
		{
			tmp = a[i * n + j];
			for (k = 0; k < i; k++)
				tmp -= a[i * n + k] * a[k * n + j];
			a[i * n + j] = tmp/a[i * n + i];
		}
		synchronize(total_threads);
	}

	first_row = n * my_rank;
	first_row = first_row/total_threads;
	last_row = n * (my_rank + 1);
	last_row = last_row/total_threads;

	for (k = first_row; k < last_row; k++)
	{
		for (i = 0; i < n; i++)
		{
			tmp = x[i * n + k];
			for (j = 0; j < i; j++)
				tmp -= a[i * n + j] * x[j * n + k];
			x[i * n + k] = tmp/a[i * n + i];
		}

		for (i = n - 1; i >= 0; i--)
		{
			tmp = x[i * n + k];
			for (j = i + 1; j < n; j++)
				tmp -= a[i * n + j] * x[j * n + k];
			x[i * n + k] = tmp;
		}
	}

	return 0;
}
