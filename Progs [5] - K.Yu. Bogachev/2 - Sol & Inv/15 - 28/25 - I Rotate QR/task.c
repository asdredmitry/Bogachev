#include <math.h>

#include "task.h"

int InvertMatrix(int n, double* a, double* x)
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
		for (j = 0; j < n; ++j)
			x[i * n + j] = (double)(i == j);

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

			for (k = 0; k < n; ++k)
			{
				tmp1 = x[k * n + i];
				tmp2 = x[k * n + j];

				x[k * n + i] = tmp1 * cosPhi - tmp2 * sinPhi;
				x[k * n + j] = tmp1 * sinPhi + tmp2 * cosPhi;
			}

		}
	}

	for (i = 0; i < n; ++i)
		for (j = i + 1; j < n; ++j)
		{
			tmp1 = x[i * n + j];
			x[i * n + j] = x[j * n + i];
			x[j * n + i] = tmp1;
		}

	for (k = 0; k < n; ++k)
		for (i = n - 1; i >= 0; --i)
		{
			tmp1 = x[i * n + k];
			for (j = i + 1; j < n; ++j)
				tmp1 -= a[i * n + j] * x[j * n + k];
			x[i * n + k] = tmp1 / a[i * n + i];
		}

	return 0;
}
