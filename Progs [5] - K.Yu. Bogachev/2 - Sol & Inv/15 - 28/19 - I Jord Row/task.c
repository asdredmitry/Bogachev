#include <math.h>

#include "task.h"

int InvertMatrix(int n, double* a, double* x, int* index)
{
	int i;
	int j;
	int k;
	int indMax;
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
		indMax = i;

		for (j = i + 1; j < n; ++j)
			if (max < fabs(a[i * n + j]))
			{
				max = fabs(a[i * n + j]);
				indMax = j;
			}

		k = index[i];
		index[i] = index[indMax];
		index[indMax] = k;

		for (j = 0; j < n; ++j)
		{
			tmp = a[j * n + i];
			a[j * n + i] = a[j * n + indMax];
			a[j * n + indMax] = tmp;
		}

		if (fabs(a[i * n + i]) < 1e-100)
			return -1;

		tmp = 1.0 / a[i * n + i];
		for (j = i; j < n; ++j)
			a[i * n + j] *= tmp;

		for (j = 0; j < n; ++j)
			x[i * n + j] *= tmp;

		for (j = 0; j < i; ++j)
		{
			tmp = a[j * n + i];
			for (k = i; k < n; ++k)
				a[j * n + k] -= a[i * n + k] * tmp;

			for (k = 0; k < n; ++k)
				x[j * n + k] -= x[i * n + k] * tmp;
		}

		for (j = i + 1; j < n; ++j)
		{
			tmp = a[j * n + i];
			for (k = i; k < n; ++k)
				a[j * n + k] -= a[i * n + k] * tmp;

			for (k = 0; k < n; ++k)
				x[j * n + k] -= x[i * n + k] * tmp;
		}
	}

	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
			a[index[i] * n + j] = x[i * n + j];

	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
			x[i * n + j] = a[i * n + j];

	return 0;
}
