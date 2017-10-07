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

int SolveSystem(int n, double *a, double *b, double *x, int *index, int my_rank, int total_threads)
{
	int i, j, k;
	int j1, j2, k1, k2;
	int first_row;
	int last_row;
	double tmp;

	for (i = 0; i < n; i++)
		index[i] = i;

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

			tmp = b[i];
			b[i] = b[k1];
			b[k1] = tmp;

			tmp = a[i * n + i];

			tmp = 1.0/tmp;
			for (j = i; j < n; j++)
				a[i * n + j] *= tmp;
			b[i] *= tmp;
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
			b[j] -= tmp * b[i];
		}
		synchronize(total_threads);
	}

	if (my_rank == 0)
		for (i = n - 1; i >= 0; i--)
		{
			tmp = b[i];
			for (j = i + 1; j < n; j++)
				tmp -= a[i * n + j] * x[index[j]];
			x[index[i]] = tmp;
		}

	return 0;
}
