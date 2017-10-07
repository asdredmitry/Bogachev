#include <math.h>

#include "func.h"

void func(int n, double* a)
{
	int i;
	double tmp1;
	double tmp2;

	tmp1 = a[n - 1];

	for (i = 0; i < n; ++i)
	{
		tmp2 = a[i];
		a[i] = tmp1;
		tmp1 = tmp2;
	}
}
