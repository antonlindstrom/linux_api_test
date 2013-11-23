#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>

#define STR_SIZE 100

int main(int argc, char *argv[]) {
  int fd, x;
  struct iovec iov[3];
  struct stat myStruct;
  char str[STR_SIZE];
  ssize_t numRead, totRequired;

  if (argc != 2 || strcmp(argv[1], "--help") == 0) {
    printf("Usage: %s file\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  fd = open(argv[1], O_RDONLY);

  if (fd == -1) {
    printf("Error: failed to open file %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  totRequired = 0;

  iov[0].iov_base = &myStruct;
  iov[0].iov_len = sizeof(struct stat);
  totRequired += iov[0].iov_len;

  iov[1].iov_base = &x;
  iov[1].iov_len = sizeof(x);
  totRequired += iov[1].iov_len;

  iov[2].iov_base = str;
  iov[2].iov_len = STR_SIZE;
  totRequired += iov[2].iov_len;

  numRead = readv(fd, iov, 3);

  if (numRead == -1) {
    printf("Error: failed to readv\n");
    exit(EXIT_FAILURE);
  }

  if (numRead < totRequired)
    printf("Read fewer bytes han requested\n");

  printf("Total bytes requested: %ld; bytes read: %ld\n", (long) totRequired, (long) numRead);

  exit(EXIT_SUCCESS);
}
