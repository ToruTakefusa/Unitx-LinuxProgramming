#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
  int ret, fd;
  char buf[1024];

  system("ls -l / >| ls.output");

  if ((fd = open("ls.output", O_RDONLY)) < 0) {
    perror("open() error");
  }
  else {
    while((ret = read(fd, buf, sizeof(buf) -1)) > 0) {
      buf[ret] = 0x00;
      printf("block read: \n<%s?\n", buf);
    }
    close(fd);
  }
  unlink("ls.output");
}
