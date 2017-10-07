#include <stdio.h>
#include <math.h>

#include "func.h"

int func(char* fname, double x, int* i_out, int* j_out)
{
	int i;
	int j;
	int length;
	double tmp;
	FILE* fin;

	fin = fopen(fname, "r");

	if (!fin)
		return -1;

	i = -1;
	j = -1;
	length = 0;

	while (fscanf(fin, "%lf", &tmp) == 1)
	{
		++length;
		if (fabs(x - tmp) < 1e-100)
		{
			if (i == -1)
				i = length;
			j = length;
		}
	}

	if (!feof(fin))
	{
		fclose(fin);

		return -2;
	}

	fclose(fin);

	if (i == -1)
		return 0;

	*i_out = i;
	*j_out = j;

	return 1;
}
