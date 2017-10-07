#include <math.h>

#include "func.h"

void func(int m, int n, double* a, int i, int j)
{
	int k;
	double tmp;

	for (k = 0; k < m; ++k)
	{
		tmp = a[k * n + i];
		a[k * n + i] = a[k * n + j];
		a[k * n + j] = tmp;
	}
}
