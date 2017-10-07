#include <stdio.h>

#include "func.h"

int main(void)
{
	int rezult;
	char fname1[256];
	char fname2[256];

	system("echo \"[3;31mThanks to Yurii Silaev, whose program you are using now![0;m\"");

	printf("Please, enter first file name: ");
	scanf("%255s", fname1);

	printf("Please, enter second file name: ");
	scanf("%255s", fname2);

	rezult = func(fname1, fname2);

	switch (rezult)
	{
	case -6:
		printf("Second sequence is bigger, then first!\n");

		break;
	case -5:
		printf("First sequence is bigger, then second!\n");

		break;
	case -4:
		printf("There is not enough elements!\n");

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
		printf("No, it is not so.\n");

		break;
	case 1:
		printf("Yes, it is so.\n");

		break;
	}

	return 0;
}
