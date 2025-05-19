CC = gcc
CFLAGS = -Wall

all: cse232editor

cse232editor: main.c edit.c insert.c delete.c save.c display.c undo_redo.c
	$(CC) $(CFLAGS) -o cse232editor main.c edit.c insert.c delete.c save.c display.c undo_redo.c -lncurses

libinterface.a: interface.c
	$(CC) $(CFLAGS) -c interface.c -o interface.o
	ar rcs libinterface.a interface.o

test: libinterface.a test_interface.c
	$(CC) $(CFLAGS) -o test_interface test_interface.c -L. -linterface -lncurses
	./test_interface

clean:
	rm -f cse232editor test_interface *.o *.a



