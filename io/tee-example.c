#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define READ_BUFFER 8192

int main (int argc, char *argv[]) {
  int fd;
  char buffer[READ_BUFFER];
  ssize_t numRead, numWrite;

  numRead = read(STDIN_FILENO, buffer, READ_BUFFER);

  if (numRead == -1) {
    printf("Error: Could not read() STDIN\n");
    exit(EXIT_FAILURE);
  }

  buffer[numRead] = '\0';

  if (argc == 1) {
    printf("%s", buffer);
  } else {
    fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

    if (fd == -1) {
      printf("Error: open\n");
      exit(EXIT_FAILURE);
    }

    numWrite = write(fd, buffer, numRead);

    if (numWrite == -1) {
      printf("Error: write\n");
      exit(EXIT_FAILURE);
    }
  }

  exit(EXIT_SUCCESS);
}
