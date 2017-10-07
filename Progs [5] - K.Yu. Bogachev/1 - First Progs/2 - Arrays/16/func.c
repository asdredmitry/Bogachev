#include <math.h>

#include "func.h"

void func(int m, int n, double* a, int i, int j)
{
	int k;
	double tmp;

	for (k = 0; k < n; ++k)
	{
		tmp = a[i * n + k];
		a[i * n + k] = a[j * n + k];
		a[j * n + k] = tmp;
	}
	m = m;
}
