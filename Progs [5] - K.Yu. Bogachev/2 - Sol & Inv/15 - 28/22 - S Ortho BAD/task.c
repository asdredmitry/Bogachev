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
		tmp1 = a[i * n + i];
		for (j = 0; j < i; ++j)
			tmp1 += a[i * n + j] * a[j * n + i];

		if (fabs(tmp1) < 1e-100)
			return -1;

		for (j = i + 1; j < n; ++j)
		{
			tmp2 = a[i * n + j];
			for (k = 0; k < i; ++k)
				tmp2 += a[i * n + k] * a[k * n + j];
			x[j] = tmp2;
		}

		tmp2 = -b[i];
		for (j = 0; j < i; ++j)
			tmp2 += a[i * n + j] * b[j];
		tmp2 /= tmp1;
		b[i] = -tmp2;

		for (j = 0; j < i; ++j)
			b[j] -= tmp2 * a[j * n + i];

		for (j = i + 1; j < n; ++j)
		{
			tmp2 = x[j] / tmp1;
			a[i * n + j] = -tmp2;

			for (k = 0; k < i; ++k)
				a[k * n + j] -= tmp2 * a[k * n + i];
		}
	}

	for (i = 0; i < n; ++i)
		x[i] = b[i];

	return 0;
}
