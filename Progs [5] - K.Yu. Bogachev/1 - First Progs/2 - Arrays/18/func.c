#include <math.h>

#include "func.h"

void func(int m, int n, double* a, int i, int j, double b)
{
	int k;

	for (k = 0; k < n; ++k)
	{
		a[j * n + k] += b * a[i * n + k];
	}
	m = m;
}
