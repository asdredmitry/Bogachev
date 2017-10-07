#include <math.h>

#include "func.h"

void func(int n, int m, double* a, double* b)
{
	int i;
	int j;

	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < m; ++j)
		{
			if (fabs(b[j] - a[i]) < 1e-100)
			{
				a[i] = 0.0;

				break;
			}
		}
	}
}
