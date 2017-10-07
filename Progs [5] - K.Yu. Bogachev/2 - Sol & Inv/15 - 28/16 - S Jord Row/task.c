#include <math.h>

#include "task.h"

int SolveSystem(int n, double* a, double* b, double* x, int* index)
{
	int i;
	int j;
	int k;
	int indMax;
	double tmp;
	double max;

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
