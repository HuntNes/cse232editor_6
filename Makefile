CC = gcc
CFLAGS = -Wall

all: cse232editor

cse232editor: main.c edit.c insert.c delete.c display.c save.c
	$(CC) $(CFLAGS) -o cse232editor main.c edit.c insert.c delete.c save.c display.c -lcurses
clean:
	rm -f cse232editor
