#include <string.h> // strtok()
#include <stdio.h>
#include <fcntl.h> //open
#include <unistd.h> // read, close
#include <stdlib.h> //exit

#define BUFFERSIZE 4096

int byteSum = 0;
int newlineSum = 0;
int wordSum = 0;

int countWord(char* file) {
  int fd;
  if ((fd = open(file, O_RDONLY)) == -1) {
    perror(file);
    exit(-1);
  }

  char buf[BUFFERSIZE];
  int readByte = 0;
  int byte = 0;
  int newline = 0;
  int word = 0;

  while((readByte = read(fd, buf, BUFFERSIZE)) > 0) {
    byte += readByte;
    for(int i = 0; i < readByte; ++i) {
      if (buf[i] == '\n') ++newline;
      if ((buf[i] == '\n') || (buf[i] == ' ' || buf[i] == '\t')) {
        ++word;
      }
    }
  }
  close(fd);

  printf("%d %d %d %s\n", newline, word, byte, file);
  byteSum += byte;
  newlineSum += newline;
  wordSum += word;
}

int main(int ac, char *av[]) {
  if (ac == 1) {
    fprintf(stderr, "usage: %s file1, file2, ...\n", *av);
    exit(1);
  }

  for (int i = 1; i < ac; ++i) {
    countWord(av[i]);
  }
  if (ac != 2)
    printf("%d %d %d total\n", newlineSum, wordSum, byteSum);
}
