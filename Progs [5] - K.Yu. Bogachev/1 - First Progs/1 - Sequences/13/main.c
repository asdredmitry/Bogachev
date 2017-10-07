#include <stdio.h>

#include "func.h"

int main(void)
{
	int rezult;
	char fname[256];
	double x;

	system("echo \"[3;31mThanks to Yurii Silaev, whose program you are using now![0;m\"");

	printf("Please, enter file name: ");
	scanf("%255s", fname);

	rezult = func(fname, &x);

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
		printf("Answer = %d, maximum = %lf\n", rezult, x);

		break;
	}

	return 0;
}
