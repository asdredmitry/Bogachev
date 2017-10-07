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
	int nValues;
	int inputMode;
	double eps = 1e-10;
	double left;
	double right;
	double* a = NULL;
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
	values = (double*)malloc(n * sizeof(double));

	if (!(a && values))
	{
		printf("Not enough memory!\n");

		if (a)
			free(a);
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
		free(values);

		return -6;
	}

	printf("\nMatrix A:\n");
	PrintMatrix(n, a);
	printf("\n");

	printf("Please, enter left and right borders: ");
	scanf("%lf%lf", &left, &right);
	printf("\n");

	if ((right < left) || (fabs(right - left) < 1e-100))
	{
		printf("Wrong input!\n");

		free(a);
		free(values);

		return -7;
	}

	printf("Calculating...\n");

	t = clock();
	FindValues(n, a, left, right, values, &nValues, eps, &iter);
	t = clock() - t;

	if (nValues > 0)
	{
		printf("\nNumber of values = %d\n", nValues);
		printf("\nValues:\n");
		PrintVector(nValues, values);
		printf("\n");

		printf("Finding time\t= %.2f sec.\n", (double)t / CLOCKS_PER_SEC);
		printf("Iterations\t= %d\n", iter);
	}
	else
		printf("\nThere is no values.\n");

	free(a);
	free(values);

	return 0;
}
