/**
 * 2-10-1.c Read /etc/utmp, display the list of /etc/utmp.
 */
#include <stdio.h>
#include <unistd.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>

void show_info(struct utmp *);

int main() {
  struct utmp utbuf;
  int utmpfd;

  if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
	perror(UTMP_FILE);
	exit(1);
  }

  while(read(utmpfd, &utbuf, sizeof(utbuf)) == sizeof(utbuf))
	show_info(&utbuf);
  close(utmpfd);
  return 0;
}

void show_info(struct utmp *utbufp) {
  if (utbufp->ut_type != USER_PROCESS)
	return;
  printf("%-8.8s", utbufp->ut_name);
  printf("\n");
}
