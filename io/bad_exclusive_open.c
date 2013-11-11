#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

/*
 * This program shows an example when another program can open a file
 * between the both open() calls.
 *
 */

int main(int argc, char *argv[]) {
  int fd;

  fd = open(argv[1], O_WRONLY);

  if (fd != -1) {

    printf("[PID %ld] File \"%s\" already exists\n", (long) getpid(), argv[1]);
    close(fd);

  } else {

    if (errno != ENOENT) {

      printf("Error: Could not open file!\n");
      exit(EXIT_FAILURE);

    } else {

      fd = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

      if ( fd == -1) {
        printf("Error: Could not open file!\n");
        exit(EXIT_FAILURE);
      }

      printf("[PID %ld] Created file \"%s\" exclusively\n", (long) getpid(), argv[1]);
    }

  }

}
