
CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-lreadline -lncurses
BIN=shell

all: $(BIN)

shell: filesystem.o shell.o
	$(CC) -o shell shell.o filesystem.o $(LDFLAGS) 

shell.o: shell.c
	$(CC) $(CFLAGS) -c -o shell.o shell.c

filesystem.o: filesystem.h filesystem.c
	$(CC) $(CFLAGS) -c -o filesystem.o filesystem.c

clean:
	rm -f *.o $(BIN) *~
