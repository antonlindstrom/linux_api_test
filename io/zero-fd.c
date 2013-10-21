#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
  int fd;

  if (argc != 2) {
    printf("%s filename\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if (close(STDIN_FILENO) == -1) {
    printf("Error close\n");
    exit(EXIT_FAILURE);
  }

  fd = open(argv[1], O_RDONLY);

  if (fd == -1) {
    printf("Error open\n");
    exit(EXIT_FAILURE);
  }

  printf("FD used by file: %d.\n", fd);

  if (close(fd) == -1) {
    printf("Error close\n");
    exit(EXIT_FAILURE);
  }

  return 0;
}
