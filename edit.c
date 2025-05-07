#include <stdio.h>
#include <string.h>
#include "cse232editor.h"

extern struct node textbuffer[MAX_LINES];
extern int inuse_head;
extern int free_head;

void edit(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
       
        return;
    }

    char line[MAX_LEN];
    int prev = -1;

    while (fgets(line, sizeof(line), fp)) {
        
        line[strcspn(line, "\n")] = 0;
       
        int idx = free_head;
        if (idx == -1) break; 
       
        free_head = textbuffer[idx].next;

        strcpy(textbuffer[idx].statement, line);
        textbuffer[idx].prev = prev;
        textbuffer[idx].next = -1;

        if (prev != -1)
            textbuffer[prev].next = idx;
        else
            inuse_head = idx;

        prev = idx;
    }

    fclose(fp);
}