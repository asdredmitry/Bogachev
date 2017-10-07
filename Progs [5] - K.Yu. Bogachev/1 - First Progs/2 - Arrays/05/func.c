#include <math.h>

#include "func.h"

void func(int n, double* a, double x)
{
	int i;
	int last;
	double tmp;

	last = 0;

	for (i = 0; i < n; ++i)
	{
		if (a[i] < x)
		{
			tmp = a[i];
			a[i] = a[last];
			a[last] = tmp;

			++last;
		}
	}
}
