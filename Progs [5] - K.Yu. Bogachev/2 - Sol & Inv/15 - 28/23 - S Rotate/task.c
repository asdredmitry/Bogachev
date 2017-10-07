#include <math.h>

#include "task.h"

int SolveSystem(int n, double* a, double* b, double* x)
{
	int i;
	int j;
	int k;
	double r;
	double tmp1;
	double tmp2;
	double cosPhi;
	double sinPhi;

	for (i = 0; i < n; ++i)
	{
		for (j = i + 1; j < n; ++j)
		{
			tmp1 = a[i * n + i];
			tmp2 = a[j * n + i];

			r = sqrt(tmp1 * tmp1 + tmp2 * tmp2);

			if (r < 1e-100)
				return -1;

			cosPhi = tmp1 / r;
			sinPhi = -tmp2 / r;

			a[i * n + i] = r;
			a[j * n + i] = 0.0;

			for (k = i + 1; k < n; ++k)
			{
				tmp1 = a[i * n + k];
				tmp2 = a[j * n + k];

				a[i * n + k] = tmp1 * cosPhi - tmp2 * sinPhi;
				a[j * n + k] = tmp1 * sinPhi + tmp2 * cosPhi;
			}

			tmp1 = b[i];
			tmp2 = b[j];

			b[i] = tmp1 * cosPhi - tmp2 * sinPhi;
			b[j] = tmp1 * sinPhi + tmp2 * cosPhi;
		}
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
