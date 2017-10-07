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

		tmp = 1.0 / a[i * n + i];
		for (j = i; j < n; ++j)
			a[i * n + j] *= tmp;
		b[i] *= tmp;

		for (j = i + 1; j < n; ++j)
		{
			tmp = a[j * n + i];
			for (k = i; k < n; ++k)
				a[j * n + k] -= a[i * n + k] * tmp;
			b[j] -= b[i] * tmp;
		}
	}

	for (i = n - 1; i >= 0; --i)
	{
		tmp = b[i];
		for (j = i + 1; j < n; ++j)
			tmp -= a[i * n + j] * x[j];
		x[i] = tmp;
	}

	return 0;
}
