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

static void Rot(int n, double* a)
{
	int i;
	int j;
	int k;
	double x;
	double y;
	double r;
	double cosPhi;
	double sinPhi;

	for (i = 1; i < n - 1; ++i)
	{
		for (j = i + 1; j < n; ++j)
		{
			x = a[i * n + i - 1];
			y = a[j * n + i - 1];

			if (fabs(y) < 1e-100)
				continue;

			r = sqrt(x * x + y * y);

			if (r < 1e-100)
				continue;

			cosPhi = x / r;
			sinPhi = -y / r;

			a[i * n + i - 1] = r;
			a[j * n + i - 1] = 0.0;

			for (k = i; k < n; ++k)
			{
				x = a[i * n + k];
				y = a[j * n + k];

				a[i * n + k] = x * cosPhi - y * sinPhi;
				a[j * n + k] = x * sinPhi + y * cosPhi;
			}

			for (k = 0; k < n; ++k)
			{
				x = a[k * n + i];
				y = a[k * n + j];

				a[k * n + i] = x * cosPhi - y * sinPhi;
				a[k * n + j] = x * sinPhi + y * cosPhi;
			}
		}
	}
}

static double GetShift(int n, double* a, int k)
{
	return a[(k - 1) * n + k + 1];
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

	Rot(n, a);

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
