#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
  int fd;
  off_t offset;

  // Open with O_APPEND
  fd = open("temp.exercise", O_WRONLY | O_APPEND | O_CREAT, S_IWUSR | S_IRUSR);

  if (fd == -1) {
    printf("Error: Could not open file.\n");
    exit(EXIT_FAILURE);
  }

  // Seek to the beginning
  offset = lseek(fd, 0, SEEK_SET);

  if (offset == -1) {
    printf("Error: Could not seek to beginning of file.\n");
    exit(EXIT_FAILURE);
  }

  // Write some data
  if (write(fd, "They call me the seeker\n", 24) == -1) {
    printf("Error: Failed to write to file.\n");
    exit(EXIT_FAILURE);
  }

  // Close
  if (close(fd) == -1) {
    printf("Error: Failed to close file.\n");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
