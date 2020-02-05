#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 10000
struct utmp current_record[SIZE];
struct last {
  short ut_type;
  char ut_name[32];
  char ut_line[32];
  char ut_host[256];
  long start_time;
  long last_time;
};
struct last last_record[SIZE];

void show_info(struct last *utbufp);
void showtime(long timeval);

/*
 * who1. c - first verson of who program.
 * Open utmp file, show the contents.
 */

int main(int ac, char *av[]) {
  int utmpfd;
  int reclen = sizeof(current_record);

  char* WTMP = "/var/log/wtmp";
  if ((utmpfd = open(WTMP, O_RDONLY)) == -1 ) {
    perror(WTMP);
    exit(1);
  }

  int count = 1;
  while(lseek(utmpfd, -(sizeof(struct utmp) * count), SEEK_END) != -1) {
    read(utmpfd, &current_record[count - 1], reclen);
    ++count;
  }

  long tmp = 0;
  for (int i = 0; i < count - 1; ++i) {
    short tmp_type = current_record[i].ut_type;
    //if ((tmp_type != USER_PROCESS) && (tmp_type != BOOT_TIME)) continue;
    if (strcmp(current_record[i].ut_name, "shutdown") == 0) {
      tmp = current_record[i].ut_time;
      continue;
    }
    last_record[i].ut_type = current_record[i].ut_type;
    strcpy(last_record[i].ut_name, current_record[i].ut_name);
    strcpy(last_record[i].ut_line, current_record[i].ut_line);
    strcpy(last_record[i].ut_host, current_record[i].ut_host);
    last_record[i].start_time = current_record[i].ut_time;
    last_record[i].last_time = tmp;
  }

  for (int i = 0; i < count - 1; i++) {
    show_info(&last_record[i]);
  }
  close(utmpfd);
  return 0;
}

/*
 * show info()
 * Show the contents of utmp struct that human can read.
 * DON'T HARD CODE SIZE INFORMATION
 */
void show_info(struct last *utbufp) {
  short tmp_type = utbufp->ut_type;
  if ((tmp_type != USER_PROCESS) && (tmp_type != BOOT_TIME )) return;
  printf("%-8.8s", utbufp->ut_name);
  printf(" ");
  printf("%-12.12s", utbufp->ut_line);
  printf(" ");
  printf("%-16.16s", utbufp->ut_host);
  printf(" ");
  showtime(utbufp->start_time);
  printf(" ");
  showtime(utbufp->last_time);
  printf("\n");
}

void showtime(long timeval) {
  printf("%16.16s", ctime(&timeval));
}
