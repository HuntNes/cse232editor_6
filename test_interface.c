#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "cse232editor.h"

int main() {
    
    for (int i = 0; i < MAX_LINES; i++) {
        textbuffer[i].prev = -1;
        textbuffer[i].next = i + 1;
        strcpy(textbuffer[i].statement, "");
    }
    textbuffer[MAX_LINES - 1].next = -1;
    inuse_head = -1;
    free_head = 0;

    
    insert_line(0, "aaa");
    
    insert_line(1, "bbb");
    
    insert_line(1, "ccc");
    
    delete(2);
    
    undo();
    
    redo();
    
    save("testout.txt");
    
    display();
    
    FILE *fp = fopen("testout.txt", "r");
    char buf[40];
    fgets(buf, sizeof(buf), fp);
    assert(strcmp(buf, "ddd\n") == 0);
    fgets(buf, sizeof(buf), fp);
    assert(strcmp(buf, "aaa\n") == 0);
    fclose(fp);
    printf("Passed\n");
    return 0;
}
