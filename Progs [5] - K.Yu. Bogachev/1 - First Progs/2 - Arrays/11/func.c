#include <math.h>

#include "func.h"

int func(int n, double* a)
{
	int i;
	int j;

	for (i = 0; i < n; ++i)
		for (j = i + 1; j < n; ++j)
			if (fabs(a[i * n + j] - a[j * n + i]) > 1e-100)
				return 0;

	return 1;
}
