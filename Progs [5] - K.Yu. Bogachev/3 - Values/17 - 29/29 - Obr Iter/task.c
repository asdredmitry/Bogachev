#include <math.h>

#include "task.h"

static int InvertMatrix(int n, double* a, double* x)
{
	int i;
	int j;
	int k;
	double tmp1;
	double tmp2;

	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
			x[i * n + j] = (double)(i == j);

	for (i = 0; i < n; ++i)
	{
		tmp1 = 0.0;
		for (j = i + 1; j < n; ++j)
			tmp1 += a[j * n + i] * a[j * n + i];

		tmp2 = sqrt(tmp1 + a[i * n + i] * a[i * n + i]);

		if (tmp2 < 1e-50)
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

		for (k = i + 1; k < n; ++k)
		{
			tmp1 = 0.0;
			for (j = i; j < n; ++j)
				tmp1 += a[j * n + i] * a[j * n + k];

			tmp1 *= 2.0;
			for (j = i; j < n; ++j)
				a[j * n + k] -= tmp1 * a[j * n + i];
		}

		for (k = 0; k < n; ++k)
		{
			tmp1 = 0.0;
			for (j = i; j < n; ++j)
				tmp1 += a[j * n + i] * x[j * n + k];

			tmp1 *= 2.0;
			for (j = i; j < n; ++j)
				x[j * n + k] -= tmp1 * a[j * n + i];
		}

		a[i * n + i] = tmp2;
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

static void MakeNorm(int n, double* x)
{
	int i;
	double tmp;

	tmp = 0.0;
	for (i = 0; i < n; ++i)
		tmp += x[i] * x[i];
	tmp = sqrt(tmp);

	for (i = 0; i < n; ++i)
		x[i] /= tmp;
}

static void Mult(int n, double* a, double* x, double* rezult)
{
	int i;
	int j;
	double tmp;

	for (i = 0; i < n; ++i)
	{
		tmp = 0.0;
		for (j = 0; j < n; ++j)
			tmp += a[i * n + j] * x[j];

		rezult[i] = tmp;
	}
}

int FindValue(int n, double* a, double lambda, double eps, double* e, double* a1, double* x2, int* iterOut)
{
	int i;
	int iter;
	double norm1;
	double norm2;
	double* x1 = e;

	for (i = 0; i < n; ++i)
		a[i * n + i] -= lambda;

	if (InvertMatrix(n, a, a1) != 0)
		return -1;

	for (i = 0; i < n; ++i)
		x2[i] = 1.0;

	MakeNorm(n, x2);

	iter = 0;

	do
	{
		for (i = 0; i < n; ++i)
			x1[i] = x2[i];

		Mult(n, a1, x1, x2);

		for (i = 0; i < n; ++i)
			if (fabs(x2[i]) < 1e-50)
				x2[i] = 0.0;

		MakeNorm(n, x2);

		norm1 = 0.0;
		for (i = 0; i < n; ++i)
			norm1 += (x1[i] - x2[i]) * (x1[i] - x2[i]);
		norm1 = sqrt(norm1);

		norm2 = 0.0;
		for (i = 0; i < n; ++i)
			norm2 += (x1[i] + x2[i]) * (x1[i] + x2[i]);
		norm2 = sqrt(norm2);

		++iter;
	}
	while (norm1 > eps && norm2 > eps);

	for (i = 0; i < n; ++i)
		e[i] = x2[i];

	*iterOut = iter;

	return 0;
}
