#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cse232editor.h"
#include "interface.h"

struct node textbuffer[MAX_LINES];
int free_head = 0;
int inuse_head = -1;

void initialize_buffer() {
    for (int i = 0; i < MAX_LINES; i++) {
        textbuffer[i].prev = -1;
        textbuffer[i].next = i + 1;
        strcpy(textbuffer[i].statement, "");
    }
    textbuffer[MAX_LINES - 1].next = -1;
    inuse_head = -1;
    free_head = 0;
}

void run_interface();
void show_help();

int main(int argc, char *argv[]) {
    initialize_buffer();
    run_interface();
    return 0;
}