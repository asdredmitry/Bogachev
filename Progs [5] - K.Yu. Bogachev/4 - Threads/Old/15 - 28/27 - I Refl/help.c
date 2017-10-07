#include <sys/resource.h>
#include <sys/time.h>
#include <stdio.h>
#include <math.h>

#include "help.h"

#define MAX_OUTPUT_SIZE 5

double f(int i, int j)
{
	return 1.0/(i + j + 1.0);// + (i == j);
}

void InputMatrix(int n, double *a, int mode, FILE *input)
{
	int i, j;

	if (mode == 1)
	{
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				fscanf(input, "%lf", &a[i * n + j]);
		fclose(input);
	}
	else
	{
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				a[i * n + j] = f(i, j);
	}
}

void OutputMatrix(int n, double *a)
{
	int i, j;
	int m = (n > MAX_OUTPUT_SIZE) ? MAX_OUTPUT_SIZE : n;

	for (i = 0; i < m; i++)
	{
		printf("| ");
		for (j = 0; j < m; j++)
			printf("%10.3g ", a[i * n +j]);
		printf(" |\n");
	}
}

double TestMatrix(int n, double *a, double *x)
{
	int i, j, k;
	double tmp;
	double rezult;

	rezult = 0.0;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			tmp = 0.0;
			for (k = 0; k < n; k++)
				tmp += a[i * n + k] * x[k * n + j];
			if (i == j)
				tmp -= 1.0;
			rezult += tmp * tmp;
		}

	return sqrt(rezult);
}

long int get_time(void)
{
	struct rusage buf;

	getrusage(RUSAGE_SELF, &buf);

	return buf.ru_utime.tv_sec * 100 + buf.ru_utime.tv_usec/10000;
}

long int get_full_time(void)
{
	struct timeval buf;

	gettimeofday(&buf, 0);

	return buf.tv_sec * 100 + buf.tv_usec/10000;
}
