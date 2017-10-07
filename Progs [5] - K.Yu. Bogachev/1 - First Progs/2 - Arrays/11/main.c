#include <stdlib.h>
#include <stdio.h>

#include "func.h"

static double f(int i, int j)
{
	return 1.0 / (i + j + 1.0);
}

static int Input(int* n_out, double** a_out)
{
	int mode;
	int i;
	int j;
	int n;
	double* a;
	char fname[256];
	FILE* fin;

	printf("Please, choose input mode:\n");
	printf("\t1 - from file.\n");
	printf("\t2 - from formula.\n");
	printf("-> ");
	scanf("%d", &mode);
	printf("\n");

	if (mode == 1)
	{
		printf("Please, enter file name: ");
		scanf("%255s", fname);

		fin = fopen(fname, "r");
		if (!fin)
			return -4;

		if (fscanf(fin, "%d", &n) != 1)
		{
			fclose(fin);

			return -5;
		}

		if (n < 1)
		{
			fclose(fin);

			return -2;
		}

		a = (double*)malloc(n * n * sizeof(double));
		if (!a)
		{
			fclose(fin);

			return -3;
		}

		for (i = 0; i < n * n; ++i)
			if (fscanf(fin, "%lf", &a[i]) != 1)
			{
				fclose(fin);

				free(a);

				return -5;
			}

		fclose(fin);

		*n_out = n;
		*a_out = a;

		return 0;
	}
	else if (mode == 2)
	{
		printf("Please, enter n: ");
		scanf("%d", &n);

		if (n < 1)
			return -2;

		a = (double*)malloc(n * n * sizeof(double));
		if (!a)
			return -3;

		for (i = 0; i < n; ++i)
			for (j = 0; j < n; ++j)
				a[i * n + j] = f(i, j);

		*n_out = n;
		*a_out = a;

		return 0;
	}
	else
		return -1;
}

int main(void)
{
	int i;
	int j;
	int n;
	int rezult;
	double* a;

	system("echo \"[3;31mThanks to Yurii Silaev, whose program you are using now![0;m\"");

	rezult = Input(&n, &a);

	switch (rezult)
	{
	case -5:
		printf("Error in reading from file!\n");

		return -5;
	case -4:
		printf("Cann't open file!\n");

		return -4;
	case -3:
		printf("Not enough memory!\n");

		return -3;
	case -2:
		printf("Incorrect n!\n");

		return -2;
	case -1:
		printf("Incorrect mode!\n");

		return -1;
	case 0:
		break;
	}

	printf("\nMatrix:\n");
	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < n; ++j)
			printf("%f ", a[i * n + j]);
		printf("\n");
	}
	printf("\n");

	rezult = func(n, a);

	switch (rezult)
	{
	case 0:
		printf("Matrix is not symmetric.\n");

		break;
	case 1:
		printf("Matrix is symmetric.\n");

		break;
	}

	free(a);

	return 0;
}
