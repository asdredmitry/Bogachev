#include <stdio.h>
#include <math.h>

#include "func.h"

int func(char* fname, double* x_out, int* i_out, int* j_out)
{
	int i;
	int j;
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
	i = 1;
	j = 1;
	length = 1;

	while (fscanf(fin, "%lf", &tmp) == 1)
	{
		++length;
		if (fabs(max - tmp) < 1e-100)
			j = length;
		else if (tmp > max)
		{
			max = tmp;
			i = length;
			j = i;
		}
	}

	if (!feof(fin))
	{
		fclose(fin);

		return -2;
	}

	fclose(fin);

	*x_out = max;
	*i_out = i;
	*j_out = j;

	return 0;
}
