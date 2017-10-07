#include <stdio.h>
#include <math.h>

#include "func.h"

int func(char* fname1, char* fname2)
{
	int flag;
	double tmp1_1;
	double tmp1_2;
	double tmp1_3;
	double tmp2_1;
	double tmp2_2;
	double tmp2_3;
	FILE* fin1;
	FILE* fin2;

	fin1 = fopen(fname1, "r");

	if (!fin1)
		return -1;

	fin2 = fopen(fname2, "r");

	if (!fin2)
	{
		fclose(fin1);

		return -1;
	}

	if (fscanf(fin1, "%lf", &tmp1_1) != 1)
	{
		if (!feof(fin1))
		{
			fclose(fin1);
			fclose(fin2);

			return -2;
		}
		else
		{
			fclose(fin1);
			fclose(fin2);

			return -3;
		}
	}

	if (fscanf(fin2, "%lf", &tmp2_1) != 1)
	{
		if (!feof(fin2))
		{
			fclose(fin1);
			fclose(fin2);

			return -2;
		}
		else
		{
			fclose(fin1);
			fclose(fin2);

			return -3;
		}
	}

	if (fscanf(fin1, "%lf", &tmp1_2) != 1)
	{
		if (!feof(fin1))
		{
			fclose(fin1);
			fclose(fin2);

			return -2;
		}
		else
		{
			fclose(fin1);
			fclose(fin2);

			return -4;
		}
	}

	if (fscanf(fin2, "%lf", &tmp2_2) != 1)
	{
		if (!feof(fin2))
		{
			fclose(fin1);
			fclose(fin2);

			return -2;
		}
		else
		{
			fclose(fin1);
			fclose(fin2);

			return -4;
		}
	}

	flag = 0;

	while (1)
	{
		if (fscanf(fin1, "%lf", &tmp1_3) != 1)
		{
			if (!feof(fin1))
			{
				fclose(fin1);
				fclose(fin2);

				return -2;
			}
			else if (fscanf(fin2, "%lf", &tmp2_3) != 1)
			{
				if (!feof(fin2))
				{
					fclose(fin1);
					fclose(fin2);

					return -2;
				}
				else
				{
					fclose(fin1);
					fclose(fin2);

					if (flag == 0)
						return -4;
					else
						return 1;
				}
			}
			else
			{
				fclose(fin1);
				fclose(fin2);

				return -6;
			}

		}

		if (fscanf(fin2, "%lf", &tmp2_3) != 1)
		{
			if (!feof(fin2))
			{
				fclose(fin1);
				fclose(fin2);

				return -2;
			}
			else
			{
				fclose(fin1);
				fclose(fin2);

				return -5;
			}
		}

		if (fabs(tmp2_2 - 0.5 * (tmp1_1 + tmp1_3)) > 1e-100)
		{
			fclose(fin1);
			fclose(fin2);

			return 0;
		}
		else
			flag = 1;

		tmp1_1 = tmp1_2;
		tmp1_2 = tmp1_3;

		tmp2_1 = tmp2_2;
		tmp2_2 = tmp2_3;
	}
}
