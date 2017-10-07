#include <math.h>

#include "task.h"

#define SQ2 0.707106781186547461715

static double CalcNorm(int n, double* x)
{
	int i;
	double rezult;

	rezult = 0.0;
	for (i = 0; i < n; ++i)
		rezult += x[i] * x[i];
	rezult = sqrt(rezult);

	return rezult;
}

void FindValues(int n, double* a, double* values, double eps, int* iterOut)
{
	int i;
	int j;
	int iNil;
	int jNil;
	int iter;
	double x;
	double y;
	double cosPhi;
	double sinPhi;
	double *b = values;

	iter = 0;

	for (i = 0; i < n; ++i)
		b[i] = 0.0;

	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
			if (i != j)
				b[i] += a[i * n + j] * a[i * n + j];

	while (CalcNorm(n, b) > eps)
	{
		iNil = 0;
		jNil = 1;
		for (i = 0; i < n; ++i)
			for (j = i + 1; j < n; ++j)
				if (fabs(a[iNil * n + jNil]) < fabs(a[i * n + j]))
				{
					iNil = i;
					jNil = j;
				}

		x = -2.0 * a[iNil * n + jNil];
		y = a[iNil * n + iNil] - a[jNil * n + jNil];

		if (fabs(y) < 1e-100)
		{
			cosPhi = SQ2;
			sinPhi = SQ2;
		}
		else
		{
			cosPhi = SQ2 * sqrt(1.0 + fabs(y) / sqrt(x * x + y * y));
			sinPhi = 0.5 * (x * y > 0 ? 1.0 : -1.0) * fabs(x) / (cosPhi * sqrt(x * x + y * y));
		}

		for (j = 0; j < n; ++j)
		{
			x = a[iNil * n + j];
			a[iNil * n + j] = x * cosPhi - a[jNil * n + j] * sinPhi;
			a[jNil * n + j] = x * sinPhi + a[jNil * n + j] * cosPhi;
		}

		for (j = 0; j < n; ++j)
			if (j != iNil && j != jNil)
			{
				a[j * n + iNil] = a[iNil * n + j];
				a[j * n + jNil] = a[jNil * n + j];
			}

		x = a[iNil * (n + 1)];
		a[iNil * n + iNil] = x * cosPhi - a[iNil * n + jNil] * sinPhi;
		y = a[jNil * n + iNil];
		a[jNil * n + jNil] = y * sinPhi + a[jNil * (n + 1)] * cosPhi;

		a[iNil * n + jNil] = 0.0;
		a[jNil * n + iNil] = 0.0;

		b[iNil] = 0.0;
		for (i = 0; i < n; ++i)
			if (i != iNil)
				b[iNil] += a[i * n + iNil] * a[i * n + iNil];

		b[jNil] = 0.0;
		for (j = 0; j < n; ++j)
			if (j != jNil)
				b[jNil] += a[j * n + jNil] * a[j * n + jNil];

		++iter;
	}

	for (i = 0; i < n; ++i)
		values[i] = a[i * n + i];

	*iterOut = iter;
}
