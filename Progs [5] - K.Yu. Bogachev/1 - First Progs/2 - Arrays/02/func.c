#include <math.h>

#include "func.h"

void func(int n, double* a)
{
	int i;
	double tmp;

	for (i = 0; i < n / 2; ++i)
	{
		tmp = a[i];
		a[i] = a[n - i - 1];
		a[n - i - 1] = tmp;
	}
}
