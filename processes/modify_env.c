#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

extern char **environ;

int main(int argc, char *argv[])
{
  int j;
  char **ep;

  clearenv();

  for (j = 1; j < argc; j++) {
    if (putenv(argv[j]) != 0) {
      printf("Error: putenv, %s\n", argv[j]);
      exit(EXIT_FAILURE);
    }
  }

  if (setenv("GREET", "Hello World", 0) == -1) {
    printf("Error: setenv\n");
    exit(EXIT_FAILURE);
  }

  unsetenv("BYE");

  for (ep = environ; *ep != NULL; ep++)
    puts(*ep);

  exit(EXIT_SUCCESS);
}
