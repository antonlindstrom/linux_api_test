#include <stdio.h>
#include <stdlib.h>

/*
 * A program to create a 30s zombie
 * The parent spawns a process that isn't reaped until after 30s.
 * The process will be reaped after the parent is done with sleep.
 */
int main(int argc, char **argv[])
{
	int id = fork();

	if ( id > 0 ) {
		printf("Parent is sleeping..\n");
		sleep(30);
	}

	if ( id == 0 )
		printf("Child process is done.\n");

	exit(EXIT_SUCCESS);
}
