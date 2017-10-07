#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "func.h"

static int Input(int* n_out, int* m_out, double** a_out, double** b_out)
{
	int mode;
	int i;
	int n;
	int m;
	double* a;
	double* b;
	char fname[256];
	FILE* fin;

	printf("Please, choose input mode:\n");
	printf("\t1 - from file.\n");
	printf("\t2 - random.\n");
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

		if (fscanf(fin, "%d %d", &n, &m) != 2)
		{
			fclose(fin);

			return -5;
		}

		if (n < 1 || m < 1)
		{
			fclose(fin);

			return -2;
		}

		a = (double*)malloc(n * sizeof(double));
		if (!a)
		{
			fclose(fin);

			return -3;
		}

		b = (double*)malloc(m * sizeof(double));
		if (!b)
		{
			fclose(fin);

			free(a);

			return -3;
		}

		for (i = 0; i < n; ++i)
			if (fscanf(fin, "%lf", &a[i]) != 1)
			{
				fclose(fin);

				free(a);
				free(b);

				return -5;
			}

		for (i = 0; i < m; ++i)
			if (fscanf(fin, "%lf", &b[i]) != 1)
			{
				fclose(fin);

				free(a);
				free(b);

				return -5;
			}

		fclose(fin);

		*n_out = n;
		*m_out = m;
		*a_out = a;
		*b_out = b;

		return 0;
	}
	else if (mode == 2)
	{
		printf("Please, enter n: ");
		scanf("%d", &n);

		if (n < 1)
			return -2;

		printf("Please, enter m: ");
		scanf("%d", &m);

		if (m < 1)
			return -2;

		a = (double*)malloc(n * sizeof(double));
		if (!a)
			return -3;

		b = (double*)malloc(m * sizeof(double));
		if (!a)
		{
			free(a);

			return -3;
		}

		srand(time(NULL));

		for (i = 0; i < n; ++i)
		{
			a[i] = (rand() % 21 - 10) * (rand() % 101) / 100.0;
			b[i] = (rand() % 21 - 10) * (rand() % 101) / 100.0;
		}

		*n_out = n;
		*m_out = m;
		*a_out = a;
		*b_out = b;

		return 0;
	}
	else
		return -1;
}

int main(void)
{
	int i;
	int n;
	int m;
	int rezult;
	double* a;
	double* b;

	system("echo \"[3;31mThanks to Yurii Silaev, whose program you are using now![0;m\"");

	rezult = Input(&n, &m, &a, &b);

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

	printf("\nArrays:\n");
	for (i = 0; i < n; ++i)
		printf("%f ", a[i]);
	printf("\n");

	for (i = 0; i < n; ++i)
		printf("%f ", b[i]);
	printf("\n");

	func(n, m, a, b);

	printf("\nRezulting array:\n");
	for (i = 0; i < n; ++i)
		printf("%f ", a[i]);
	printf("\n");

	free(a);
	free(b);

	return 0;
}
