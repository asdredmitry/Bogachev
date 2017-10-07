#include <stdio.h>
#include <math.h>

#include "func.h"

int func(char* fname, double x)
{
	int number;
	double tmp;
	FILE* fin;

	fin = fopen(fname, "r");

	if (!fin)
		return -1;

	number = 0;

	while (fscanf(fin, "%lf", &tmp) == 1)
	{
		++number;
		if (fabs(x - tmp) < 1e-100)
		{
			fclose(fin);

			return number;
		}
	}

	if (!feof(fin))
	{
		fclose(fin);

		return -2;
	}

	fclose(fin);

	if (number == 0)
		return -3;

	return 0;
}
