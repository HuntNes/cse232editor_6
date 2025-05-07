#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cse232editor.h"

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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./cse232editor filename\n");
        return 1;
    }

    initialize_buffer();
    edit(argv[1]);

    printf("Editor started. (Commands: Q to quit)\n");

    char command[10];
    while (1) {
        printf("> ");
        fgets(command, sizeof(command), stdin);

        if (command[0] == 'Q' || command[0] == 'q') {
            break;
        }
        else {
            printf("Command not recognized yet.\n");
        }
    }

    return 0;
}