#include <stdio.h>
#include <fcntl.h> //open
#include <unistd.h> // read, close
#include <errno.h> //perror
#include <string.h> //memset

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

  char buffer[BUFFERSIZE];
  while(read(fd, buffer, BUFFERSIZE) > 0) {
    printf("%s", buffer);
    memset(buffer, '\0', BUFFERSIZE);
  }

  if (close(fd) == -1) {
    perror("Cannot close file");
    return -1;
  }
}
