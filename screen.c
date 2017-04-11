#include "tedit.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

extern struct Window window;
extern struct Buffer buffer;

void termResetCursor() {
	write(STDOUT_FILENO, "\x1b[H", 3);
}

void termClear() {
	write(STDOUT_FILENO, "\x1b[2J", 4);
	termResetCursor();
}

void editorDrawRows(struct Buffer* buffer) {
	for (int y = 0; y < window.windowRows; y++) {
		if (y == window.windowRows / 3) {
			char welcome[80];
			int welcomelen = snprintf(welcome, sizeof(welcome),
				"Terminal Editor (tedit) -- version %s", TEDIT_VERSION);
			
			if (welcomelen > window.windowCols) welcomelen = window.windowCols;
			
			int padding = (window.windowCols - welcomelen) / 2;
			if (padding) {
				bufferAppend(buffer, "~", 1);
				padding--;
			}

			while (padding--) { bufferAppend(buffer, " ", 1); }
			bufferAppend(buffer, welcome, welcomelen);
		} else {
			bufferAppend(buffer, "~", 1);
		}

		bufferAppend(buffer, "\x1b[K", 3);
		if (y < window.windowRows - 1) { bufferAppend(buffer, "\r\n", 2); }
	}
}

void refreshScreen() {
	bufferAppend(&buffer, "\x1b[?25l", 6);
	bufferAppend(&buffer, "\x1b[H", 3);
	
	editorDrawRows(&buffer);
	
	char buf[32];
	snprintf(buf, sizeof(buf), "\x1b[%d;%dH", buffer.cursorY + 1, buffer.cursorX + 1);
	bufferAppend(&buffer, buf, strlen(buf));
	
	bufferAppend(&buffer, "\x1b[?25h", 6);
	
	write(STDOUT_FILENO, buffer.buff, buffer.len);
}