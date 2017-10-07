#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "matrix.h"
#include "task.h"

#define INPUT_FILE_NAME "data.dat"

int main(void)
{
	int n;
	int iter;
	int rezult;
	int inputMode;
	double eps = 1e-10;
	double lambda;
	double* a = NULL;
	double* e = NULL;
	double* a1 = NULL;
	double* x2 = NULL;
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
	e = (double*)malloc(n * sizeof(double));
	a1 = (double*)malloc(n * n * sizeof(double));
	x2 = (double*)malloc(n * sizeof(double));

	if (!(a && e && a1 && x2))
	{
		printf("Not enough memory!\n");

		if (a)
			free(a);
		if (e)
			free(e);
		if (a1)
			free(a1);
		if (x2)
			free(x2);

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
		free(e);
		free(a1);
		free(x2);

		return -6;
	}

	printf("\nMatrix A:\n");
	PrintMatrix(n, a);
	printf("\n");

	printf("Please, enter lambda: ");
	scanf("%lf", &lambda);

	printf("\nCalculating...\n");

	t = clock();
	rezult = FindValue(n, a, lambda, eps, e, a1, x2, &iter);
	t = clock() - t;

	if (rezult == 0)
	{
		printf("\nIt's vector:\n");
		PrintVector(n, e);
		printf("\n");

		printf("Finding time\t= %.2f sec.\n", (double)t / CLOCKS_PER_SEC);

		printf("Iterations\t= %d\n", iter);
	}
	else
		printf("\nYour shouldn't use matrix value!\n");

	free(a);
	free(e);
	free(a1);
	free(x2);

	return 0;
}
