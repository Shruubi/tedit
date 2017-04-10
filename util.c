#include "tedit.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void die(const char *s) {
	perror(s);
	exit(1);
}