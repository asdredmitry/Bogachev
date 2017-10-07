#include <math.h>

#include "task.h"

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

static double ScalarProduction(int n, double* x1, double* x2)
{
	int i;
	double rezult;

	rezult = 0.0;
	for (i = 0; i < n; ++i)
		rezult += x1[i] * x2[i];

	return rezult;
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

void FindValue(int n, double* a, double* valueOut, double* x1, double* x2, int* iterOut)
{
	int i;
	int iter;
	double tmp1;
	double tmp2;
	double value;
	double valuePrev;

	x1[0] = 1.0;
	for (i = 1; i < n; ++i)
		x1[i] = 0.0;

	iter = 0;
	valuePrev = -1e300;

	while (1)
	{
		++iter;

		Mult(n, a, x1, x2);

		tmp1 = ScalarProduction(n, x1, x2);
		tmp2 = ScalarProduction(n, x1, x1);

		if (tmp2 > 0)
		{
			value = tmp1 / tmp2;

			if (fabs(value - valuePrev) < 1e-100)
				break;

			valuePrev = value;
		}

		for (i = 0; i < n; ++i)
			x1[i] = x2[i];

		if (iter % 10 == 0)
			MakeNorm(n, x1);
	}

	MakeNorm(n, x1);
	*valueOut = value;
	*iterOut = iter;
}
