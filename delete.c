#include <stdio.h>
#include <string.h>
#include "cse232editor.h"

extern struct node textbuffer[MAX_LINES];
extern int inuse_head;
extern int free_head;
extern int undo_top, redo_top;

void delete(int line) {
    if (inuse_head == -1) {
        printf("Error: Buffer is empty.\n");
        return;
    }

    int idx = inuse_head;
    int curr_line = 0;
    while (idx != -1 && curr_line < line) {
        idx = textbuffer[idx].next;
        curr_line++;
    }
    if (idx == -1) {
        printf("Error: Line not found.\n");
        return;
    }


    Operation op;
    op.type = OP_DELETE;
    op.line = line;
    strncpy(op.statement, textbuffer[idx].statement, MAX_LEN);
    push_undo(op);
    redo_top = -1;

    if (textbuffer[idx].prev != -1)
        textbuffer[textbuffer[idx].prev].next = textbuffer[idx].next;
    else
        inuse_head = textbuffer[idx].next;

    if (textbuffer[idx].next != -1)
        textbuffer[textbuffer[idx].next].prev = textbuffer[idx].prev;

  
    textbuffer[idx].next = free_head;
    free_head = idx;

    printf("Line %d deleted.\n", line);
}
