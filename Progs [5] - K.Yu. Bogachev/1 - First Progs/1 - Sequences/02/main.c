#include <stdio.h>

#include "func.h"

int main(void)
{
	int rezult;
	char fname[256];

	system("echo \"[3;31mThanks to Yurii Silaev, whose program you are using now![0;m\"");

	printf("Please, enter file name: ");
	scanf("%255s", fname);

	rezult = func(fname);

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
	case 0:
		printf("Sequence is not monotonous.\n");

		break;
	case 1:
		printf("Sequence is increasing.\n");

		break;
	case 2:
		printf("Sequence is decreasing.\n");

		break;
	case 3:
		printf("Sequence is constant.\n");

		break;
	}

	return 0;
}
