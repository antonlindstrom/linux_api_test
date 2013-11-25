#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_READ 20

int main() {
  char buffer[MAX_READ];
  ssize_t numRead;

  numRead = read(STDIN_FILENO, buffer, MAX_READ);
  if (numRead == -1) {
    printf("Error: read\n");
    exit(EXIT_FAILURE);
  }

  buffer[numRead] = '\0';
  printf("The input data was: %s\n", buffer);

  exit(EXIT_SUCCESS);
}
