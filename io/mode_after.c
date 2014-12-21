#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

/*
 * Write to a file that we create with mode 0000.
 * POSIX standard declares that when a file is created with ordinary O_CREAT:
 * the provided mode only applies after the creation of the file.
 */
int main(int argc, char *argv[])
{
	/* Should be able to write file even if we set 0 perms. */
	int fd = open("/tmp/test_file", O_CREAT | O_TRUNC | O_RDWR, 0);

	if (fd == -1) {
		printf("Error: Could not open file!\n");
		exit(EXIT_FAILURE);
	}

	if (write(fd, "hello\n", 7) == -1) {
		printf("Error: Failed to write to file\n");
		exit(EXIT_FAILURE);
	}

	printf("No failures detected, we wrote to a file with mode 0000\n");
	close(fd);

	/* Now, when the file is closed, we can't open it again because we
	 * have no permissions to do so.
	 */
	fd = open("/tmp/test_file", O_CREAT | O_TRUNC | O_RDWR, 0);

	if (fd == -1) {
		printf("Error: Could not reopen file, permission denied\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
