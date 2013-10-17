#include <stdio.h>
#include <sys/types.h>

int main(void) {
  pid_t mypid, parentpid;

  mypid = getpid();
  parentpid = getppid();

  printf("PID: %ld\n", (long) mypid);
  printf("PPID: %ld\n", (long) parentpid);

   return 0;
}
