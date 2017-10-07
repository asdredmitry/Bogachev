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

static void Rot3(int n, double* a)
{
	int i;
	int j;
	int k;
	double x;
	double y;
	double r;
	double s;
	double a_ii;
	double a_ij;
	double a_ji;
	double a_jj;
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

			a[i * n + i - 1] = a[(i - 1) * n + i] = r;
			a[j * n + i - 1] = a[(i - 1) * n + j] = 0.0;

			for (k = i + 1; k < n; ++k)
			{
				if (k == j)
					continue;

				x = a[i * n + k];
				y = a[j * n + k];
				a[k * n + i] = a[i * n + k] = x * cosPhi - y * sinPhi;
				a[k * n + j] = a[j * n + k] = x * sinPhi + y * cosPhi;
			}

			x = a[i * n + i];
			y = a[j * n + j];
			r = a[i * n + j];
			s = a[j * n + i];

			a_ii = x * cosPhi - s * sinPhi;
			a_ji = x * sinPhi + s * cosPhi;
			a_ij = r * cosPhi - y * sinPhi;
			a_jj = r * sinPhi + y * cosPhi;

			a[i * n + i] = a_ii * cosPhi - a_ij * sinPhi;
			a[j * n + i] = a_ii * sinPhi + a_ij * cosPhi;
			a[i * n + j] = a[j * n + i];
			a[j * n + j] = a_ji * sinPhi + a_jj * cosPhi;
		}
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
	double tmp;

	for (i = 0; i < k - 1; ++i)
	{
		tmp = a[i * n + i] - (i > 0 ? a[i * n + i - 1] * a[i * n + i - 1] : 0.0);

		if (tmp < 1e-100)
			tmp = 1e-10;

		a[i * n + i] = sqrt(tmp);

		a[(i + 1) * n + i] /= a[i * n + i];
	}

	tmp = a[(k - 1) * n + k - 1] - a[(k - 1) * n + k - 2] * a[(k - 1) * n + k - 2];

	if (tmp < 1e-100)
		tmp = sqrt(tmp);

	a[(k - 1) * n + k - 1] = sqrt(tmp);
}

static void CalcProduction(int n, double* a, int k)
{
	int i;
	double tmp1;
	double tmp2;

	for (i = 0; i < k - 1; ++i)
	{
		tmp1 = a[i * n + i];
		tmp2 = a[(i + 1) * n + i];

		if (i != 0)
			a[i * n + i - 1] *= tmp1;

		a[i * n + i] = tmp1 * tmp1 + tmp2 * tmp2;
		a[i * n + i + 1] = tmp2 * a[(i + 1) * n + i + 1];
	}

	tmp1 = a[(k - 1) * n + k - 1];
	a[(k - 1) * n + k - 2] *= tmp1;
	a[(k - 1) * n + k - 1] *= tmp1;
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

	Rot3(n, a);

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
