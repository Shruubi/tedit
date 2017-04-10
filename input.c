#include "tedit.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern struct Buffer buffer;

char getKey() {
	int nread;
	char c;
	
	while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
		if (nread == -1 && errno != EAGAIN) die("read");
	}
	
	return c;
}

void handleInput(char input) {
	switch(input) {
		case CTRL_KEY('q'):
			exit(0);
			break;
		case 'a':
			buffer.cursorX--;
			break;
		case 'd':
			buffer.cursorX++;
			break;
		case 'w':
			buffer.cursorY--;
			break;
		case 's':
			buffer.cursorY++;
			break;
	}
}