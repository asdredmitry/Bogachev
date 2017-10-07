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
			tmp = a[i * n + j];
			a[i * n + j] = a[j * n + i];
			a[j * n + i] = tmp;
		}
}
