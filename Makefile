CC = gcc
CFLAGS = -Wall

all: cse232editor

cse232editor: main.c edit.c insert.c delete.c save.c display.c undo_redo.c
	$(CC) $(CFLAGS) -o cse232editor main.c edit.c insert.c delete.c save.c display.c undo_redo.c -lncurses

clean:
	rm -f cse232editor

