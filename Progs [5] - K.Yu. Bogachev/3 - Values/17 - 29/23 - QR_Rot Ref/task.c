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
	return a[(k - 1) * n + k - 1];
}

static void MakeShift(int n, double* a, int k, double s)
{
	int i;

	for (i = 0; i < k; ++i)
		a[i * n + i] -= s;
}

static void MakeDecomposition(int n, double* a, int k, double* cosPhi, double* sinPhi)
{
	int i;
	int j;
	double x;
	double y;
	double r;

	for (i = 0; i < k - 1; ++i)
	{
		x = a[i * n + i];
		y = a[(i + 1) * n + i];

		r = sqrt(x * x + y * y);

		if (r < 1e-100)
		{
			cosPhi[i] = (a[i * n + i] > 0.0 ? 1.0 : -1.0);
			sinPhi[i] = 0.0;
		}
		else
		{
			cosPhi[i] = x / r;
			sinPhi[i] = -y / r;
		}

		for (j = i + 1; j < k; ++j)
		{
			x = a[i * n + j];
			y = a[(i + 1) * n + j];

			a[i * n + j] = x * cosPhi[i] - y * sinPhi[i];
			a[(i + 1) * n + j] = x * sinPhi[i] + y * cosPhi[i];
		}

		a[i * n + i] = r;
		a[(i + 1) * n + i] = 0.0;
	}
}

static void CalcProduction(int n, double* a, int k, double* cosPhi, double* sinPhi)
{
	int i;
	int j;
	double x;
	double y;

	for (i = 0; i < k - 1; ++i)
		for (j = 0; j < i + 2; ++j)
		{
			x = a[j * n + i];
			y = a[j * n + i + 1];

			a[j * n + i] = x * cosPhi[i] - y * sinPhi[i];
			a[j * n + i + 1] = x * sinPhi[i] + y * cosPhi[i];
		}
}

void FindValues(int n, double* a, double* values, double eps, double* cosPhi, double* sinPhi, int* iterOut)
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

			MakeDecomposition(n, a, k, cosPhi, sinPhi);
			CalcProduction(n, a, k, cosPhi, sinPhi);

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
