#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define SHOWHOST

void show_info(struct utmp *utbufp);

/*
 * who1. c - first verson of who program.
 * Open utmp file, show the contents.
 */

int main(int ac, char *av[]) {
  struct utmp current_record;
  int utmpfd;
  int reclen = sizeof(current_record);

  if (ac ==2) {
    if ((utmpfd = open(av[1], O_RDONLY)) == -1 ) {
      perror(av[1]);
      exit(1);
    }
  } else {
    if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1 ) {
      perror(UTMP_FILE);
      exit(1);
    }
  }

  while(read(utmpfd, &current_record, reclen) == reclen)
    show_info(&current_record);
  close(utmpfd);
  return 0;
}

/*
 * show info()
 * Show the contents of utmp struct that human can read.
 * DON'T HARD CODE SIZE INFORMATION
 */
void show_info(struct utmp *utbufp) {
  printf("%-8.8s", utbufp->ut_name);
  printf(" ");
  printf("%-8.8s", utbufp->ut_line);
  printf(" ");
  printf("%10d", utbufp->ut_time);
  printf(" ");
  #ifdef SHOWHOST
  printf("(%s)", utbufp->ut_host);
  #endif
  printf(" ");
  printf("%d", utbufp->ut_type);
  printf(" ");
  printf("%s", utbufp-> ut_id);
  printf(" ");
  printf("%d", utbufp->ut_pid);
  printf(" ");
  printf("%d", utbufp->ut_exit.e_termination);
  printf(" ");
  printf("%d", utbufp->ut_exit.e_exit);
  printf("\n");
}
