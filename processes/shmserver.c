#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SEGMENT_SIZE 64

int main(int argc, char **argv[])
{
	int shmid;
	char *shmaddr;

	/* Create or get the shared memory segment */
	if ((shmid = shmget(555, SEGMENT_SIZE, 0644 | IPC_CREAT)) == -1) {
		printf("Error: Could not get memory segment\n");
		exit(EXIT_FAILURE);
	}

	/* Attach to the shared memory segment */
	if ((shmaddr = shmat(shmid, NULL, 0)) == (char *) -1) {
		printf("Error: Could not attach to memory segment\n");
		exit(EXIT_FAILURE);
	}

	/* Write a character to the shared memory segment */
	*shmaddr = 'a';

	/* Detach the shared memory segment */
	if (shmdt(shmaddr) == -1) {
		printf("Error: Could not close memory segment\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
