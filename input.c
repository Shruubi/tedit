#include "tedit.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern struct Buffer buffer;
extern struct Window window;

int getKey() {
	int nread;
	char c;
	
	while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
		if (nread == -1 && errno != EAGAIN) die("read");
	}
	
	if (c == '\x1b') {
		char seq[3];
		if (read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
		if (read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';
		if (seq[0] == '[') {
			switch (seq[1]) {
				case 'A': return ARROW_UP;
				case 'B': return ARROW_DOWN;
				case 'C': return ARROW_RIGHT;
				case 'D': return ARROW_LEFT;
			}
		}
		
		return '\x1b';
	} else {
		return c;
	}
}

void handleInput(int input) {
	switch(input) {
		case CTRL_KEY('q'):
			exit(0);
			break;
		case ARROW_LEFT:
			if(buffer.cursorX != 0) {
				buffer.cursorX--;
			}
			break;
		case ARROW_RIGHT:
			if(buffer.cursorX != window.windowCols - 1) {
				buffer.cursorX++;
			}
			break;
		case ARROW_UP:
			if(buffer.cursorY != 0) {
				buffer.cursorY--;
			}
			break;
		case ARROW_DOWN:
			if(buffer.cursorY != window.windowRows - 1) {
				buffer.cursorY++;
			}
			break;
	}
}