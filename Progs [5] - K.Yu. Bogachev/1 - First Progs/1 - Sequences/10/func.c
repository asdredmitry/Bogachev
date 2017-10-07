#include <stdio.h>
#include <math.h>

#include "func.h"

int func(char* fname)
{
	int count;
	int tmp1;
	int tmp2;
	int tmp3;
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

			return 1;
		}
	}

	if (tmp1 > tmp2)
		count = 1;
	else
		count = 0;

	tmp3 = tmp2;

	while (fscanf(fin, "%d", &tmp3) == 1)
	{
		if ((tmp2 > tmp1) && (tmp2 > tmp3))
			++count;

		tmp1 = tmp2;
		tmp2 = tmp3;
	}

	if (!feof(fin))
	{
		fclose(fin);

		return -2;
	}

	fclose(fin);

	if (tmp3 > tmp1)
		++count;

	return count;
}
