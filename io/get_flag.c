#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[]) {
  int fd, flags, accessMode;

  fd = open(argv[1], O_RDWR | O_CREAT | O_SYNC, S_IWUSR | S_IRUSR);

  if (fd == -1) {
    printf("Error, couldn't open %s.\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  flags = fcntl(fd, F_GETFL);

  if (flags == -1) {
    printf("Error, couldn't F_GETFL properly.\n");
    exit(EXIT_FAILURE);
  }

  if (flags & O_SYNC)
    printf("Writes are synchronized\n");
  else
    printf("Writes aren't synchronized\n");

  accessMode = flags & O_ACCMODE;

  if (accessMode == O_WRONLY || accessMode == O_RDWR)
    printf("File is writable\n");

  flags |= O_APPEND;

  if (fcntl(fd, F_SETFL, flags) == -1) {
    printf("Error, couldn't set O_APPEND with fcntl()\n");
    exit(EXIT_FAILURE);
  }

  if (flags & O_APPEND)
    printf("Writes are O_APPEND\n");

  close(fd);

  exit(EXIT_SUCCESS);
}
