#include <math.h>

#include "func.h"

int func(int n, double* a, double x)
{
	int i;
	int j;

	for (i = 0; i < n; ++i)
	{
		if (a[i] < x)
		{
			--n;

			for (j = i; j < n; ++j)
				a[j] = a[j + 1];

			--i;
		}
	}

	return n;
}
