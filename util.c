#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void die(const char *s) {
	perror(s);
	exit(1);
}

void termResetCursor() {
	write(STDOUT_FILENO, "\x1b[H", 3);
}

void termClear() {
 	write(STDOUT_FILENO, "\x1b[2J", 4);
 	termResetCursor();
}

void drawVimRows(int numRows) {
	int y;
	for (y = 0; y < numRows; y++) {
		write(STDOUT_FILENO, "~\r\n", 3);
	}
}