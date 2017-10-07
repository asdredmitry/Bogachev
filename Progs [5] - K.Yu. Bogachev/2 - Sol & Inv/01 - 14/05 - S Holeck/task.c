#include <math.h>

#include "task.h"

int GetNum(int i, int j);

int GetNum(int i, int j)
{
	if (i < j)
		return j * (j + 1) / 2 + i;
	else
		return i * (i + 1) / 2 + j;
}

int SolveSystem(int n, double* a, double* b, double* x, double* d)
{
	int i;
	int j;
	int k;
	double tmp;

	for (i = 0; i < n; ++i)
	{
		tmp = a[GetNum(i, i)];
		for (j = 0; j < i; ++j)
			tmp -= a[GetNum(j, i)] * a[GetNum(j, i)] * d[j];
		d[i] = tmp > 0 ? 1.0 : -1.0;

		/* WARNING!!! THIS IS CHEAT!!! IT SHOULD NOT TO BE USED!!! */
		tmp = fabs(tmp);
		/* YOU SHOULD USE GOOD MATRIX, NOT 1.0 / (i + j + 1.0) */

		if (tmp < 1e-100)
			return -1;

		a[GetNum(i, i)] = sqrt(tmp);

		for (j = i + 1; j < n; ++j)
		{
			tmp = a[GetNum(i, j)];
			for (k = 0; k < i; ++k)
				tmp -= a[GetNum(k, i)] * d[k] * a[GetNum(k, j)];
			a[GetNum(i, j)] = tmp / (a[GetNum(i, i)] * d[i]);
		}
	}

	for (i = 0; i < n; ++i)
	{
		tmp = b[i];
		for (j = 0; j < i; ++j)
			tmp -= a[GetNum(j, i)] * x[j];
		x[i] = tmp / a[GetNum(i, i)];
	}

	for (i = n - 1; i >= 0; --i)
	{
		tmp = x[i];
		for (j = i + 1; j < n; ++j)
			tmp -= a[GetNum(i, j)] * x[j];
		x[i] = tmp / (a[GetNum(i, i)] * d[i]);
	}

	return 0;
}
