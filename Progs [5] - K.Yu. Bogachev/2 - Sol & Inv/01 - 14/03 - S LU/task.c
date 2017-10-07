#include <math.h>

#include "task.h"

int SolveSystem(int n, double* a, double* b, double* x)
{
	int i;
	int j;
	int k;
	double tmp;

	for (i = 0; i < n; ++i)
	{
		if (fabs(a[i * n + i]) < 1e-100)
			return -1;

		for (j = i; j < n; ++j)
		{
			tmp = a[j * n + i];
			for (k = 0; k < i; ++k)
				tmp -= a[j * n + k] * a[k * n + i];
			a[j * n + i] = tmp;
		}

		for (j = i + 1; j < n; ++j)
		{
			tmp = a[i * n + j];
			for (k = 0; k < i; ++k)
				tmp -= a[i * n + k] * a[k * n + j];
			a[i * n + j] = tmp / a[i * n + i];
		}
	}

	for (i = 0; i < n; i++)
	{
		tmp = b[i];
		for (j = 0; j < i; j++)
			tmp -= a[i * n + j] * x[j];
		x[i] = tmp / a[i * n + i];
	}

	for (i = n - 1; i >= 0; i--)
	{
		tmp = x[i];
		for (j = i + 1; j < n; j++)
			tmp -= a[i * n + j] * x[j];
		x[i] = tmp;
	}

	return 0;
}
