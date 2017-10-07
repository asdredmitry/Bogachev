#include <math.h>

#include "func.h"

void func(int n, double* a)
{
	int i;
	double tmp1;
	double tmp2;

	tmp1 = a[0];

	for (i = 1; i < n - 1; ++i)
	{
		tmp2 = a[i];
		a[i] = 0.5 * (tmp1 + a[i + 1]);
		tmp1 = tmp2;
	}
}
