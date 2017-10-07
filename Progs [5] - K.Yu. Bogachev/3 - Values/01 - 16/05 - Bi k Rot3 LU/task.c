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

static int n_(int n, double* a, double lambda)
{
	int i;
	int rezult;
	double l;

	l = a[0 * n + 0] - lambda;
	rezult = l < 0.0 ? 1 : 0;

	for (i = 1; i < n; ++i)
	{
		if (fabs(l) < 1e-100)
			l = 1e-10;

		l = a[i * n + i] - lambda - a[i * n + i - 1] * a[(i - 1) * n + i] / l;

		if (l < 0)
			++rezult;
	}

	return rezult;
}

void FindValue(int n, double* a, int k, double* valueOut, double eps, int* iterOut)
{
	int iter;
	double left;
	double right;
	double middle;

	right = CalcNorm(n, a) + 1e-10;
	left = -right;

	iter = 0;

	Rot3(n, a);

	while (right - left > eps)
	{
		middle = 0.5 * (left + right);

		if (n_(n, a, middle) < k)
			left = middle;
		else
			right = middle;

		++iter;
	}

	*valueOut = 0.5 * (left + right);
	*iterOut = iter;
}
