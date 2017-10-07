#include <math.h>

#include "func.h"

void func(int m, int n, int k, double* a, double* b, double* c)
{
	int i;
	int j;
	int l;
	double tmp;

	for (i = 0; i < m; ++i)
	{
		for (j = 0; j < k; ++j)
		{
			tmp = 0.0;
			for (l = 0; l < n; ++l)
				tmp += a[i * n + l] * b[l * k + j];
			c[i * k + j] = tmp;
		}
	}
}
