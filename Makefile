default: main.c util.o term.o input.o
	$(CC) util.o term.o input.o main.c -o tedit -Wall -Wextra -pedantic -std=c99

util: util.c
	$(CC) util.c -o util.o -Wall -Wextra -pedantic -std=c99

term: term.c
	$(CC) term.c -o term.o -Wall -Wextra -pedantic -std=c99

input: input.c
	$(CC) input.c -o input.o -Wall -Wextra -pedantic -std=c99