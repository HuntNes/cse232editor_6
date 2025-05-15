
#include "cse232editor.h"
#include <string.h>
#include <stdio.h>
void delete(int line) {
    if (line < 0 || line >= MAX_LINES) {
        printf("Error: Invalid line input!\n");
        return;
    }
    int prev = textbuffer[line].prev;
    int next = textbuffer[line].next;


    if (line == inuse_head) {
        inuse_head = next;
    }


    if (prev != -1) {
        textbuffer[prev].next = next;
    }


    if (next != -1) {
        textbuffer[next].prev = prev;
    }


    textbuffer[line].prev = -1;
    textbuffer[line].next = free_head;
    memset(textbuffer[line].statement, 0, MAX_LEN);
    free_head = line;
}
