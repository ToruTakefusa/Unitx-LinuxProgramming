#ifndef UTMPLIB_H
#define UTMPLIB_H

#include <utmp.h>

int utmp_open(char *);
struct utmp *utmp_next();
int utmp_close();

#endif
