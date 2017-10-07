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
	int rezult;
	int inputMode;
	double* a = NULL;
	double* x = NULL;
	double* d = NULL;
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

	a = (double*)malloc(n * (n + 1) / 2 * sizeof(double));
	x = (double*)malloc(n * (n + 1) / 2 * sizeof(double));
	d = (double*)malloc(n * sizeof(double));

	if (!(a && x))
	{
		printf("Not enough memory!\n");

		if (a)
			free(a);
		if (x)
			free(x);
		if (d)
			free(d);

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
		free(x);
		free(d);

		return -6;
	}

	printf("\nMatrix A:\n");
	PrintMatrix(n, a);
	printf("\n");

	printf("Calculating...\n");

	t = clock();
	rezult = InvertMatrix(n, a, x, d);
	t = clock() - t;

	switch (rezult)
	{
	case -1:
		printf("Can't invert - matrix is deteriorated.\n");

		break;
	case 0:
		printf("\nMatrix A^{-1}:\n");
		PrintMatrix(n, x);
		printf("\n");

		printf("Inversion time\t\t= %.2f sec.\n\n", (double)t / CLOCKS_PER_SEC);

		if (inputMode == 1)
		{
			fin = fopen(INPUT_FILE_NAME, "r");
			fscanf(fin, "%d", &n);
		}

		InputMatrix(n, a, inputMode, fin);

		if (inputMode == 1)
			fclose(fin);

		printf("Solution ||A * A^{-1} - b||\t= %e\n", SolutionError(n, a, x));

		break;
	default:
		printf("Unknown error!\n");

		break;
	}

	free(a);
	free(x);
	free(d);

	return 0;
}
