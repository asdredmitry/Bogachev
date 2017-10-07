#include <stdio.h>
#include <math.h>

#include "func.h"

int func(char* fname)
{
	int count;
	double tmp1;
	double tmp2;
	FILE* fin;

	fin = fopen(fname, "r");

	if (!fin)
		return -1;

	if (fscanf(fin, "%lf", &tmp1) != 1)
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

	count = 1;

	while (fscanf(fin, "%lf", &tmp2) == 1)
	{
		if (fabs(tmp2 - tmp1) > 1e-100)
			++count;

		tmp1 = tmp2;
	}

	if (!feof(fin))
	{
		fclose(fin);

		return -2;
	}

	fclose(fin);

	return count;
}
