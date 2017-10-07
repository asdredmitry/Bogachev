#include <math.h>

#include "task.h"

static double CalcNorm(int n, double* a)
{
	int i;
	int j;
	double tmp;
	double rezult;

	rezult = 0.0;
	for (i = 0; i < n; ++i)
	{
		tmp = 0.0;
		for (j = 0; j < n; ++j)
			tmp += fabs(a[i * n + j]);

		if (rezult < tmp)
			rezult = tmp;
	}

	return rezult;
}

static void Ref(int n, double* a)
{
	int i;
	int j;
	int k;
	double tmp1;
	double tmp2;

	for (i = 0; i < n - 2; ++i)
	{
		tmp1 = 0.0;
		for (j = i + 2; j < n; ++j)
			tmp1 += a[j * n + i] * a[j * n + i];

		tmp2 = sqrt(a[(i + 1) * n + i] * a[(i + 1) * n + i] + tmp1);

		if (tmp2 < 1e-100)
		{
			a[(i + 1) * n + i] = 0.0;
			a[(i + 2) * n + i] = 0.0;

			continue;
		}

		if (tmp1 < 1e-100)
		{
			a[(i + 2) * n + i] = 0.0;

			continue;
		}

		a[(i + 1) * n + i] -= tmp2;

		tmp1 = 1.0 / sqrt(a[(i + 1) * n + i] * a[(i + 1) * n + i] + tmp1);
		for (j = i + 1; j < n; ++j)
			a[j * n + i] *= tmp1;

		for (j = i + 1; j < n; ++j)
		{
			tmp1 = 0.0;
			for (k = i + 1; k < n; ++k)
				tmp1 += a[k * n + i] * a[k * n + j];

			tmp1 *= 2.0;
			for (k = i + 1; k < n; ++k)
				a[k * n + j] -= tmp1 * a[k * n + i];
		}

		for (j = 0; j < n; ++j)
		{
			tmp1 = 0.0;
			for (k = i + 1; k < n; ++k)
				tmp1 += a[k * n + i] * a[j * n + k];

			tmp1 *= 2.0;
			for (k = i + 1; k < n; ++k)
				a[j * n + k] -= tmp1 * a[k * n + i];
		}

		a[(i + 1) * n + i] = tmp2;
		for (j = i + 2; j < n; ++j)
			a[j * n + i] = 0.0;
	}
}

static double GetShift(int n, double* a, int k)
{
	return a[(k - 1) * n + k];
}

static void MakeShift(int n, double* a, int k, double s)
{
	int i;

	for (i = 0; i < k; ++i)
		a[i * n + i] -= s;
}

static void MakeDecomposition(int n, double* a, int k)
{
	int i;
	int j;

	for (i = 1; i < k; ++i)
	{
		a[i * n + i - 1] = a[i * n + i - 1] / a[(i - 1) * n + i - 1];

		for (j = i; j < k; ++j)
			a[i * n + j] -= a[i * n + i - 1] * a[(i - 1) * n + j];
	}
}

static void CalcProduction(int n, double* a, int k)
{
	int i;
	int j;

	for (i = 0; i < k; ++i)
	{
		if (i != 0)
			a[i * n + i - 1] *= a[i * n + i];

		for (j = i; j < k; ++j)
			a[i * n + j] += a[i * n + j + 1] * a[(j + 1) * n + j];
	}
}

void FindValues(int n, double* a, double* values, double eps, int* iterOut)
{
	int i;
	int k;
	int iter;
	double t;
	double s;

	iter = 0;

	t = CalcNorm(n, a) * eps;

	Ref(n, a);

	for (k = n; k > 2; --k)
		while (fabs(a[(k - 1) * n + k - 2]) > t)
		{
			s = GetShift(n, a, k);
			MakeShift(n, a, k, s);

			MakeDecomposition(n, a, k);
			CalcProduction(n, a, k);

			MakeShift(n, a, k, -s);

			++iter;
		}

	if (n > 1)
	{
		t = a[0 * n + 0] + a[1 * n + 1];
		s = a[0 * n + 0] * a[1 * n + 1] - a[0 * n + 1] * a[1 * n + 0];
		s = sqrt(t * t - 4.0 * s);

		a[0 * n + 0] = 0.5 * (t + s);
		a[1 * n + 1] = 0.5 * (t - s);
	}

	for (i = 0; i < n; ++i)
		values[i] = a[i * n + i];

	*iterOut = iter;
}
