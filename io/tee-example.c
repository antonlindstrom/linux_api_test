#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>

#define READ_BUFFER 8192

int main (int argc, char *argv[]) {
  int fd, opt, flags;
  char buffer[READ_BUFFER];
  ssize_t numRead, numWrite;

  flags = O_RDWR | O_TRUNC | O_CREAT;

  // Set flags to append if opt -a
  while((opt = getopt(argc, argv, "a:")) != -1) {
    if (opt = 'a') {
      flags = O_RDWR | O_APPEND | O_CREAT;
    }
  }

  numRead = read(STDIN_FILENO, buffer, READ_BUFFER);

  if (numRead == -1) {
    printf("Error: Could not read() STDIN\n");
    exit(EXIT_FAILURE);
  }

  buffer[numRead] = '\0';

  // Write to STDOUT and exit
  if (argc == 1) {
    printf("%s", buffer);
    exit(EXIT_SUCCESS);
  }

  // Write to file specified last of args
  fd = open(argv[argc-1], flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

  if (fd == -1) {
    printf("Error: failed to open %s\n", argv[argc-1]);
    exit(EXIT_FAILURE);
  }

  numWrite = write(fd, buffer, numRead);

  if (numWrite == -1) {
    printf("Error: failed to write %s\n", argv[argc-1]);
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
