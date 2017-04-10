#define TEDIT_VERSION "0.1.0"
#define CTRL_KEY(k) ((k) & 0x1f)

struct Window {
	int windowRows;
	int windowCols;
};

struct Buffer {
	char* buff;
	int len;
	int cursorX;
	int cursorY;
};

// main.c
void init();

// util.c
void die(const char *s);

// term.c
void disableRawMode();
void enableRawMode();
int getWindowSize(int *rows, int *cols);

// input.c
char getKey();
void handleInput(char input);

// buffer.c
void bufferAppend(struct Buffer* buffer, const char* str, int len);
void bufferFree(struct Buffer* buffer);
struct Buffer bufferCreate();

// screen.c
void termResetCursor();
void termClear();
void editorDrawRows(struct Buffer* buffer);
void refreshScreen();
