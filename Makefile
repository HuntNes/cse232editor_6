CC = gcc
CFLAGS = -Wall

all: cse232editor

cse232editor: main.c edit.c insert.c
	$(CC) $(CFLAGS) -o cse232editor main.c edit.c insert.c

clean:
	rm -f cse232editor 