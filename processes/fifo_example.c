#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv[])
{
	if (mknod("myfifo", S_IFIFO|0666, 0) == -1) {
		printf("Failed to mknod\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
