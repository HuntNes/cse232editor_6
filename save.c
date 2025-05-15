#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cse232editor.h"

extern struct node textbuffer[MAX_LINES];
extern int inuse_head;

void save(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Error: Could not open file for writing.\n");
        return;
    }
    int idx = inuse_head;
    while (idx != -1) {
        fprintf(fp, "%s\n", textbuffer[idx].statement);
        idx = textbuffer[idx].next;
    }
    fclose(fp);
    printf("File saved successfully: %s\n", filename);
}