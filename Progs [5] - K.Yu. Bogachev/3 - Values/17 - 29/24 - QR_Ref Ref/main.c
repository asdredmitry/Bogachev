#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "matrix.h"
#include "task.h"

#define INPUT_FILE_NAME "data.dat"

int main(void)
{
	int i;
	int j;
	int n;
	int iter;
	int rezult;
	int inputMode;
	double eps = 1e-10;
	double inv1;
	double inv2;
	double* a = NULL;
	double* x1 = NULL;
	double* x2 = NULL;
	double* values = NULL;
	FILE* fin = NULL;
	clock_t t;

	system("echo \"[3;31mThanks to Yurii Silaev, whose program you are using now![0;m\"");

	printf("Input mode : 1 - from file \"%s\".\n", INPUT_FILE_NAME);
	printf("             2 - from formula.\n");
	printf("-> ");
	scanf("%d", &inputMode);

	switch (inputMode)
	{
	case 1:
		fin = fopen(INPUT_FILE_NAME, "r");

		if (!fin)
		{
			printf("Cann't open file!\n");

			return -1;
		}

		if (fscanf(fin, "%d", &n) != 1)
		{
			printf("Error in reading from file!\n");

			fclose(fin);

			return -2;
		}

		break;
	case 2:
		printf("Please, enter N: ");
		scanf("%d", &n);

		break;
	default:
		printf("Incorrect mode!\n");

		return -3;
	}

	if (n < 1)
	{
		printf("Incorrect N!\n");

		if (inputMode == 1)
			fclose(fin);

		return -4;
	}

	a = (double*)malloc(n * n * sizeof(double));
	x1 = (double*)malloc(n * sizeof(double));
	x2 = (double*)malloc(n * sizeof(double));
	values = (double*)malloc(n * sizeof(double));

	if (!(a && x1 && x2 && values))
	{
		printf("Not enough memory!\n");

		if (a)
			free(a);
		if (x1)
			free(x1);
		if (x2)
			free(x2);
		if (values)
			free(values);

		if (inputMode == 1)
			fclose(fin);

		return -5;
	}

	rezult = InputMatrix(n, a, inputMode, fin);

	if (inputMode == 1)
		fclose(fin);

	if (rezult == -1)
	{
		printf("Error in reading from file!\n");

		free(a);
		free(x1);
		free(x2);
		free(values);

		return -6;
	}

	printf("\nMatrix A:\n");
	PrintMatrix(n, a);
	printf("\n");

	printf("Calculating...\n");

	inv1 = 0.0;
	inv2 = 0.0;
	for (i = 0; i < n; ++i)
	{
		inv1 -= a[i * n + i];
		for (j = 0; j < n; ++j)
			inv2 -= a[i * n + j] * a[j * n + i];
	}

	t = clock();
	FindValues(n, a, values, eps, x1, x2, &iter);
	t = clock() - t;

	for (i = 0; i < n; ++i)
	{
		inv1 += values[i];
		inv2 += values[i] * values[i];
	}

	printf("\nValues:\n");
	PrintVector(n, values);
	printf("\n");

	printf("Finding time\t= %.2f sec.\n", (double)t / CLOCKS_PER_SEC);
	printf("Iterations\t= %d\n\n", iter);

	printf("Sum(x_i) - Sum(a_i)\t\t= %g\n", inv1);
	printf("Sum(x_i ^ 2) - Sum(a_ij * a_ji)\t= %g\n", inv2);

	free(a);
	free(x1);
	free(x2);
	free(values);

	return 0;
}
