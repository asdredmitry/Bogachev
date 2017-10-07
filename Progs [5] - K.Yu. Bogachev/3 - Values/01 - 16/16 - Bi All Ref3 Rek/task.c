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

static void Ref3(int n, double* a)
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
			for (k = i + 1; k < n; k++)
				tmp1 += a[j * n + k] * a[k * n + i];
			a[i * n + j] = tmp1;
		}

		tmp1 = 0.0;
		for (j = i + 1; j < n; ++j)
			tmp1 += a[i * n + j] * a[j * n + i];
		tmp1 *= 2.0;

		for (j = i + 1; j < n; ++j)
			a[i * n + j] = 2.0 * a[i * n + j] - tmp1 * a[j * n + i];

		for (j = i + 1; j < n; ++j)
			for (k = i + 1; k < n; ++k)
				a[j * n + k] -= a[i * n + j] * a[k * n + i] + a[i * n + k] * a[j * n + i];

		a[(i + 1) * n + i] = tmp2;
		a[i * n + i + 1] = tmp2;
		for (j = i + 2; j < n; ++j)
		{
			a[j * n + i] = 0.0;
			a[i * n + j] = 0.0;
		}
	}
}

static int n_(int n, double* a, double lambda)
{
	int i;
	int rezult;
	double x;
	double y;
	double u;
	double v;
	double tmp;
	double a_k;
	double b_k1;
	double gamma;

	x = a[0 * n + 0] - lambda;
	y = 1.0;
	rezult = x < 0.0 ? 1 : 0;

	for (i = 1; i < n; ++i)
	{
		a_k = a[i * n + i] - lambda;
		b_k1 = a[i * n + i - 1];

		tmp = fabs(b_k1 * b_k1 * y);

		if (fabs(x) > tmp)
			tmp = fabs(x);

		if (tmp < 1e-50)
			tmp = 1e-15;

		gamma = 1e15 / tmp;
		u = gamma * (a_k * x - b_k1 * b_k1 * y);
		v = gamma * x;

		if (u * x < 0.0)
			++rezult;

		x = u;
		y = v;
	}

	return rezult;
}

void FindValues(int n, double* a, double* values, double eps, int* iterOut)
{
	int i;
	int j;
	int iter;
	int count;
	double left;
	double right;
	double currentLeft;
	double currentRight;
	double currentMiddle;

	Ref3(n, a);

	right = CalcNorm(n, a) + 1e-10;
	left = -right;

	iter = 0;

	i = 0;
	currentLeft = left;
	currentRight = right;

	while (i < n)
	{
		while (currentRight - currentLeft > eps)
		{
			currentMiddle = 0.5 * (currentLeft + currentRight);

			if (n_(n, a, currentMiddle) < i + 1)
				currentLeft = currentMiddle;
			else
				currentRight = currentMiddle;

			++iter;
		}

		currentMiddle = 0.5 * (currentLeft + currentRight);
		count = n_(n, a, currentRight) - n_(n, a, currentLeft);

		for (j = 0; j < count; ++j)
			values[i + j] = currentMiddle;

		i += count;

		currentLeft = currentMiddle;
		currentRight = right;
	}

	*iterOut = iter;
}
