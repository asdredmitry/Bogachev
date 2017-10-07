#include <stdio.h>
#include <math.h>

#include "matrix.h"

#define MAX_OUTPUT_SIZE 5

static double f(int i, int j, int n)
{
	if (i == n - 1)
		return j + 1.0;
	else if (j == n - 1)
		return i + 1.0;
	else
		return (double)(i == j);
}

int InputMatrix(int n, double* a, int inputMode, FILE* fin)
{
	int i;
	int j;

	if (inputMode == 1)
	{
		for (i = 0; i < n; ++i)
			for (j = 0; j < n; ++j)
				if (fscanf(fin, "%lf", &a[i * n + j]) != 1)
					return -1;
	}
	else
	{
		for (i = 0; i < n; ++i)
			for (j = 0; j < n; ++j)
				a[i * n + j] = f(i, j, n);
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
			printf("%10.3g ", a[i * n + j]);
		printf("|\n");
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
