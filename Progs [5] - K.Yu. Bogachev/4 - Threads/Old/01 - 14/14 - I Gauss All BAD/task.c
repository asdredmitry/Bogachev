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

int InvMatrix(int n, double *a, double *x, int *index, int my_rank, int total_threads)
{
	int i, j, k;
	int j1, j2, k1, k2;
	int first_row;
	int last_row;
	double tmp;

	if (my_rank == 0)
	{
		for (i = 0; i < n; i++)
			index[i] = i;

		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				x[i * n + j] = (double)(i == j);
	}

	for (i = 0; i < n; i++)
	{
		if (my_rank == 0)
		{
			k1 = i;
			k2 = i;
			for (j1 = i; j1 < n; j1++)
				for (j2 = i; j2 < n; j2++)
					if (fabs(a[k1 * n + k2]) < fabs(a[j1 * n + j2]))
					{
						k1 = j1;
						k2 = j2;
					}

			j = index[i];
			index[i] = index[k2];
			index[k2] = j;

			for (j = 0; j < n; j++)
			{
				tmp = a[i * n + j];
				a[i * n + j] = a[k1 * n + j];
				a[k1 * n + j] = tmp;
			}

			for (j = 0; j < n; j++)
			{
				tmp = a[j * n + i];
				a[j * n + i] = a[j * n + k2];
				a[j * n + k2] = tmp;
			}

			for (j = 0; j < n; j++)
			{
				tmp = x[i * n + j];
				x[i * n + j] = x[k1 * n + j];
				x[k1 * n + j] = tmp;
			}

			tmp = a[i * n + i];

			tmp = 1.0/tmp;
			for (j = i; j < n; j++)
				a[i * n + j] *= tmp;
			for (j = 0; j < n; j++)
				x[i * n + j] *= tmp;
		}
		synchronize(total_threads);

		first_row = (n - i - 1) * my_rank;
		first_row = first_row/total_threads + i + 1;
		last_row = (n - i - 1) * (my_rank + 1);
		last_row = last_row/total_threads + i + 1;

		for (j = first_row; j < last_row; j++)
		{
			tmp = a[j * n + i];
			for (k = i; k < n; k++)
				a[j * n + k] -= tmp * a[i * n + k];
			for (k = 0; k < n; k++)
				x[j * n + k] -= tmp * x[i * n + k];
		}
		synchronize(total_threads);
	}

	first_row = n * my_rank;
	first_row = first_row/total_threads;
	last_row = n * (my_rank + 1);
	last_row = last_row/total_threads;

	for (k = first_row; k < last_row; k++)
		for (i = n - 1; i >= 0; i--)
		{
			tmp = x[i * n + k];
			for (j = i + 1; j < n; j++)
				tmp -= a[i * n + j] * x[j * n + k];
			x[i * n + k] = tmp;
		}
	synchronize(total_threads);

	if (my_rank == 0)
	{
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				a[index[i] * n + j] = x[i * n + j];

		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				x[i * n + j] = a[i * n + j];
	}

	return 0;
}
