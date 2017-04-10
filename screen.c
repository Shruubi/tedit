#include "tedit.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void termResetCursor() {
	write(STDOUT_FILENO, "\x1b[H", 3);
}

void termClear() {
 	write(STDOUT_FILENO, "\x1b[2J", 4);
 	termResetCursor();
}

void editorDrawRows(struct Buffer* buffer) {
	int y;

	for (y = 0; y < window.windowRows; y++) {
		bufferAppend(buffer, "~", 1);
		bufferAppend(buffer, "\x1b[K", 3);
		
		if (y < window.windowRows - 1) {
		  bufferAppend(buffer, "\r\n", 2);
		}
	}
}

void refreshScreen() {
	struct Buffer buffer = bufferCreate();

	bufferAppend(&buffer, "\x1b[?25l", 6);
	bufferAppend(&buffer, "\x1b[H", 3);
	
	editorDrawRows(&buffer);
	
	bufferAppend(&buffer, "\x1b[H", 3);
	bufferAppend(&buffer, "\x1b[?25h", 6);
	
	write(STDOUT_FILENO, buffer.b, buffer.len);
	
	bufferFree(&buffer);
}