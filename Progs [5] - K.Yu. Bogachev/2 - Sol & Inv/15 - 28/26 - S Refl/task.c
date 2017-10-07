#include <math.h>

#include "task.h"

int SolveSystem(int n, double* a, double* b, double* x)
{
	int i;
	int j;
	int k;
	double tmp1;
	double tmp2;

	for (i = 0; i < n; ++i)
	{
		tmp1 = 0.0;
		for (j = i + 1; j < n; ++j)
			tmp1 += a[j * n + i] * a[j * n + i];

		tmp2 = sqrt(tmp1 + a[i * n + i] * a[i * n + i]);

		if (tmp2 < 1e-100)
			return -1;

		a[i * n + i] -= tmp2;

		tmp1 = sqrt(tmp1 + a[i * n + i] * a[i * n + i]);

		if (tmp1 < 1e-100)
		{
			a[i * n + i] += tmp2;
			continue;
		}

		tmp1 = 1.0 / tmp1;
		for (j = i; j < n; ++j)
			a[j * n + i] *= tmp1;

		tmp1 = 0.0;
		for (j = i; j < n; ++j)
			tmp1 += a[j * n + i] * b[j];

		tmp1 *= 2.0;
		for (j = i; j < n; ++j)
			b[j] -= tmp1 * a[j * n + i];

		for (k = i + 1; k < n; ++k)
		{
			tmp1 = 0.0;
			for (j = i; j < n; ++j)
				tmp1 += a[j * n + i] * a[j * n + k];

			tmp1 *= 2.0;
			for (j = i; j < n; ++j)
				a[j * n + k] -= tmp1 * a[j * n + i];
		}

		a[i * n + i] = tmp2;
	}

	for (i = n - 1; i >= 0; --i)
	{
		tmp1 = b[i];
		for (j = i + 1; j < n; ++j)
			tmp1 -= a[i * n + j] * x[j];
		x[i] = tmp1 / a[i * n + i];
	}

	return 0;
}
