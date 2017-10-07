#include <math.h>

#include "func.h"

void func(int m, int n, double* a, double* b, double* c)
{
	int i;
	int j;
	double tmp;

	for (i = 0; i < m; ++i)
	{
		tmp = 0.0;
		for (j = 0; j < n; ++j)
			tmp += a[i * n + j] * b[j];
		c[i] = tmp;
	}
}
