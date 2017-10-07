#include <stdio.h>
#include <math.h>

#include "matrix.h"

#define MAX_OUTPUT_SIZE 5

static double f(int i, int j, int k1, int k2)
{
	if ((i - j > k1) || (j - i > k2))
		return 0.0;
	else
		return 1.0 / (i + j + 1.0);
}

int InputMatrix(int n, int k1, int k2, double* a, double* b, int inputMode, FILE* fin)
{
	int i;
	int j;
	double tmp;

	if (inputMode == 1)
	{
		for (i = 0; i < n; ++i)
		{
			for (j = 0; j < n; ++j)
				if (fscanf(fin, "%lf", &a[i * n + j]) != 1)
					return -1;

			if (fscanf(fin, "%lf", &b[i]) != 1)
				return -1;
		}
	}
	else
	{
		for (i = 0; i < n; ++i)
		{
			tmp = 0.0;
			for (j = 0; j < n; ++j)
			{
				a[i * n + j] = f(i, j, k1, k2);
				if (j % 2 == 0)
					tmp += a[i * n + j];
			}
			b[i] = tmp;
		}
	}

	return 0;
}

void PrintMatrix(int n, double* a, double* b)
{
	int i;
	int j;
	int nPrint;

	nPrint = (n > MAX_OUTPUT_SIZE) ? MAX_OUTPUT_SIZE : n;

	for (i = 0; i < nPrint; ++i)
	{
		printf("| ");
		for (j = 0; j < nPrint; ++j)
			printf("%10.3g ", a[i * n + j]);
		printf("|\t%10.3g\n", b[i]);
	}
}

void PrintVector(int n, double* x)
{
	int i;
	int nPrint;

	nPrint = (n > MAX_OUTPUT_SIZE) ? MAX_OUTPUT_SIZE : n;

	for (i = 0; i < nPrint; ++i)
		printf("%10.3g ", x[i]);
	printf("\n");
}

double SolutionError(int n, double* a, double* b, double* x)
{
	int i;
	int j;
	double tmp;
	double rezult;

	rezult = 0.0;
	for (i = 0; i < n; ++i)
	{
		tmp = 0.0;
		for (j = 0; j < n; ++j)
			tmp += a[i * n + j] * x[j];
		tmp -= b[i];

		rezult += tmp * tmp;
	}

	return sqrt(rezult);
}

double SolutionAccuracy(int n, double* x)
{
	int i;
	double tmp;
	double rezult;

	rezult = 0.0;
	for (i = 0; i < n; ++i)
	{
		tmp = x[i];

		if (i % 2 == 0)
			tmp -= 1.0;

		rezult += tmp * tmp;
	}

	return sqrt(rezult);
}
