#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
  int i, fd, flags, perms, bytes;
  int lseek_on = 0;

  // Take up to 3 arguments
  if (argc < 2 || argc > 4) {
    printf("Usage: %s filename num-bytes [x]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if (argc == 4 && strcmp(argv[3], "x") == 0) {
    lseek_on = 1;
  }

  bytes = atoi(argv[2]);
  perms = S_IRUSR | S_IWUSR;

  // x is supplied, use lseek instead of O_APPEND
  if (lseek_on == 1) {
    printf("Appending with lseek()\n");
    flags = O_WRONLY | O_CREAT | O_TRUNC;
  } else {
    printf("Appending with O_APPEND\n");
    flags = O_WRONLY | O_CREAT | O_TRUNC | O_APPEND;
  }

  // Open file
  fd = open(argv[1], flags, perms);

  if (fd == -1) {
    printf("Error: Failed to open file\n");
    exit(EXIT_FAILURE);
  }

  // Write each byte at a time
  for (i = 0; i < bytes; i++) {
    if (lseek_on == 1)
      lseek(fd, 0, SEEK_END);

    if (write(fd, "1", 1) == -1) {
      printf("Error: Failed to write to file\n");
      exit(EXIT_FAILURE);
    }
  }

  if (close(fd) == -1) {
    printf("Error: Failed to close file\n");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
