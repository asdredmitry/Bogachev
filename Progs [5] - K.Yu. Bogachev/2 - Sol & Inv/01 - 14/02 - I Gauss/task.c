#include <math.h>

#include "task.h"

int InvertMatrix(int n, double* a, double* x)
{
	int i;
	int j;
	int k;
	double tmp;

	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
			x[i * n + j] = (double)(i == j);

	for (i = 0; i < n; ++i)
	{
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

	return 0;
}
