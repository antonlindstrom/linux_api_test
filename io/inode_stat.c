#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char *argv[]) {
  struct stat node;

  if (argc != 2) {
    printf("Usage: %s FILE\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if (stat(argv[1], &node) == -1) {
    printf("Error: Could not stat %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  printf("inode: %ld\n", (long) node.st_ino);
  printf("mode: %lo (octal)\n", (unsigned long) node.st_mode);
  printf("link count: %ld\n", (long) node.st_nlink);
  printf("owner: %ld\n", (long) node.st_uid);
  printf("group: %ld\n", (long) node.st_gid);
  printf("dev: %ld\n", (long) node.st_dev);
  printf("device type: %ld\n", (long) node.st_rdev);
  printf("size: %ld\n", (long) node.st_size);
  printf("block size: %ld\n", (long) node.st_blksize);
  printf("# 512B blocks: %ld\n", (long) node.st_blocks);
  printf("atime: %ld\n", (long) node.st_atime);
  printf("mtime: %ld\n", (long) node.st_mtime);
  printf("ctime: %ld\n", (long) node.st_ctime);

  exit(EXIT_SUCCESS);
}
