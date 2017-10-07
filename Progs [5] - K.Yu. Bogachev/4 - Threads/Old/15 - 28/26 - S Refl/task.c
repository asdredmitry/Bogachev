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

int SolveSystem(int n, double *a, double *b, double *x, int my_rank, int total_threads)
{
	int i, j, k;
	int first_row;
	int last_row;
	double tmp1, tmp2;

	for (i = 0; i < n; i++)
	{
		if (my_rank == 0)
		{
			tmp1 = 0.0;
			for (j = i + 1; j < n; j++)
				tmp1 += a[j * n + i] * a[j * n + i];

			tmp2 = sqrt(tmp1 + a[i * n + i] * a[i * n + i]);

			a[i * n + i] -= tmp2;

			x[i] = tmp1 = sqrt(tmp1 + a[i * n + i] * a[i * n + i]);
		}
		synchronize(total_threads);

		if (x[i] < 1e-100)
		{
			if (my_rank == 0)
				a[i * n + i] += tmp2;
			synchronize(total_threads);
			continue;
		}

		if (my_rank == 0)
		{
			tmp1 = 1.0/tmp1;
			for (j = i; j < n; j++)
				a[j * n + i] *= tmp1;

			tmp1 = 0.0;
			for (j = i; j < n; j++)
				tmp1 += a[j * n + i] * b[j];

			tmp1 *= 2.0;
			for (j = i; j < n; j++)
				b[j] -= tmp1 * a[j * n + i];
		}
		synchronize(total_threads);

		first_row = (n - i - 1) * my_rank;
		first_row = first_row/total_threads + i + 1;
		last_row = (n - i - 1) * (my_rank + 1);
		last_row = last_row/total_threads + i + 1;

		for (k = first_row; k < last_row; k++)
		{
			tmp1 = 0.0;
			for (j = i; j < n; j++)
				tmp1 += a[j * n + i] * a[j * n + k];

			tmp1 *= 2.0;
			for (j = i; j < n; j++)
				a[j * n + k] -= tmp1 * a[j * n + i];
		}
		synchronize(total_threads);

		if (my_rank == 0)
			a[i * n + i] = tmp2;
	}

	if (my_rank == 0)
		for (i = n - 1; i >= 0; i--)
		{
			tmp1 = b[i];
			for (j = i + 1; j < n; j++)
				tmp1 -= a[i * n + j] * x[j];
			x[i] = tmp1/a[i * n + i];
		}

	return 0;
}
