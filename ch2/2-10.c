/**
 * who2.c Read /etc/utmp, display the list of /etc/utmp.
 * Here is the difference of who1.c and who2.c.
 * who2.c doesn't display empty record.
 * who2.c display pretty time format.
 */
#include <stdio.h>
#include <unistd.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

/* # define SHOWHOST */

void showtime(long);
void show_info(struct utmp *);

int main(int ac, char *av[]) {
  if (! (ac==1 || ac ==3)){
    fprintf(stderr, "usage: who or who am i\n");
    exit(1);
  }

  if (ac == 3) {
    int isWrongArguments = (strcmp(av[1], "am") != 0) || (strcmp(av[2], "i"));
    if (isWrongArguments) {
      fprintf(stderr, "usage: %s who am i\n", *av);
      exit(1);
    }
  }

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
  printf(" ");
  printf("%-8.8s", utbufp->ut_line);
  printf(" ");
  showtime(utbufp->ut_time);
#ifdef SHOWHOST
  if(utbufp->ut_host[0] != '/0')
    printf(" (%s)", utbufp->ut_host);
#endif
  printf("\n");
}

void showtime(long timeval) {
  char *cp;
  cp = ctime(&timeval);
  printf("%12.12s", cp + 4);
}
