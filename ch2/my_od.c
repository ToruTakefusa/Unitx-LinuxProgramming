#include <stdio.h> // printf
#include <errno.h> // perror
#include <fcntl.h> // open
#include <unistd.h> // read, close

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

  short int buffer[BUFFERSIZE] = {0};
  int size = read(fd, buffer, BUFFERSIZE);
  if (size % 2 == 0) {
    size = size / 2;
  } else {
    size = size / 2 + 1;
  }

  for (int i = 0; i < size; ++i) {
    if ((i + 1) % 8 == 0) {
      printf("%6.6o\n", buffer[i]);
    } else {
      printf("%6.6o ", buffer[i]);
    }
  }
  close(fd);
}
