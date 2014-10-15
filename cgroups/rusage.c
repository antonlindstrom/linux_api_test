#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char *argv[])
{
  struct rusage usage;

  if (getrusage(RUSAGE_SELF, &usage) != 0 ) {
    printf("Could not get resource usage\n");
    exit(EXIT_FAILURE);
  }

  printf("Volontary context switches: %ld\n", usage.ru_nvcsw);
  printf("Involontary context switches: %ld\n", usage.ru_nivcsw);

  exit(EXIT_SUCCESS);
}
