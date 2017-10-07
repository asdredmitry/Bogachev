#include <math.h>

#include "task.h"

int GetNum(int i, int j);

int GetNum(int i, int j)
{
	if (i < j)
		return j * (j + 1)/2 + i;
	else
		return i * (i + 1)/2 + j;
}

int InvertMatrix(int n, double* a, double* x, double* d)
{
	int i;
	int j;
	int k;
	double tmp;

	for (i = 0; i < n; ++i)
		for (j = i; j < n; ++j)
		{
			tmp = a[GetNum(j, i)];
			for (k = 0; k < i; ++k)
				tmp -= x[GetNum(i, k)] * x[GetNum(j, k)] * d[k];

			if (i == j)
			{
				if (tmp < 0)
				{
					tmp = -tmp;
					d[i] = -1.0;
				}
				else
					d[i] = 1.0;

				if (fabs(tmp) < 1e-100)
					return -1;

				tmp = sqrt(tmp);
				x[GetNum(i, i)] = tmp;
			}
			else
				x[GetNum(j, i)] = tmp / (x[GetNum(i, i)] * d[i]);
		}

	for (i = 0; i < n; ++i)
		for (j = i; j >= 0; --j)
		{
			tmp = (double)(i == j);
			for (k = j + 1; k <= i; ++k)
				tmp -= a[GetNum(i, k)] * x[GetNum(j, k)];
			a[GetNum(i, j)] = tmp / x[GetNum(j, j)];
		}

	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
		{
			tmp = 0.0;
			for (k = (i > j) ? i : j; k < n; ++k)
				tmp += d[k] * a[GetNum(k, j)] * a[GetNum(k, i)];
			x[GetNum(i, j)] = tmp;
		}

	return 0;
}
