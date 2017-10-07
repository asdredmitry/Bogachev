#include <math.h>

#include "func.h"

int func(int n, double* a)
{
	int i;

	for (i = 0; i < n / 2; ++i)
		if (fabs(a[i] - a[n - i - 1]) > 1e-100)
			return 0;

	return 1;
}
