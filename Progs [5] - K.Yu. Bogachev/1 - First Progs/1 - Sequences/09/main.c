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
	case -4:
		printf("There is division by zero!\n");

		break;
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
		printf("It is just some sequence.\n");

		break;
	case 1:
		printf("It is algebraical sequence.\n");

		break;
	case 2:
		printf("It is geometrical sequence.\n");

		break;
	case 3:
		printf("Sequence is constant.\n");

		break;
	case 4:
		printf("Not enough elements.\n");

		break;
	}

	return 0;
}
