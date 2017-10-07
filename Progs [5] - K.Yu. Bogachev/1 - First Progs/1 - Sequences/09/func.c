#include <stdio.h>
#include <math.h>

#include "func.h"

int func(char* fname)
{
	int flag;
	double tmp1;
	double tmp2;
	double tmp3;
	double d;
	double q;
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

	if (fscanf(fin, "%lf", &tmp2) != 1)
	{
		if (!feof(fin))
		{
			fclose(fin);

			return -2;
		}
		else
		{
			fclose(fin);

			return 4;
		}
	}

	d = tmp2 - tmp1;

	if (fabs(tmp1) > 1e-100)
		q = tmp2/tmp1;
	else
	{
		fclose(fin);

		return -4;
	}

	if (fabs(tmp2 - tmp1) < 1e-100)
		flag = 3;
	else
		flag = 4;

	while (fscanf(fin, "%lf", &tmp3) == 1)
	{
		if (fabs(tmp3 - tmp2) < 1e-100)
		{
			if (flag == 4)
				flag = 3;
			else if (flag != 3)
			{
				fclose(fin);

				return 0;
			}
		}
		else if (fabs(tmp3 - (tmp2 * q)) < 1e-100)
		{
			if (flag == 4)
				flag = 2;
			else if (flag != 2)
			{
				fclose(fin);

				return 0;
			}
		}
		else if (fabs(tmp3 - (tmp2 + d)) < 1e-100)
		{
			if (flag == 4)
				flag = 1;
			else if (flag != 1)
			{
				fclose(fin);

				return 0;
			}
		}
		else
		{
			fclose(fin);

			return 0;
		}

		tmp2 = tmp3;
	}

	if (!feof(fin))
	{
		fclose(fin);

		return -2;
	}

	fclose(fin);

	return flag;
}
