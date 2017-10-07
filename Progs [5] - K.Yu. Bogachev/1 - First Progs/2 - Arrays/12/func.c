#include <math.h>

#include "func.h"

double func(int n, double* a)
{
	int i;
	double rezult;

	rezult = 0.0;

	for (i = 0; i < n; ++i)
		rezult += a[i * n + i];

	return rezult;
}
