#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd;
  if ((fd = open("sample.txt", O_RDWR)) == -1) {
    perror("Cannot open file.");
    exit(1);
  }

  int oldpos;
  if ((oldpos = lseek(fd, 20000, SEEK_END)) == -1) {
    perror("Error in lseek()");
    exit(1);
  }

  char buf[] = "This is sample message.";
  if ((write(fd, buf, sizeof(buf))) == -1) {
    perror("Cannot write");
    exit(1);
  }

  close(fd);
  return 0;
}
