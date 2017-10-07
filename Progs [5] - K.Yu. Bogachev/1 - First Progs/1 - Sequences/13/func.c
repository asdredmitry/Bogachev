#include <stdio.h>
#include <math.h>

#include "func.h"

int func(char* fname, double* x_out)
{
	int number;
	int length;
	double max;
	double tmp;
	FILE* fin;

	fin = fopen(fname, "r");

	if (!fin)
		return -1;

	if (fscanf(fin, "%lf", &tmp) != 1)
	{
		if (!feof(fin))
		{
			fclose(fin);

			return -2;
		}
		else
		{
			fclose(fin);

			return -3;
		}
	}

	max = tmp;
	number = 1;
	length = 1;

	while (fscanf(fin, "%lf", &tmp) == 1)
	{
		++length;
		if (tmp > max)
		{
			max = tmp;
			number = length;
		}
	}

	if (!feof(fin))
	{
		fclose(fin);

		return -2;
	}

	fclose(fin);

	*x_out = max;

	return number;
}
