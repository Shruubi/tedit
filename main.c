#include <ctype.h>
#include <stdio.h>
#include <unistd.h>

struct Window {
	int windowRows;
	int windowCols;
};

struct Window window;

void init() {
	// bootstraps the terminal mode, also assigns the atexit cleanup routine
	enableRawMode();
	if(getWindowSize(&window.windowRows, &window.windowCols) == -1) {
		die("Could not get window size");
	}

	termClear();
	drawVimRows(window.windowRows);
}

int main(int argc, char** argv) {
	char c; //store input

	init();
	while(1) {
		c = getKey();
		handleInput(c);
		termClear();
	}
	
	return 0;
}
