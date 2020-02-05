#include <string.h> //strncpy
#include <stdio.h> //printf
#include <errno.h> //perror
#include <fcntl.h> //open
#include <unistd.h> // read, close, STDIN_FILENO

#define BUFFERSIZE 1024

int main(int ac, char *av[]) {
  int fd;
  if (ac == 2) {
    if ((fd = open(av[1], O_RDONLY)) == -1) {
      perror("Cannot open file");
      return -1;
    }
  } else {
    fd = STDIN_FILENO;
  }

  char buf[BUFFERSIZE];
  int line = 0;
  char content[BUFFERSIZE];

  while(read(fd, buf, BUFFERSIZE) > 0) {
    int byte = 0;
    for (int i = 0; i < BUFFERSIZE; ++i) {
      if (buf[i] == '\n') ++line;
      ++byte;
      if (line == 10) {
        strncpy(content, buf, byte);
        content[byte] = '\0';
        goto LABEL;
      }
    }
    printf("%s", buf);
    memset(buf, '\0', BUFFERSIZE);
  }

 LABEL:
  printf("%s", content);

  if (close(fd) == -1) {
    perror("Cannot close file");
  }
}
