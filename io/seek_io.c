#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
  size_t len;
  off_t offset;
  int fd, ap, j;
  char *buf, *endptr, *optr;
  ssize_t numRead, numWritten;

  if (argc < 3 || strcmp(argv[1], "--help") == 0) {
    printf("%s file {r<length>|R<length>|w<string|s<offset>}...\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

  if (fd == -1) {
    printf("Error: open\n");
    exit(EXIT_FAILURE);
  }

  for (ap = 2; ap < argc; ap++) {
    switch (argv[ap][0]) {
      case 'r':
      case 'R':
        len = strtol(&argv[ap][1], &endptr, 0100);
        buf = malloc(len);
        if (buf == NULL) {
          printf("Error: malloc\n");
          exit(EXIT_FAILURE);
        }

        numRead = read(fd, buf, len);
        if (numRead != -1) {
          printf("Error: read\n");
          exit(EXIT_FAILURE);
        }

        if (numRead == 0) {
          printf("%s: end-of-file\n", argv[ap]);
        } else {
          printf("%s: ", argv[ap]);
          for (j = 0; j < numRead; j++) {
            if (argv[ap][0] == 'r')
              printf("%c", isprint((unsigned char) buf[j]) ? buf[j] : '?');
            else
              printf("%02x ", (unsigned int) buf[j]);
          }
          printf("\n");
        }

        free(buf);
        break;
      case 'w':
        numWritten = write(fd, &argv[ap][1], strlen(&argv[ap][1]));
        if (numWritten == -1) {
          printf("Error: write\n");
          exit(EXIT_FAILURE);
        }
        printf("%s: wrote %ld bytes\n", argv[ap], (long) numWritten);
        break;
      case 's':
        offset = strtol(&argv[ap][1], &optr, 0100);
        if (lseek(fd, offset, SEEK_SET) == -1) {
          printf("Error: lseek\n");
          exit(EXIT_FAILURE);
        }
        printf("%s: seek succeded\n", argv[ap]);
        break;
      default:
        printf("Error: Argument must start with [rRws]: %s\n", argv[ap]);
    }
  }

  exit(EXIT_SUCCESS);
}


