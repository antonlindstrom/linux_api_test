#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
  int inputFd, outputFd, openFlags, length, numRead;
  mode_t filePerms;
  char *buf;

  if (argc != 3 || strcmp(argv[1], "--help") == 0) {
    printf("%s old-file new-file\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // Read source file
  inputFd = open(argv[1], O_RDONLY);

  if (inputFd == -1) {
    printf("Error opening file %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  // Open FD for target
  openFlags = O_CREAT | O_WRONLY | O_TRUNC;
  filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

  outputFd = open(argv[2], openFlags, filePerms);

  if (outputFd == -1) {
    printf("opening file %s\n", argv[2]);
    exit(EXIT_FAILURE);
  }

  // Seek to end of file to get length
  length = lseek(inputFd, 0, SEEK_END)+1;

  if (length == -1) {
    printf("Error: Could not seek to SEEK_END\n");
    exit(EXIT_FAILURE);
  }

  // Allocate buffer
  buf = malloc(length);

  // reset file pointer for read()
  if (lseek(inputFd, 0, SEEK_SET) == -1) {
    printf("Error: Could not SET_SEEK seek to 0\n");
    exit(EXIT_FAILURE);
  }

  // While reading, write to new file
  while((numRead = read(inputFd, buf, length)) > 0)
    if (write(outputFd, buf, numRead) != numRead) {
      printf("couldn't write whole buffer\n");
      exit(EXIT_FAILURE);
    }

  if (numRead == -1) {
    printf("Error read\n");
    exit(EXIT_FAILURE);
  }

  if (close(inputFd) == -1) {
    printf("Error close input\n");
    exit(EXIT_FAILURE);
  }

  if (close(outputFd) == -1) {
    printf("Error close output\n");
    exit(EXIT_FAILURE);
  }

  free(buf);

  exit(EXIT_SUCCESS);
}
