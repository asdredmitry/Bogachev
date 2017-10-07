#include <math.h>

#include "task.h"

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

void FindValues(int n, double* a, double left, double right, double* values, int* nValuesOut, double eps, int* iterOut)
{
	int i;
	int j;
	int iter;
	int count;
	int nValues;
	int beforeLeftBorderCount;
	double currentLeft;
	double currentRight;
	double currentMiddle;

	Rot3(n, a);

	right += 1e-10;
	left -= 1e-10;

	nValues = n_(n, a, right) - n_(n, a, left);

	if (nValues == 0)
	{
		*nValuesOut = 0;
		*iterOut = 0;

		return ;
	}

	iter = 0;

	i = 0;
	beforeLeftBorderCount = n_(n, a, left);
	currentLeft = left;
	currentRight = right;

	while (i < nValues)
	{
		while (currentRight - currentLeft > eps)
		{
			currentMiddle = 0.5 * (currentLeft + currentRight);

			if (n_(n, a, currentMiddle) < i + 1 + beforeLeftBorderCount)
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

	*nValuesOut = nValues;
	*iterOut = iter;
}
