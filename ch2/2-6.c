#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
  int fd1, fd2, fd3;
  char contents[21];

  if (((fd1 = open("foo1.txt", O_RDONLY)) == -1)
      || ((fd2 = open("foo1.txt", O_WRONLY)) == -1)
      || ((fd3 = open("foo1.txt", O_RDONLY)) == -1)) {
      perror("Cannot open file.");
      exit(1);
  }

  int rs;
  if ((rs = read(fd1, contents, 20)) != 20) {
    perror("Cannot read 20 bytes.");
    exit(1);
    }

  printf("%s", contents);
  char buf[] = "testing 1 2 3...";
  if (write(fd2, buf, sizeof(buf)) != sizeof(buf)) {
    perror("Cannot write file.");
    exit(1);
  }

  if (read(fd3, contents, 20) != 20) {
    perror("Cannot read 20 bytes.");
    exit(1);
  }
  printf("%s", contents);

  close(fd1);
  close(fd2);
  close(fd3);
  return 0;
}
