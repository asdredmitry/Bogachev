#include <stdio.h>
#include <math.h>

#include "func.h"

int func(char* fname)
{
	int tmp1;
	int tmp2;
	int tmp3;
	int length;
	FILE* fin;

	fin = fopen(fname, "r");

	if (!fin)
		return -1;

	if (fscanf(fin, "%d", &tmp1) != 1)
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

	if (fscanf(fin, "%d", &tmp2) != 1)
	{
		if (!feof(fin))
		{
			fclose(fin);

			return -2;
		}
		else
		{
			fclose(fin);

			return -4;
		}
	}

	length = 2;

	while (fscanf(fin, "%d", &tmp3) == 1)
	{
		++length;
		if (fabs(tmp1 - (tmp2 + tmp3)) > 1e-100)
		{
			fclose(fin);

			return 0;
		}

		tmp1 = tmp2;
		tmp2 = tmp3;
	}

	if (!feof(fin))
	{
		fclose(fin);

		return -2;
	}

	fclose(fin);

	if (length == 2)
		return -4;

	if (fabs(tmp2 - 1.0) > 1e-100 || fabs(tmp1 - 1.0) > 1e-100)
		return 0;

	return 1;
}
