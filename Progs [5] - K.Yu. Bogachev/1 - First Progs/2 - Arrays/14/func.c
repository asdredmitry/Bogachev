#include <math.h>

#include "func.h"

void func(int n, double* a)
{
	int i;
	int j;
	double tmp;

	for (i = 0; i < n; ++i)
		for (j = i + 1; j < n; ++j)
		{
			tmp = 0.5 * (a[i * n + j] + a[j * n + i]);
			a[i * n + j] = tmp;
			a[j * n + i] = tmp;
		}
}
