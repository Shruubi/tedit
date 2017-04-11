#include "tedit.h"

#include <ctype.h>
#include <stdio.h>
#include <unistd.h>

struct Window window;
struct Buffer buffer;

void init() {
	// bootstraps the terminal mode, also assigns the atexit cleanup routine
	enableRawMode();

	// init window
	if(getWindowSize(&window.windowRows, &window.windowCols) == -1) {
		die("Could not get window size");
	}

	// init buffer
	buffer = bufferCreate();

	// clear window for drawing
	refreshScreen();
}

//int main(int argc, char** argv) {
int main(void) {
	int c; //store input

	init(); //bootstrap
	while(1) {
		//main loop
		c = getKey();
		handleInput(c);
		refreshScreen();
	}
	
	return 0;
}
