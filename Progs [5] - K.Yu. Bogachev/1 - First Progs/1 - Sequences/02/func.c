#include <stdio.h>
#include <math.h>

#include "func.h"

int func(char* fname)
{
	int flag;
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

	flag = -1;

	while (fscanf(fin, "%lf", &tmp2) == 1)
	{
		if (fabs(tmp2 - tmp1) < 1e-100)
		{
			if (flag == -1)
				flag = 3;
			else if (flag != 3)
				flag = 0;
		}
		else if (tmp2 < tmp1)
		{
			if (flag == -1)
				flag = 2;
			else if (flag != 2)
				flag = 0;
		}
		else
		{
			if (flag == -1)
				flag = 1;
			else if (flag != 1)
				flag = 0;
		}

		if (flag == 0)
		{
			fclose(fin);

			return 0;
		}

		tmp1 = tmp2;
	}

	if (!feof(fin))
	{
		fclose(fin);

		return -2;
	}

	fclose(fin);

	return flag;
}
