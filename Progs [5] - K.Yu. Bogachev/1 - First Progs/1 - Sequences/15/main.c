#include <stdio.h>

#include "func.h"

int main(void)
{
	int rezult;
	int i;
	int j;
	char fname[256];
	double x;

	system("echo \"[3;31mThanks to Yurii Silaev, whose program you are using now![0;m\"");

	printf("Please, enter file name: ");
	scanf("%255s", fname);

	rezult = func(fname, &x, &i, &j);

	switch (rezult)
	{
	case -3:
		printf("Sequence is empty!\n");

		break;
	case -2:
		printf("Error in reading from file!\n");

		break;
	case -1:
		printf("Cann't open file!\n");

		break;
	default:
		printf("Maximum = %lf, i = %d, j = %d\n", x, i, j);

		break;
	}

	return 0;
}
