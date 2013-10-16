#include <stdio.h>
#include <stdlib.h>

#ifdef __GLIBC__
  #include <unistd.h>
  #include <gnu/libc-version.h>
#endif

const char *gnu_get_libc_version(void);

int main() {
  char *glibc_version;
  size_t len;

  len = confstr(_CS_GNU_LIBC_VERSION, NULL, (size_t)0);
  glibc_version = malloc(len);

  confstr(_CS_GNU_LIBC_VERSION, glibc_version, len);

  printf("GNU C Library version, gnu_get_libc_version(): %s\n", gnu_get_libc_version());
  printf("GNU C Library version, _CS_GNU_LIBC_VERSION(): %s\n", glibc_version);

  free(glibc_version);

  return 0;
}
