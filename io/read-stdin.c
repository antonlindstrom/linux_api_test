#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_READ 20

int main() {
  char buffer[MAX_READ];

  if (read(STDIN_FILENO, buffer, MAX_READ) == -1) {
    printf("Error: read\n");
    exit(EXIT_FAILURE);
  }

  printf("The input data was: %s\n", buffer);

  return 0;
}
