#include <stdio.h>
#include <string.h>
#include "cse232editor.h"

extern struct node textbuffer[MAX_LINES];
extern int inuse_head;
extern int free_head;
extern int undo_top, redo_top;

void insert_line(int line, const char *stat) {
    if (stat == NULL) {
        printf("Error: Invalid text input.\n");
        return;
    }

    if (free_head == -1) {
        printf("Error: No space to insert a new line.\n");
        return;
    }

    int new_idx = free_head;
    free_head = textbuffer[new_idx].next;

    strncpy(textbuffer[new_idx].statement, stat, MAX_LEN - 1);
    textbuffer[new_idx].statement[MAX_LEN - 1] = '\0';

    // Undo kaydı ekle
    Operation op;
    op.type = OP_INSERT;
    op.line = line;
    strncpy(op.statement, stat, MAX_LEN);
    push_undo(op);
    // Redo stack'i sıfırla
    redo_top = -1;

    if (inuse_head == -1 || line <= 0) {
        textbuffer[new_idx].prev = -1;
        textbuffer[new_idx].next = inuse_head;
        if (inuse_head != -1) {
            textbuffer[inuse_head].prev = new_idx;
        }
        inuse_head = new_idx;
        printf("Line inserted at beginning.\n");
        return;
    }

    int current = inuse_head;
    int idx = 0;
    while (textbuffer[current].next != -1 && idx < line - 1) {
        current = textbuffer[current].next;
        idx++;
    }

    int next_idx = textbuffer[current].next;
    textbuffer[new_idx].prev = current;
    textbuffer[new_idx].next = next_idx;
    textbuffer[current].next = new_idx;
    if (next_idx != -1) {
        textbuffer[next_idx].prev = new_idx;
    }
    printf("Line inserted at position %d.\n", line);
}