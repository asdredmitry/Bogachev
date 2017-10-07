#include <stdio.h>
#include <math.h>

#include "matrix.h"

#define MAX_OUTPUT_SIZE 5

extern int GetNum(int i, int j);

static double f(int i, int j)
{
	return 1.0 / (i + j + 1.0);
}

int InputMatrix(int n, double* a, int inputMode, FILE* fin)
{
	int i;
	int j;

	if (inputMode == 1)
	{
		for (i = 0; i < n; ++i)
			for (j = 0; j < n; ++j)
				if (fscanf(fin, "%lf", &a[GetNum(i, j)]) != 1)
					return -1;
	}
	else
	{
		for (i = 0; i < n; ++i)
			for (j = 0; j < n; ++j)
				a[GetNum(i, j)] = f(i, j);
	}

	return 0;
}

void PrintMatrix(int n, double* a)
{
	int i;
	int j;
	int nPrint;

	nPrint = (n > MAX_OUTPUT_SIZE) ? MAX_OUTPUT_SIZE : n;

	for (i = 0; i < nPrint; ++i)
	{
		printf("| ");
		for (j = 0; j < nPrint; ++j)
			printf("%10.3g ", a[GetNum(i, j)]);
		printf("|\n");
	}
}

double SolutionError(int n, double* a, double* x)
{
	int i;
	int j;
	int k;
	double tmp;
	double rezult;

	rezult = 0.0;
	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < n; ++j)
		{
			tmp = 0.0;
			for (k = 0; k < n; ++k)
				tmp += a[GetNum(i, k)] * x[GetNum(k, j)];

			if (i == j)
				tmp -= 1.0;

			rezult += tmp * tmp;
		}
	}

	return sqrt(rezult);
}
