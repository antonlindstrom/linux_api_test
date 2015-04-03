#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_ALLOCS 10000

int main(int argc, char *argv[])
{
	char *ptr[MAX_ALLOCS], *endptr;
	int freeStep, freeMin, freeMax, blockSize, numAllocs, j;

	printf("\n");

	if (argc < 3 || strcmp(argv[1], "--help") == 0) {
		printf("%s num-allocs block-size [step [min [max]]]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	numAllocs = (int)strtol(argv[2], NULL, 10);
	if (numAllocs > MAX_ALLOCS) {
		printf("numAllocs > %d\n", MAX_ALLOCS);
		exit(EXIT_FAILURE);
	}

	freeStep = (argc > 3) ? (int)strtol(argv[3], NULL, 10) : 1;
	freeMin = (argc > 4) ? (int)strtol(argv[4], NULL, 10) : 1;
	freeMax = (argc > 5) ? (int)strtol(argv[5], NULL, 10) : numAllocs;

	if (freeMax > MAX_ALLOCS) {
		printf("free-max > num-allocs\n");
		exit(EXIT_FAILURE);
	}

	printf("Initial program break:          %10p\n", sbrk(0));

	printf("Allocating %d*%d bytes\n", numAllocs, blockSize);
	for (j = 0; j < numAllocs; j++) {
		ptr[j] = malloc(blockSize);
		if (ptr[j] == NULL) {
			printf("malloc() failed!\n");
			exit(EXIT_FAILURE);
		}
	}

	printf("Program break is now:           %10p\n", sbrk(0));

	printf("Freeing blocks from %d to %d in steps of %d\n",
		freeMin, freeMax, freeStep);

	for (j = freeMin - 1; j < freeMax; j += freeStep)
		free(ptr[j]);

	printf("After free(), program break is: %10p\n", sbrk(0));
	exit(EXIT_SUCCESS);
}
