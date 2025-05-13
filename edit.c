#include <stdio.h>
#include <string.h>
#include "cse232editor.h"

extern struct node textbuffer[MAX_LINES];
extern int inuse_head;
extern int free_head;

void edit(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("New file created: %s\n", filename);
        return;
    }

    for (int i = 0; i < MAX_LINES; i++) {
        textbuffer[i].prev = -1;
        textbuffer[i].next = i + 1;
        strcpy(textbuffer[i].statement, "");
    }
    textbuffer[MAX_LINES - 1].next = -1;
    inuse_head = -1;
    free_head = 0;

    char line[MAX_LEN];
    int prev = -1;

    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0;
        
        int idx = free_head;
        if (idx == -1) {
            printf("Warning: File too large, some lines were not loaded.\n");
            break;
        }
        
        free_head = textbuffer[idx].next;

        strncpy(textbuffer[idx].statement, line, MAX_LEN - 1);
        textbuffer[idx].statement[MAX_LEN - 1] = '\0';
        textbuffer[idx].prev = prev;
        textbuffer[idx].next = -1;

        if (prev != -1)
            textbuffer[prev].next = idx;
        else
            inuse_head = idx;

        prev = idx;
    }

    fclose(fp);
    printf("File loaded successfully: %s\n", filename);
}