#include <stdio.h>
#include <math.h>

#include "func.h"

int func(char* fname, double* d_out)
{
	int length;
	double tmp;
	double sum1;
	double sum2;
	FILE* fin;

	fin = fopen(fname, "r");

	if (!fin)
		return -1;

	length = 0;
	sum1 = 0.0;
	sum2 = 0.0;

	while (fscanf(fin, "%lf", &tmp) == 1)
	{
		++length;
		sum1 += tmp;
		sum2 += tmp * tmp;
	}

	if (!feof(fin))
	{
		fclose(fin);

		return -2;
	}

	fclose(fin);

	sum1 /= length;
	sum1 *= sum1;
	sum2 /= length;

	*d_out = sqrt(sum2 - sum1);

	return length;
}
