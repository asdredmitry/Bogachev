#include <math.h>

#include "task.h"

int InvertMatrix(int n, double* a, double* x, int* index)
{
	int i;
	int j;
	int k;
	int indMax1;
	int indMax2;
	double tmp;
	double max;

	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
			x[i * n + j] = (double)(i == j);

	for (i = 0; i < n; ++i)
		index[i] = i;

	for (i = 0; i < n; ++i)
	{
		max = fabs(a[i * n + i]);
		indMax1 = i;
		indMax2 = i;

		for (j = i; j < n; ++j)
			for (k = i; k < n; ++k);
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

		for (j = 0; j < n; ++j)
		{
			tmp = x[i * n + j];
			x[i * n + j] = x[indMax1 * n + j];
			x[indMax1 * n + j] = tmp;
		}

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

		for (j = 0; j < n; ++j)
			x[i * n + j] *= tmp;

		for (j = i + 1; j < n; ++j)
		{
			tmp = a[j * n + i];
			for (k = i; k < n; ++k)
				a[j * n + k] -= a[i * n + k] * tmp;

			for (k = 0; k < n; ++k)
				x[j * n + k] -= x[i * n + k] * tmp;
		}
	}

	for (k = 0; k < n; ++k)
		for (i = n - 1; i >= 0; --i)
		{
			tmp = x[i * n + k];
			for (j = i + 1; j < n; ++j)
				tmp -= a[i * n + j] * x[j * n + k];
			x[i * n + k] = tmp;
		}

	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
			a[index[i] * n + j] = x[i * n + j];

	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
			x[i * n + j] = a[i * n + j];

	return 0;
}
