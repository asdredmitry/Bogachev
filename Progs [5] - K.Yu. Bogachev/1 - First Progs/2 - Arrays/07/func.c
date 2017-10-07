#include <math.h>

#include "func.h"

void func(int n, double* a, int k)
{
	int i;
	int j;
	double tmp1;
	double tmp2;

	while (k < 0)
		k += n;
	k %= n;

	tmp1 = a[0];
	j = 0;

	for (i = 0; i < n; ++i)
	{
		tmp2 = a[((i + 1) * k) % n + j];
		a[((i + 1) * k) % n + j] = tmp1;
		tmp1 = tmp2;

		if (((i + 1) * k) % n == 0 && i != n - 1)
		{
			++j;
			tmp1 = a[((i + 1) * k) % n + j];
		}
	}
}
