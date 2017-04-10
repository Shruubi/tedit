#include "tedit.h"

#include <stdlib.h>
#include <string.h>

void bufferAppend(struct Buffer* buffer, const char* str, int len) {
	// allocate a larger block of memory
	char *new = realloc(buffer->buff, buffer->len + len);
	if (new == NULL) {
		// if alloc fails, die here
		die("Failed to allocate buffer");
	}
	
	// copy new string onto end of buffer
	memcpy(&new[buffer->len], str, len);
	
	// update buffer
	buffer->buff = new;
	buffer->len += len;
}

void bufferFree(struct Buffer* buffer) {
	free(buffer->buff);
}

struct Buffer bufferCreate() {
	struct Buffer b;
	b.buff = NULL;
	b.len = 0;
	b.cursorX = 0;
	b.cursorY = 0;
	return b;
}