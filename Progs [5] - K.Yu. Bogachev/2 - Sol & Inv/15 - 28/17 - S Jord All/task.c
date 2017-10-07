#include <math.h>

#include "task.h"

int SolveSystem(int n, double* a, double* b, double* x, int* index)
{
	int i;
	int j;
	int k;
	int indMax1;
	int indMax2;
	double tmp;
	double max;

	for (i = 0; i < n; ++i)
		index[i] = i;

	for (i = 0; i < n; ++i)
	{
		max = fabs(a[i * n + i]);
		indMax1 = i;
		indMax2 = i;

		for (j = i; j < n; ++j)
			for (k = i; k < n; ++k)
				if (max < fabs(a[j * n + k]))
				{
					max = fabs(a[j * n + k]);
					indMax1 = j;
					indMax2 = k;
				}

		k = index[i];
		index[i] = index[indMax2];
		index[indMax2] = k;

		for (j = 0; j < n; ++j)
		{
			tmp = a[i * n + j];
			a[i * n + j] = a[indMax1 * n + j];
			a[indMax1 * n + j] = tmp;
		}

		tmp = b[i];
		b[i] = b[indMax1];
		b[indMax1] = tmp;

		for (j = 0; j < n; ++j)
		{
			tmp = a[j * n + i];
			a[j * n + i] = a[j * n + indMax2];
			a[j * n + indMax2] = tmp;
		}

		if (fabs(a[i * n + i]) < 1e-100)
			return -1;

		tmp = 1.0 / a[i * n + i];
		for (j = i; j < n; ++j)
			a[i * n + j] *= tmp;
		b[i] *= tmp;

		for (j = 0; j < i; ++j)
		{
			tmp = a[j * n + i];
			for (k = i; k < n; ++k)
				a[j * n + k] -= a[i * n + k] * tmp;
			b[j] -= b[i] * tmp;
		}

		for (j = i + 1; j < n; ++j)
		{
			tmp = a[j * n + i];
			for (k = i; k < n; ++k)
				a[j * n + k] -= a[i * n + k] * tmp;
			b[j] -= b[i] * tmp;
		}
	}

	for (i = n - 1; i >= 0; --i)
		x[index[i]] = b[i];

	return 0;
}
