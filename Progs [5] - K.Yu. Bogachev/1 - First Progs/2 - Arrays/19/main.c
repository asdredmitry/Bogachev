#include <stdlib.h>
#include <stdio.h>

#include "func.h"

static double f1(int i, int j)
{
	return 1.0 / (i + j + 1.0);
}

static double f2(int i)
{
	return i * i;
}

static int Input(int* m_out, int* n_out, double** a_out, double** b_out, double** c_out)
{
	int mode;
	int i;
	int j;
	int m;
	int n;
	double* a;
	double* b;
	double* c;
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

		if (fscanf(fin, "%d %d", &m, &n) != 2)
		{
			fclose(fin);

			return -5;
		}

		if (m < 1 || n < 1)
		{
			fclose(fin);

			return -2;
		}

		a = (double*)malloc(m * n * sizeof(double));
		b = (double*)malloc(n * sizeof(double));
		c = (double*)malloc(m * sizeof(double));

		if (!(a && b && c))
		{
			fclose(fin);

			if (a)
				free(a);
			if (b)
				free(b);
			if (c)
				free(c);

			return -3;
		}

		for (i = 0; i < m * n; ++i)
			if (fscanf(fin, "%lf", &a[i]) != 1)
			{
				fclose(fin);

				free(a);
				free(b);
				free(c);

				return -5;
			}

		for (i = 0; i < n; ++i)
			if (fscanf(fin, "%lf", &b[i]) != 1)
			{
				fclose(fin);

				free(a);
				free(b);
				free(c);

				return -5;
			}

		fclose(fin);

		*m_out = m;
		*n_out = n;
		*a_out = a;
		*b_out = b;
		*c_out = c;

		return 0;
	}
	else if (mode == 2)
	{
		printf("Please, enter m: ");
		scanf("%d", &m);

		if (m < 1)
			return -2;

		printf("Please, enter n: ");
		scanf("%d", &n);

		if (n < 1)
			return -2;

		a = (double*)malloc(m * n * sizeof(double));
		b = (double*)malloc(n * sizeof(double));
		c = (double*)malloc(m * sizeof(double));

		if (!(a && b && c))
		{
			if (a)
				free(a);
			if (b)
				free(b);
			if (c)
				free(c);

			return -3;
		}

		for (i = 0; i < m; ++i)
			for (j = 0; j < n; ++j)
				a[i * n + j] = f1(i, j);

		for (i = 0; i < n; ++i)
			b[i] = f2(i);

		*m_out = m;
		*n_out = n;
		*a_out = a;
		*b_out = b;
		*c_out = c;

		return 0;
	}
	else
		return -1;
}

int main(void)
{
	int i;
	int j;
	int m;
	int n;
	int rezult;
	double* a;
	double* b;
	double* c;

	system("echo \"[3;31mThanks to Yurii Silaev, whose program you are using now![0;m\"");

	rezult = Input(&m, &n, &a, &b, &c);

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

	printf("\nMatrix A:\n");
	for (i = 0; i < m; ++i)
	{
		for (j = 0; j < n; ++j)
			printf("%f ", a[i * n + j]);
		printf("\n");
	}

	printf("\nVector b:\n");
	for (i = 0; i < n; ++i)
		printf("%f ", b[i]);
	printf("\n");

	func(m, n, a, b, c);

	printf("\nRezult vector:\n");
	for (i = 0; i < m; ++i)
		printf("%f ", c[i]);
	printf("\n");

	free(a);
	free(b);
	free(c);

	return 0;
}
