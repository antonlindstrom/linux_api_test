#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd;
  char buffer[] = "Message on stdout (on fd 2)\n";

  // Duplicate stdout to stderr
  fd = dup2(STDOUT_FILENO, STDERR_FILENO);

  if (fd == -1) {
    printf("Error: Could not dup() stdout (fd 1)\n");
    exit(EXIT_FAILURE);
  }

  if (write(STDERR_FILENO, buffer, sizeof(buffer)) == -1) {
    printf("Could not write to buffer to STDERR_FILENO\n");
    exit(EXIT_FAILURE);
  }

}
