#include <stdio.h>
#include <math.h>

#include "func.h"

int func(char* fname, double x)
{
	int number;
	int length;
	double tmp;
	FILE* fin;

	fin = fopen(fname, "r");

	if (!fin)
		return -1;

	number = 0;
	length = 0;

	while (fscanf(fin, "%lf", &tmp) == 1)
	{
		++length;
		if (fabs(x - tmp) < 1e-100)
			number = length;
	}

	if (!feof(fin))
	{
		fclose(fin);

		return -2;
	}

	fclose(fin);

	if (length == 0)
		return -3;

	return number;
}
