#include <string.h> // strncpy
#include <stdio.h> // printf
#include <errno.h> // perror
#include <fcntl.h> // open
#include <unistd.h> // read, close, STDIN_FILENO, lssek
#include <sys/types.h> // lseek

#define BUFFERSIZE 1024

int main(int ac, char *av[]) {
  int fd;
  if (ac == 1) {
    fd = STDIN_FILENO;
  } else {
    if ((fd = open(av[1], O_RDONLY)) == -1) {
      perror("Cannot open file");
      return -1;
    }
  }

  char buf[BUFFERSIZE];
  int line = 0;
  char content[BUFFERSIZE];

  lseek(fd, -BUFFERSIZE, SEEK_CUR);
  while(read(fd, buf, BUFFERSIZE) > 0) {
    int byte = 0;
    for(int i = BUFFERSIZE - 1; i > -1; --i) {
      if (buf[i] == '\n') ++line;
      ++byte;
      if (line == 11) { // need 11 lines. first line is just \n
        --byte; // do not first \n
        for (int i = 0; i < byte; ++i) {
          content[i] = buf[BUFFERSIZE - byte + i];
        }
        content[byte] = '\0';
        printf("%s", content);
        goto LABEL;
      }
    }
    printf("%s", buf);
    memset(buf, '\0', BUFFERSIZE);
    lseek(fd, -BUFFERSIZE, SEEK_CUR);
  }

 LABEL:

  if (close(fd) == -1) {
    perror("Cannot close file");
    return -1;
  }
}
