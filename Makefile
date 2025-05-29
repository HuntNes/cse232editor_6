CC = gcc
CFLAGS = -Wall -g

SRCS = main.c edit.c insert.c delete.c save.c display.c undo_redo.c interface.c
OBJS = $(SRCS:.c=.o)

all: cse232editor

cse232editor: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lncurses

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f cse232editor $(OBJS)



