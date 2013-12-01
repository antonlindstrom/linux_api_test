#define _LARGEFILE64_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char *argv[]) {
  int fd;
  off64_t off;

  if (argc != 3 || strcmp(argv[1], "--help") == 0) {
    printf("Usage: %s pathname offset\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  fd = open64(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

  if (fd == -1) {
    printf("Failed to call open64 on file %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  off = atoll(argv[2]);

  if (lseek64(fd, off, SEEK_SET) == -1) {
    printf("Failed to call lseek64 on fd %d\n", fd);
    exit(EXIT_FAILURE);
  }

  if (write(fd, "test", 4) == -1) {
    printf("Failed to call write on fd %d\n", fd);
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
