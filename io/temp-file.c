#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
  int fd;
  char template[] = "/tmp/somestringXXXXXX";
  struct stat fileStat;

  fd = mkstemp(template);
  if (fd == -1) {
    printf("Error, could not create temporary file.\n");
    exit(EXIT_FAILURE);
  }

  printf("Generated filename was: %s\n", template);

  // Test if file exists
  if (stat(template, &fileStat) == -1) {
    printf("Failed to stat %s, file not available.\n", template);
  } else {
    printf("All good, %s exists.\n", template);
  }

  unlink(template);

  if (close(fd) == -1) {
    printf("Error, could not close temporary file.\n");
    exit(EXIT_FAILURE);
  }
  printf("Temporary file is now deleted.\n");
}
